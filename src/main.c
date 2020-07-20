#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include "../include/xhttpd_send.h"
#include "../include/xhttpd_node.h"
#include "../include/xhttpd_other.h"
#include "../include/get_type.h"

#define N 4096


int main(int argc,char *argv[])
{
	char line[N*2], method[N*2], path[N*2], protocol[N*2], idx[N*4], location[N*4];
    char *file;
    size_t len;
    int ich, i, n;
    struct stat sb;
    FILE *fp;
    struct dirent **dl; //拆分目录时用于存储目录项
	
	if (argc != 2)
		send_error(500, "Internal Error", NULL, "Config error - no dir specified.");

    if (chdir(argv[1]) < 0)
		send_error(500, "Internal Error", NULL, "Config error - couldn't chdir().");

    if (fgets(line, sizeof(line), stdin) == NULL)                       //GET /my_%5bxdight%5d.txt http/1.1
		send_error(400, "Bad Request", NULL, "No request found.");

    if (sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol) != 3)
		send_error(400, "Bad Request", NULL, "Can't parse request.");

    while (fgets(line, sizeof(line), stdin) != NULL) {		//注意stdin被dup2至xinetd管道的读端
		if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0)
			break;
	}

    if (strcasecmp(method, "GET") != 0)
		send_error(501, "Not Implemented", NULL, "That method is not implemented.");

    if (path[0] != '/')
		send_error(400, "Bad Request", NULL, "Bad filename.");

    file = &(path[1]);		//file = path+1
	
	strdecode(file, file);          //strencode/strdecode();解码
	
	if (file[0] == '\0') //当文件路径为空的时候，既没有文件
		file = "./";
	
	len = strlen(file);
    if (file[0] == '/' || strcmp(file, "..") == 0 
					   || strncmp(file, "../", 3) == 0 
					   || strstr(file, "/../") != NULL
					   || strcmp(&(file[len-3]), "/..") == 0)
	{
		send_error(400, "Bad Request", (char*)0, "Illegal filename.");
	}
	if (stat(file, &sb) < 0)   //file != my_%5bxdight%5d.txt   file == my_[xdight].txt  上上步解码
		send_error(404, "Not Found", (char*)0, "File not found.");		
		
		
	if (S_ISDIR(sb.st_mode)) {

		if (file[len-1] != '/') {
	    	snprintf(location, sizeof(location), "Location: %s/", path);
	    	send_error(302, "Found", location, "Directories must end with a slash.");
	    }
/*
		snprintf(idx, sizeof(idx), "%sindex.html", file);
		if (stat(idx, &sb) >= 0) {
	    	file = idx;
	    	goto do_file;	//如果有index.html则跳到do_file:
	    }
*/
		send_headers(200, "Ok", NULL, "text/html", -1, sb.st_mtime);
		
		printf("<html><head><title>Index of %s</title></head>"
		               "\n<body bgcolor=\"#99cc99\"><h4>Index of %s</h4>\n<pre>\n"
		               , file, file);

		n = scandir(file, &dl, NULL, alphasort);        //拆分目录项

		if (n < 0)
	    	//perror("scandir");
			write_log("main",89,"scandir error");
            //写错误日志  fopen(); /home/itheima/log/   myxhttpd.log   __FILE__   __LINE__  errno  描述  / strerror(errno);
		else
	    	for (i = 0; i < n; ++i)
				//发送文件详细信息，包括日期和时间
                file_infos(file, dl[i]->d_name);	
		
	}
	else {					//所请求非目录而是一个文件

do_file:
		fp = fopen(file, "r");	//只读方式将文件打开
		if (fp == (FILE*)0)
	    	send_error(403, "Forbidden", (char*)0, "File is protected.");

		send_headers(200, "Ok", (char*)0, get_mime_type(file), sb.st_size, sb.st_mtime);

		while ((ich = getc(fp)) != EOF)
	    	putchar(ich);
	}
    fflush(stdout);
    exit(0);
		
		
}
