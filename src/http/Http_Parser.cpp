
#line 1 "Http_Parser.rl"
#include <http/http_parser.h>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LEN(AT, FPC) (FPC - buffer - parser->AT)
#define MARK(M,FPC) (parser->M = (FPC) - buffer)
#define PTR_TO(F) (buffer + parser->F)

/** Machine **/


#line 108 "Http_Parser.rl"


/** Data **/

#line 24 "Http_Parser.cpp"
static const char _http_parser_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 2, 6, 7, 2, 9, 
	1, 2, 10, 1, 2, 11, 1, 2, 
	12, 1, 2, 13, 1
};

static const short _http_parser_key_offsets[] = {
	0, 0, 12, 21, 24, 26, 27, 28, 
	29, 30, 31, 32, 33, 35, 37, 54, 
	55, 71, 74, 76, 77, 86, 92, 98, 
	107, 113, 119, 120, 121, 122, 123, 132, 
	141, 150, 159, 168, 177, 186, 195, 204, 
	213, 222, 231, 240, 249, 258, 267, 276, 
	285, 286, 296, 306, 316, 326, 336, 345, 
	355, 365, 374, 384, 394, 404, 413, 424, 
	434, 444, 453, 463, 472
};

static const char _http_parser_trans_keys[] = {
	36, 68, 71, 72, 80, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 95, 45, 
	46, 48, 57, 65, 90, 42, 47, 104, 
	32, 35, 72, 84, 84, 80, 47, 49, 
	46, 48, 49, 10, 13, 10, 13, 33, 
	124, 126, 35, 39, 42, 43, 45, 46, 
	48, 57, 65, 90, 94, 122, 10, 33, 
	58, 124, 126, 35, 39, 42, 43, 45, 
	46, 48, 57, 65, 90, 94, 122, 10, 
	13, 32, 10, 13, 10, 32, 37, 60, 
	62, 127, 0, 31, 34, 35, 48, 57, 
	65, 70, 97, 102, 48, 57, 65, 70, 
	97, 102, 32, 34, 35, 37, 60, 62, 
	127, 0, 31, 48, 57, 65, 70, 97, 
	102, 48, 57, 65, 70, 97, 102, 116, 
	116, 112, 58, 32, 36, 95, 45, 46, 
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
	36, 95, 45, 46, 48, 57, 65, 90, 
	32, 36, 95, 45, 46, 48, 57, 65, 
	90, 32, 36, 95, 45, 46, 48, 57, 
	65, 90, 32, 36, 95, 45, 46, 48, 
	57, 65, 90, 32, 36, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 95, 45, 
	46, 48, 57, 65, 90, 32, 32, 36, 
	69, 95, 45, 46, 48, 57, 65, 90, 
	32, 36, 76, 95, 45, 46, 48, 57, 
	65, 90, 32, 36, 69, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 84, 95, 
	45, 46, 48, 57, 65, 90, 32, 36, 
	69, 95, 45, 46, 48, 57, 65, 90, 
	32, 36, 95, 45, 46, 48, 57, 65, 
	90, 32, 36, 69, 95, 45, 46, 48, 
	57, 65, 90, 32, 36, 84, 95, 45, 
	46, 48, 57, 65, 90, 32, 36, 95, 
	45, 46, 48, 57, 65, 90, 32, 36, 
	69, 95, 45, 46, 48, 57, 65, 90, 
	32, 36, 65, 95, 45, 46, 48, 57, 
	66, 90, 32, 36, 68, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 95, 45, 
	46, 48, 57, 65, 90, 32, 36, 79, 
	85, 95, 45, 46, 48, 57, 65, 90, 
	32, 36, 83, 95, 45, 46, 48, 57, 
	65, 90, 32, 36, 84, 95, 45, 46, 
	48, 57, 65, 90, 32, 36, 95, 45, 
	46, 48, 57, 65, 90, 32, 36, 84, 
	95, 45, 46, 48, 57, 65, 90, 32, 
	36, 95, 45, 46, 48, 57, 65, 90, 
	0
};

