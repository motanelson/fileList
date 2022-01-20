#include <dirent.h>
#include "cstring.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
char *fileLists(char *directory){
	char *lst;
	struct dirent *ldir;
	char *s;
	int lens=0;
	int total=0;
	char r[2080];
	lst=NULL;
	DIR *dir=opendir(directory);
	if(dir==NULL)return lst;
	//list directorys
	ldir=readdir(dir);
	while(ldir!=NULL){
		if(ldir->d_name!=NULL){
			lens=strlen(ldir->d_name);
			if (lens>2070)lens=2070;
			strncpy(r,ldir->d_name,(int)lens+1);
			r[lens];
			if (total==0){
				if (ldir->d_type==DT_DIR){
					lst=newList(r);
					total++;
				}
			}else{
				if (ldir->d_type==DT_DIR){
					lst=addList(lst,r);
					total++;
				}
			}
			ldir=readdir(dir);
		}
	}
	//list files
	dir=opendir(directory);
	if(dir==NULL)return lst;
	ldir=readdir(dir);
	while(ldir!=NULL){
		if(ldir->d_name!=NULL){
			lens=strlen(ldir->d_name);
			if (lens>2070)lens=2070;
			strncpy(r,ldir->d_name,(int)lens+1);
			r[lens];
			if (total==0){
				if (ldir->d_type!=DT_DIR){
					lst=newList(r);
					total++;
				}
			}else{
				if (ldir->d_type!=DT_DIR){
					lst=addList(lst,r);
					total++;
				}
			}
			
			ldir=readdir(dir);
		}
	}
	return lst;
}

void fileCopy(char *file1,char *file2){
	char cc[2080];
	char *ccc;
	int f1;
	int f2;
	size_t sizes;
	ccc=cc;
	f1=open(file1,O_RDONLY);
	f2=creat(file2,O_WRONLY);
	if(f1>0 && f2>0){
		sizes=2070;
		while(sizes!=0){
			sizes=read(f1,ccc,2070);
				write(f2,&ccc,sizes);				
		}
	}
	
}
