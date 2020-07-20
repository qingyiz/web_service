#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "../include/xhttpd_other.h"
#include "../include/xhttpd_node.h"
#define N 4096
#define log(filename,line,str)\
	do{\
		fprintf(tmp, "%s %d:%s\n", filename,line,str);\
		fflush(tmp);\
	}while(0)




void write_log(char *filename,int line, char* str)
{
	FILE *tmp = fopen("/home/huoz/dir/tmp.txt", "a");
	if(tmp == NULL)
	{
		perror("fopen tmp.txt error.");
		exit(1);
	} 
	log(filename,line,str);
	fclose(tmp);
}


void file_infos(char *dir, char *name)
{
    static char encoded_name[N];
    static char path[N];
    char timestr[16];
    struct stat sb;

    strencode(encoded_name, sizeof(encoded_name), name);    //
    snprintf(path, sizeof(path), "%s/%s", dir, name);

    if (lstat(path, &sb) < 0)
		printf("<a href=\"%s\">%-32.32s</a>\n", encoded_name, name);
    else {
		strftime(timestr, sizeof(timestr), "%d%b%Y %H:%M", localtime(&sb.st_mtime));
		printf("<a href=\"%s\">%-32.32s</a>    %15s %14ld\n", encoded_name, name, timestr, (int64_t)sb.st_size);
	}
	
}