static const char _http_parser_single_lengths[] = {
	0, 6, 3, 3, 2, 1, 1, 1, 
	1, 1, 1, 1, 0, 2, 5, 1, 
	4, 3, 2, 1, 5, 0, 0, 7, 
	0, 0, 1, 1, 1, 1, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	1, 4, 4, 4, 4, 4, 3, 4, 
	4, 3, 4, 4, 4, 3, 5, 4, 
	4, 3, 4, 3, 0
};

static const char _http_parser_range_lengths[] = {
	0, 3, 3, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 0, 6, 0, 
	6, 0, 0, 0, 2, 3, 3, 1, 
	3, 3, 0, 0, 0, 0, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	0, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 0
};

static const short _http_parser_index_offsets[] = {
	0, 0, 10, 17, 21, 24, 26, 28, 
	30, 32, 34, 36, 38, 40, 43, 55, 
	57, 68, 72, 75, 77, 85, 89, 93, 
	102, 106, 110, 112, 114, 116, 118, 125, 
	132, 139, 146, 153, 160, 167, 174, 181, 
	188, 195, 202, 209, 216, 223, 230, 237, 
	244, 246, 254, 262, 270, 278, 286, 293, 
	301, 309, 316, 324, 332, 340, 347, 356, 
	364, 372, 379, 387, 394
};

static const char _http_parser_indicies[] = {
	0, 2, 3, 4, 5, 0, 0, 0, 
	0, 1, 6, 7, 7, 7, 7, 7, 
	1, 8, 9, 10, 1, 11, 12, 1, 
	13, 1, 14, 1, 15, 1, 16, 1, 
	17, 1, 18, 1, 19, 1, 20, 1, 
	21, 22, 1, 23, 24, 25, 25, 25, 
	25, 25, 25, 25, 25, 25, 1, 23, 
	1, 26, 27, 26, 26, 26, 26, 26, 
	26, 26, 26, 1, 29, 30, 31, 28, 
	33, 34, 32, 35, 1, 37, 38, 1, 
	1, 1, 1, 1, 36, 39, 39, 39, 
	1, 36, 36, 36, 1, 11, 1, 12, 
	41, 1, 1, 1, 1, 40, 42, 42, 
	42, 1, 40, 40, 40, 1, 43, 1, 
	44, 1, 45, 1, 40, 1, 6, 46, 
	46, 46, 46, 46, 1, 6, 47, 47, 
	47, 47, 47, 1, 6, 48, 48, 48, 
	48, 48, 1, 6, 49, 49, 49, 49, 
	49, 1, 6, 50, 50, 50, 50, 50, 
	1, 6, 51, 51, 51, 51, 51, 1, 
	6, 52, 52, 52, 52, 52, 1, 6, 
	53, 53, 53, 53, 53, 1, 6, 54, 
	54, 54, 54, 54, 1, 6, 55, 55, 
	55, 55, 55, 1, 6, 56, 56, 56, 
	56, 56, 1, 6, 57, 57, 57, 57, 
	57, 1, 6, 58, 58, 58, 58, 58, 
	1, 6, 59, 59, 59, 59, 59, 1, 
	6, 60, 60, 60, 60, 60, 1, 6, 
	61, 61, 61, 61, 61, 1, 6, 62, 
	62, 62, 62, 62, 1, 6, 63, 63, 
	63, 63, 63, 1, 6, 1, 6, 7, 
	64, 7, 7, 7, 7, 1, 6, 46, 
	65, 46, 46, 46, 46, 1, 6, 47, 
	66, 47, 47, 47, 47, 1, 6, 48, 
	67, 48, 48, 48, 48, 1, 6, 49, 
	68, 49, 49, 49, 49, 1, 69, 50, 
	50, 50, 50, 50, 1, 6, 7, 70, 
	7, 7, 7, 7, 1, 6, 46, 71, 
	46, 46, 46, 46, 1, 72, 47, 47, 
	47, 47, 47, 1, 6, 7, 73, 7, 
	7, 7, 7, 1, 6, 46, 74, 46, 
	46, 46, 46, 1, 6, 47, 75, 47, 
	47, 47, 47, 1, 76, 48, 48, 48, 
	48, 48, 1, 6, 7, 77, 78, 7, 
	7, 7, 7, 1, 6, 46, 79, 46, 
	46, 46, 46, 1, 6, 47, 80, 47, 
	47, 47, 47, 1, 81, 48, 48, 48, 
	48, 48, 1, 6, 46, 82, 46, 46, 
	46, 46, 1, 83, 47, 47, 47, 47, 
	47, 1, 1, 0
};

