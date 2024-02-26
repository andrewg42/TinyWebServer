
#line 1 "../../src/http/Http_Parser.rl"
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

#line 116 "../../src/http/Http_Parser.rl"


/** Data **/

#line 32 "../../src/http/Http_Parser.cpp"
static const char _http_parser_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 2, 6, 7, 2, 9, 
	1, 2, 10, 1
};

static const short _http_parser_key_offsets[] = {
	0, 0, 10, 19, 22, 24, 25, 26, 
	27, 28, 29, 30, 31, 33, 34, 35, 
	51, 52, 68, 70, 71, 80, 86, 92, 
	101, 107, 113, 114, 115, 116, 117, 126, 
	135, 144, 153, 162, 171, 180, 189, 198, 
	207, 216, 225, 234, 243, 252, 261, 270, 
	279, 280, 290, 300, 309, 319, 329, 339, 
	348
};

static const char _http_parser_trans_keys[] = {
	36, 71, 80, 95, 45, 46, 48, 57, 
	65, 90, 32, 36, 95, 45, 46, 48, 
	57, 65, 90, 42, 47, 104, 32, 35, 
	72, 84, 84, 80, 47, 49, 46, 48, 
	49, 13, 10, 13, 33, 124, 126, 35, 
	39, 42, 43, 45, 46, 48, 57, 65, 
	90, 94, 122, 10, 33, 58, 124, 126, 
	35, 39, 42, 43, 45, 46, 48, 57, 
	65, 90, 94, 122, 13, 32, 13, 32, 
	37, 60, 62, 127, 0, 31, 34, 35, 
	48, 57, 65, 70, 97, 102, 48, 57, 
	65, 70, 97, 102, 32, 34, 35, 37, 
	60, 62, 127, 0, 31, 48, 57, 65, 
	70, 97, 102, 48, 57, 65, 70, 97, 
	102, 116, 116, 112, 58, 32, 36, 95, 
	45, 46, 48, 57, 65, 90, 32, 36, 
	95, 45, 46, 48, 57, 65, 90, 32, 
	36, 95, 45, 46, 48, 57, 65, 90, 
	32, 36, 95, 45, 46, 48, 57, 65, 
	90, 32, 36, 95, 45, 46, 48, 57, 
	65, 90, 32, 36, 95, 45, 46, 48, 
	57, 65, 90, 32, 36, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 95, 45, 
	46, 48, 57, 65, 90, 32, 36, 95, 
	45, 46, 48, 57, 65, 90, 32, 36, 
	95, 45, 46, 48, 57, 65, 90, 32, 
	36, 95, 45, 46, 48, 57, 65, 90, 
	32, 36, 95, 45, 46, 48, 57, 65, 
	90, 32, 36, 95, 45, 46, 48, 57, 
	65, 90, 32, 36, 95, 45, 46, 48, 
	57, 65, 90, 32, 36, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 95, 45, 
	46, 48, 57, 65, 90, 32, 36, 95, 
	45, 46, 48, 57, 65, 90, 32, 36, 
	95, 45, 46, 48, 57, 65, 90, 32, 
	32, 36, 69, 95, 45, 46, 48, 57, 
	65, 90, 32, 36, 84, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 95, 45, 
	46, 48, 57, 65, 90, 32, 36, 79, 
	95, 45, 46, 48, 57, 65, 90, 32, 
	36, 83, 95, 45, 46, 48, 57, 65, 
	90, 32, 36, 84, 95, 45, 46, 48, 
	57, 65, 90, 32, 36, 95, 45, 46, 
	48, 57, 65, 90, 0
};

static const char _http_parser_single_lengths[] = {
	0, 4, 3, 3, 2, 1, 1, 1, 
	1, 1, 1, 1, 0, 1, 1, 4, 
	1, 4, 2, 1, 5, 0, 0, 7, 
	0, 0, 1, 1, 1, 1, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	1, 4, 4, 3, 4, 4, 4, 3, 
	0
};

static const char _http_parser_range_lengths[] = {
	0, 3, 3, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 0, 0, 6, 
	0, 6, 0, 0, 2, 3, 3, 1, 
	3, 3, 0, 0, 0, 0, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	0, 3, 3, 3, 3, 3, 3, 3, 
	0
};

static const short _http_parser_index_offsets[] = {
	0, 0, 8, 15, 19, 22, 24, 26, 
	28, 30, 32, 34, 36, 38, 40, 42, 
	53, 55, 66, 69, 71, 79, 83, 87, 
	96, 100, 104, 106, 108, 110, 112, 119, 
	126, 133, 140, 147, 154, 161, 168, 175, 
	182, 189, 196, 203, 210, 217, 224, 231, 
	238, 240, 248, 256, 263, 271, 279, 287, 
	294
};

