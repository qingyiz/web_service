#pragma once
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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
void send_error(int status, char* title, char* extra_header, char* text);



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
void send_headers(int status, char* title, char* extra_header, char* mime_type, off_t length, time_t mod);
