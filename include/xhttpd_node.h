#pragma once
#include <ctype.h>
#include <stdio.h>
/*
 *  * 这里的内容是处理%20之类的东西！是"解码"过程。
 *   * %20 URL编码中的‘ ’(space)
 *    * %21 '!' %22 '"' %23 '#' %24 '$'
 *     * %25 '%' %26 '&' %27 ''' %28  '''('......
 *      * 相关知识html中的‘ ’(space)是&nbsp
 *      
*/
void strdecode(char *to, char *from);

//16进制数转化为10进制, return 0不会出现 
int hexit(char c);

//"编码"，用作回写浏览器的时候，将除字母数字及/_.-~以外的字符转义后回写。
//strencode(encoded_name, sizeof(d_name), name);

void strencode(char* to, size_t tosize, const char* from);
