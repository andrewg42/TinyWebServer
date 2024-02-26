/*
 *  ref: https://github.com/nodejs/http-parser/blob/main/http_parser.callback
 *       https://github.com/lxu4net/RagelHttpParser/blob/master/ragel/http11_parser.rl 
 *
 *  Modified by Tang.Handi in Feb. 2024.
 *
 *  Notice:
 *  If you want to change this file, please change .rl file.
 *  And then use
 *      'ragel xxx.rl -o xxx.cpp'
 *  to generate .cpp file.
 */

#include <http/http_parser.h>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <ctype.h>
#include <cstring>

/** Machine **/
%%{

    machine http_parser;

    action mark { mark = fpc; }

    action request_method {
        if(nullptr != settings->on_method)
            settings->on_method(parser);
    }

    action request_uri { 
        if(nullptr != settings->on_url)
            settings->on_url(parser, mark, fpc - mark);
    }

    action http_version {
        if(nullptr != settings->on_http_version)
            settings->on_http_version(parser, mark, fpc - mark);
    }

    action start_field { mark = fpc; }
    action write_field {
        if(nullptr != settings->on_header_field)
            settings->on_header_field(parser, mark, fpc - mark);
    }

    action start_value { mark = fpc; }
    action write_value {
        if(nullptr != settings->on_header_value)
            settings->on_header_value(parser, mark, fpc - mark);
    }

    action done {
        if(nullptr != settings->on_headers_complete)
            settings->on_headers_complete(parser, mark, fpc - mark);
        
        fbreak;
    }

    # no error handler currently
    action error { parser->http_errno = HPE_UNKNOWN; }

    #### HTTP PROTOCOL GRAMMAR
    # line endings
    CRLF = "\r\n";

    # character types
    CTL = (cntrl | 127);
    safe = ("$" | "-" | "_" | ".");
    extra = ("!" | "*" | "'" | "(" | ")" | ",");
    reserved = (";" | "/" | "?" | ":" | "@" | "&" | "=" | "+");
    unsafe = (CTL | " " | "\"" | "#" | "%" | "<" | ">");
    national = any -- (alpha | digit | reserved | extra | safe | unsafe);
    unreserved = (alpha | digit | safe | extra | national);
    escape = ("%" xdigit xdigit);
    uchar = (unreserved | escape);
    pchar = (uchar | ":" | "@" | "&" | "=" | "+");
    tspecials = ("(" | ")" | "<" | ">" | "@" | "," | ";" | ":" | "\\" | "\"" | "/" | "[" | "]" | "?" | "=" | "{" | "}" | " " | "\t");

    # elements
    token = (ascii -- (CTL | tspecials));

    # URI schemes and absolute paths
    scheme = "http";
    absolute_uri = (scheme ":" (uchar | reserved )*);

    path = ( pchar+ ( "/" pchar* )* ) ;
    query = ( uchar | reserved )* ;
    param = ( pchar | "/" )* ;
    params = ( param ( ";" param )* ) ;
    rel_path = ( path? (";" params)? ) ("?" query)?;
    absolute_path = ( "/"+ rel_path );

    Request_URI = ( "*" | absolute_uri | absolute_path ) >mark %request_uri;
    Fragment = ( uchar | reserved )*;
    # only support GET and POST
    Method = (    "GET"            %{ parser->method = HTTP_GET; }
                | "POST"           %{ parser->method = HTTP_POST; }
                | ( upper | digit | safe ){1,20}
            ) >mark %request_method;

    http_number = ( "1." ("0" | "1") ) ;
    HTTP_Version = ( "HTTP/" http_number ) >mark %http_version ;
    Request_Line = ( Method " " Request_URI ("#" Fragment){0,1} " " HTTP_Version CRLF ) ;

    field_name = ( token -- ":" )+ >start_field %write_field;

    field_value = any* >start_value %write_value;

    message_header = field_name ":" " "* field_value :> CRLF;

    Request = Request_Line ( message_header )* CRLF;

    main := (Request) @done;

}%%

/** Data **/
%% write data;

void
http_parser_init (http_parser *parser, enum http_parser_type t)
{
    int cs = 0;
    %% write init;

    memset(parser, 0, sizeof(*parser));
    parser->type = t;
    parser->state = cs;
    parser->http_errno = HPE_UNKNOWN;
}

size_t http_parser_execute (http_parser *parser,
                            const http_parser_settings *settings,
                            const char *data,
                            size_t len)
{
    int cs = parser->state;
    const char *p = data;
    const char *pe = data + len;
    const char *mark = 0;
    
    %% write exec;
    
    return p - data;
}
