#include <stdio.h>
#include <string.h>
/*
 *get_mime_type :获取请求文件类型
 ×        返回值: char * 文件类型
 ×        参  数:  name  文件路径
 *
 */

char *get_mime_type(char *name)
{
    char* dot;

    dot = strrchr(name, '.');	//自右向左查找‘.’字符;如不存在返回NULL
	/*
	 *charset=iso-8859-1	西欧的编码，说明网站采用的编码是英文；
	 *charset=gb2312		说明网站采用的编码是简体中文；
	 *charset=utf-8			代表世界通用的语言编码；
     *						可以用到中文、韩文、日文等世界上所有语言编码上
	 *charset=euc-kr		说明网站采用的编码是韩文；
	 *charset=big5			说明网站采用的编码是繁体中文；
	 *
	 *以下是依据传递进来的文件名，使用后缀判断是何种文件类型
	 *将对应的文件类型按照http定义的关键字发送回去
	 */
    if (dot == (char*)0)
		return "text/plain; charset=iso-8859-1";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
		return "text/html; charset=iso-8859-1";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
		return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
		return "image/gif";
    if (strcmp(dot, ".png") == 0)
		return "image/png";
    if (strcmp(dot, ".css") == 0)	
		return "text/css";
    if (strcmp(dot, ".au") == 0)	
		return "audio/basic";
    if (strcmp( dot, ".wav") == 0)
		return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
		return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
		return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
		return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)	
		return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)	
		return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
		return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)	
		return "application/ogg";
    if (strcmp(dot, ".pac") == 0)	
		return "application/x-ns-proxy-autoconfig";

	return "text/plain; charset=iso-8859-1";
}
