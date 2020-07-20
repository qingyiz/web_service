
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/xhttpd_send.h"

#define SERVER_NAME "xhttpd"
#define PROTOCOL "HTTP/1.1"
#define SERVER_URL "http://www.itcast.com/"
#define	FORMAT_DATE "%a, %d %b %Y %H:%M:%S GMT"


/*
 *status:错误号
 *title: 错误名
 *text： 错误描述
 *extra_header:附加描述(特殊情况302时不退出程序，而直接显示正常页面)
 */

void send_error(int status, char* title, char* extra_header, char* text)
{
    send_headers(status, title, extra_header, "text/html", -1, -1);
    printf("<html><head><title>%d %s</title></head>\n<body bgcolor=\"#cc9999\"><h4>%d %s</h4>\n", 
			status, title, status, title);

    printf("%s\n", text);
    printf("<hr>\n<address><a href=\"%s\">%s</a></address>\n</body></html>\n", SERVER_URL, SERVER_NAME);
    fflush(stdout);

    exit( 1 );
}

/*
 *每个HTTP传送都包含一个首部、一个空行和要发送的数据项。
 *Content-Type:		数据项的类型(必选项)
 *Content-length:	数据项的大小
 *Content-Encoding:	数据项使用的编码方式
 *Content-Language:	数据项使用的语言
 *
 *首部中的每一行都包含一个关键字、一个冒号和信息。
 *e.g.
 *Content-Type: text/html; charset=iso-8859-1		指明属性的首部
 *Content-Length: 508
 *													这是一行空行
 *<html> 文档内容 </html>							数据项
 */

void send_headers(int status, char* title, char* extra_header, char* mime_type, off_t length, time_t mod)
{
    time_t now;
    char timebuf[100];

    printf("%s %d %s\r\n", PROTOCOL, status, title);//HTTP/1.0 200 OK
    printf("Server: %s\r\n", SERVER_NAME);//Server: xhttpd
    now = time((time_t*)0);
    strftime(timebuf, sizeof(timebuf), FORMAT_DATE, gmtime(&now));
    printf("Date: %s\r\n", timebuf);

	// Date: Fri, 18 Jul 2014 14:34:26 GMT

    if (extra_header != NULL)
		printf("%s\r\n", extra_header);

    if (mime_type != NULL)
		printf("Content-Type: %s\r\n", mime_type);

    if (length >= 0)
		printf("Content-Length: %ld\r\n", (int64_t)length);

    if (mod != (time_t)-1) {	//强转
		strftime(timebuf, sizeof(timebuf), FORMAT_DATE, gmtime(&mod));
		printf("Last-Modified: %s\r\n", timebuf);		
	}
	printf("Connection: close\r\n");
	printf("\r\n");
}