static const char _http_parser_trans_targs[] = {
	2, 0, 49, 55, 58, 62, 3, 30, 
	4, 23, 26, 5, 20, 6, 7, 8, 
	9, 10, 11, 12, 13, 14, 19, 68, 
	15, 16, 16, 17, 18, 14, 19, 17, 
	18, 14, 19, 14, 20, 5, 21, 22, 
	23, 24, 25, 27, 28, 29, 31, 32, 
	33, 34, 35, 36, 37, 38, 39, 40, 
	41, 42, 43, 44, 45, 46, 47, 48, 
	50, 51, 52, 53, 54, 3, 56, 57, 
	3, 59, 60, 61, 3, 63, 66, 64, 
	65, 3, 67, 3
};

static const char _http_parser_trans_actions[] = {
	1, 0, 1, 1, 1, 1, 3, 0, 
	1, 1, 1, 5, 5, 1, 0, 0, 
	0, 0, 0, 0, 0, 7, 7, 17, 
	0, 9, 0, 11, 13, 19, 19, 13, 
	0, 15, 15, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 22, 0, 0, 
	25, 0, 0, 0, 28, 0, 0, 0, 
	0, 31, 0, 34
};

static const int http_parser_start = 1;
static const int http_parser_first_final = 68;
static const int http_parser_error = 0;

static const int http_parser_en_main = 1;


#line 112 "Http_Parser.rl"

void
http_parser_init (http_parser *parser, enum http_parser_type t)
{
  int cs = 0;
  
#line 239 "Http_Parser.cpp"
	{
	cs = http_parser_start;
	}

#line 118 "Http_Parser.rl"

  void *data = parser->data; /* preserve application data */
  memset(parser, 0, sizeof(*parser));
  parser->data = data;
  parser->type = t;
  parser->state = cs;
  parser->http_errno = 0;
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
  
  
#line 265 "Http_Parser.cpp"
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
#line 19 "Http_Parser.rl"
	{ mark = p; }
	break;
	case 1:
#line 21 "Http_Parser.rl"
	{}
	break;
	case 2:
#line 23 "Http_Parser.rl"
	{ 
    if(settings->on_url != NULL)
      settings->on_url(parser, mark, p -mark);
  }
	break;
	case 3:
#line 28 "Http_Parser.rl"
	{	
  }
	break;
	case 4:
#line 31 "Http_Parser.rl"
	{ mark = p; }
	break;
	case 5:
#line 32 "Http_Parser.rl"
	{ 
    if(settings->on_header_field != NULL)
      settings->on_header_field(parser, mark, p -mark);
  }
	break;
	case 6:
#line 37 "Http_Parser.rl"
	{ mark = p; }
	break;
	case 7:
#line 38 "Http_Parser.rl"
	{
    if(settings->on_header_value != NULL)
      settings->on_header_value(parser, mark, p -mark);
  }
	break;
	case 8:
#line 43 "Http_Parser.rl"
	{
    if(settings->on_headers_complete != NULL)
      settings->on_headers_complete(parser);

    if(settings->on_message_complete != NULL)
      settings->on_message_complete(parser);

    {p++; goto _out; }
  }
	break;
	case 9:
#line 86 "Http_Parser.rl"
	{ parser->method = HTTP_DELETE; }
	break;
	case 10:
#line 87 "Http_Parser.rl"
	{ parser->method = HTTP_GET; }
	break;
	case 11:
#line 88 "Http_Parser.rl"
	{ parser->method = HTTP_HEAD; }
	break;
	case 12:
#line 89 "Http_Parser.rl"
	{ parser->method = HTTP_POST; }
	break;
	case 13:
#line 90 "Http_Parser.rl"
	{ parser->method = HTTP_PUT; }
	break;
#line 413 "Http_Parser.cpp"
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

#line 138 "Http_Parser.rl"
  
  return p - data;
}