static const char _http_parser_indicies[] = {
	0, 2, 3, 0, 0, 0, 0, 1, 
	4, 5, 5, 5, 5, 5, 1, 6, 
	7, 8, 1, 9, 10, 1, 11, 1, 
	12, 1, 13, 1, 14, 1, 15, 1, 
	16, 1, 17, 1, 18, 1, 19, 1, 
	20, 1, 21, 22, 22, 22, 22, 22, 
	22, 22, 22, 22, 1, 23, 1, 24, 
	25, 24, 24, 24, 24, 24, 24, 24, 
	24, 1, 27, 28, 26, 30, 29, 32, 
	33, 1, 1, 1, 1, 1, 31, 34, 
	34, 34, 1, 31, 31, 31, 1, 9, 
	1, 10, 36, 1, 1, 1, 1, 35, 
	37, 37, 37, 1, 35, 35, 35, 1, 
	38, 1, 39, 1, 40, 1, 35, 1, 
	4, 41, 41, 41, 41, 41, 1, 4, 
	42, 42, 42, 42, 42, 1, 4, 43, 
	43, 43, 43, 43, 1, 4, 44, 44, 
	44, 44, 44, 1, 4, 45, 45, 45, 
	45, 45, 1, 4, 46, 46, 46, 46, 
	46, 1, 4, 47, 47, 47, 47, 47, 
	1, 4, 48, 48, 48, 48, 48, 1, 
	4, 49, 49, 49, 49, 49, 1, 4, 
	50, 50, 50, 50, 50, 1, 4, 51, 
	51, 51, 51, 51, 1, 4, 52, 52, 
	52, 52, 52, 1, 4, 53, 53, 53, 
	53, 53, 1, 4, 54, 54, 54, 54, 
	54, 1, 4, 55, 55, 55, 55, 55, 
	1, 4, 56, 56, 56, 56, 56, 1, 
	4, 57, 57, 57, 57, 57, 1, 4, 
	58, 58, 58, 58, 58, 1, 4, 1, 
	4, 5, 59, 5, 5, 5, 5, 1, 
	4, 41, 60, 41, 41, 41, 41, 1, 
	61, 42, 42, 42, 42, 42, 1, 4, 
	5, 62, 5, 5, 5, 5, 1, 4, 
	41, 63, 41, 41, 41, 41, 1, 4, 
	42, 64, 42, 42, 42, 42, 1, 65, 
	43, 43, 43, 43, 43, 1, 1, 0
};

static const char _http_parser_trans_targs[] = {
	2, 0, 49, 52, 3, 30, 4, 23, 
	26, 5, 20, 6, 7, 8, 9, 10, 
	11, 12, 13, 14, 15, 16, 17, 56, 
	17, 18, 19, 14, 18, 19, 14, 20, 
	5, 21, 22, 23, 24, 25, 27, 28, 
	29, 31, 32, 33, 34, 35, 36, 37, 
	38, 39, 40, 41, 42, 43, 44, 45, 
	46, 47, 48, 50, 51, 3, 53, 54, 
	55, 3
};

static const char _http_parser_trans_actions[] = {
	1, 0, 1, 1, 3, 0, 1, 1, 
	1, 5, 5, 1, 0, 0, 0, 0, 
	0, 0, 0, 7, 0, 0, 9, 17, 
	0, 11, 13, 19, 13, 0, 15, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 22, 0, 0, 
	0, 25
};

static const int http_parser_start = 1;
static const int http_parser_first_final = 56;
static const int http_parser_error = 0;

static const int http_parser_en_main = 1;


#line 120 "../../src/http/Http_Parser.rl"

void
http_parser_init (http_parser *parser, enum http_parser_type t)
{
    int cs = 0;
    
#line 209 "../../src/http/Http_Parser.cpp"
	{
	cs = http_parser_start;
	}

#line 126 "../../src/http/Http_Parser.rl"

    memset(parser, 0, sizeof(*parser));
    parser->type = t;
    parser->state = cs;
    parser->http_errno = HPE_OK;
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
    
    
#line 233 "../../src/http/Http_Parser.cpp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _http_parser_trans_keys + _http_parser_key_offsets[cs];
	_trans = _http_parser_index_offsets[cs];

	_klen = _http_parser_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _http_parser_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _http_parser_indicies[_trans];
	cs = _http_parser_trans_targs[_trans];

	if ( _http_parser_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _http_parser_actions + _http_parser_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 27 "../../src/http/Http_Parser.rl"
	{ mark = p; }
	break;
	case 1:
#line 29 "../../src/http/Http_Parser.rl"
	{
        if(nullptr != settings->on_method)
            settings->on_method(parser);
    }
	break;
	case 2:
#line 34 "../../src/http/Http_Parser.rl"
	{ 
        if(nullptr != settings->on_url)
            settings->on_url(parser, mark, p - mark);
    }
	break;
	case 3:
#line 39 "../../src/http/Http_Parser.rl"
	{
        if(nullptr != settings->on_http_version)
            settings->on_http_version(parser, mark, p - mark);
    }
	break;
	case 4:
#line 44 "../../src/http/Http_Parser.rl"
	{ mark = p; }
	break;
	case 5:
#line 45 "../../src/http/Http_Parser.rl"
	{
        if(nullptr != settings->on_header_field)
            settings->on_header_field(parser, mark, p - mark);
    }
	break;
	case 6:
#line 50 "../../src/http/Http_Parser.rl"
	{ mark = p; }
	break;
	case 7:
#line 51 "../../src/http/Http_Parser.rl"
	{
        if(nullptr != settings->on_header_value)
            settings->on_header_value(parser, mark, p - mark);
    }
	break;
	case 8:
#line 56 "../../src/http/Http_Parser.rl"
	{
        if(nullptr != settings->on_headers_complete)
            settings->on_headers_complete(parser, mark, p - mark);
        
        {p++; goto _out; }
    }
	break;
	case 9:
#line 97 "../../src/http/Http_Parser.rl"
	{ parser->method = HTTP_GET; }
	break;
	case 10:
#line 98 "../../src/http/Http_Parser.rl"
	{ parser->method = HTTP_POST; }
	break;
#line 371 "../../src/http/Http_Parser.cpp"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 144 "../../src/http/Http_Parser.rl"
    
    return p - data;
}
