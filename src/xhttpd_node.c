#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../include/xhttpd_node.h"

/*
 * 这里的内容是处理%20之类的东西！是"解码"过程。
 * %20 URL编码中的‘ ’(space)
 * %21 '!' %22 '"' %23 '#' %24 '$'
 * %25 '%' %26 '&' %27 ''' %28 '('......
 * 相关知识html中的‘ ’(space)是&nbsp
 */
void strdecode(char *to, char *from)
{
    for ( ; *from != '\0'; ++to, ++from) {
	
		if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2])) { //依次判断from中 %20 三个字符
	    
	    	*to = hexit(from[1])*16 + hexit(from[2]);
	    	from += 2;                      //移过已经处理的两个字符(%21指针指向1),表达式3的++from还会再向后移一个字符
	    } else
	    	*to = *from;
	}
    *to = '\0';
}

//16进制数转化为10进制, return 0不会出现 
int hexit(char c)
{
    if (c >= '0' && c <= '9')
		return c - '0';
    if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;

    return 0;		
}

//"编码"，用作回写浏览器的时候，将除字母数字及/_.-~以外的字符转义后回写。
//strencode(encoded_name, sizeof(encoded_name), name);
void strencode(char* to, size_t tosize, const char* from)
{
    int tolen;

    for (tolen = 0; *from != '\0' && tolen + 4 < tosize; ++from) {
		if (isalnum(*from) || strchr("/_.-~", *from) != (char*)0) {
			*to = *from;
			++to;
			++tolen;
		} else {
			sprintf(to, "%%%02x", (int) *from & 0xff);	
			to += 3;
			tolen += 3;
		}
	}
    *to = '\0';
}
