#include <http/Http_Parser.h>
#include <string>
#include "http/http_parser.h"

using namespace server;

static const std::string get_msg =
"GET /joyent/http-parser HTTP/1.1\r\n"
"Host: github.com\r\n"
"Connection: keep-alive\r\n"
"Cache-Control: max-age=0\r\n"
"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"Accept-Encoding: gzip,deflate,sdch\r\n"
"Accept-Language: zh-CN,zh;q=0.8,en;q=0.6\r\n"
"Accept-Charset: gb18030,utf-8;q=0.7,*;q=0.3\r\n"
"Cookie: tracker=http%3A%2F%2Fnodejs.org%2F; _gh_sess=BAh7DyIVemVkc2hhdy9tb25ncmVsMnsGOhhpc3N1ZV92aWV3X3NldHRpbmdzewgiCXNvcnQiDGNyZWF0ZWQiDmRpcmVjdGlvbiIJZGVzYyIKc3RhdGUiC2Nsb3NlZDoQX2NzcmZfdG9rZW4iMUw0eVBPdE5SVXU4eHYwZlRuZFJHY2x6QmNkYUlzclBoalhpZWR5a2NzS3M9OhBmaW5nZXJwcmludCIlYTM3YTg2ODQ0M2Q4ZWJiZDM4OGM4NThlMTc3OWMwZTM6DGNvbnRleHQiBi86D3Nlc3Npb25faWQiJWQ2ODVjZjM5YTcxZTg5NmZkYmI0NmNlMDY3NmUwMGFlIhNyeS9odHRwLXBhcnNlcnsAOhFsb2NhbGVfZ3Vlc3MiB3poIhhwaGVuZHJ5eC9zdXBlcnB1dHR5ewAiCmZsYXNoSUM6J0FjdGlvbkNvbnRyb2xsZXI6OkZsYXNoOjpGbGFzaEhhc2h7AAY6CkB1c2VkewA6CXVzZXJpA57pEQ%3D%3D--e3154a27f5cdb7f1a8b0351f997b7e3d752f4636; spy_repo=joyent%2Fhttp-parser; spy_repo_at=Sun%20Feb%2019%202012%2015%3A20%3A31%20GMT%2B0800%20(%E4%B8%AD%E5%9B%BD%E6%A0%87%E5%87%86%E6%97%B6%E9%97%B4); __utma=1.1355277945.1305645384.1329633368.1329635599.209; __utmc=1; __utmz=1.1327920052.183.88.utmcsr=nodejs.org|utmccn=(referral)|utmcmd=referral|utmcct=/\r\n"
"If-None-Match: 7f9c6a2baf61233cedd62ffa906b604f\r\n"
"\r\n";


static const std::string post_msg =
"POST /hoge/ HTTP/1.1\r\n"
"Host: localhost:8080\r\n"
"Connection: keep-alive\r\n"
"Content-Length: 22\r\n"
"Cache-Control: max-age=0\r\n"
"Origin: http://localhost:8080\r\n"
"Upgrade-Insecure-Requests: 1\r\n"
"User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.98 Safari/537.36\r\n"
"Content-Type: application/x-www-form-urlencoded\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
"Referer: http://localhost:8080/hoge/\r\n"
"Accept-Encoding: gzip, deflate, br\r\n"
"Accept-Language: ja,en-US;q=0.8,en;q=0.6\r\n"
"\r\n"
"name=hoge&comment=hoge\r\n";

int main() {
    http_parser parser;
    http_parser_settings settings = {
        nullptr,
        http::on_method,
        http::on_url,
        http::on_http_version,
        http::on_header_field,
        http::on_header_value,
        http::on_headers_complete,
    };

    http_parser_init(&parser, HTTP_REQUEST);
    http_parser_execute(&parser, &settings, post_msg.c_str(), post_msg.size());
    
}