#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
   
void find(char *path, char *target_file);
   
int main(int argc, char *argv[]) {
	
  if (argc != 3) {
		fprintf(2, "ERROR: You need pass in only 2 arguments\n");
		exit(1);
	}

	char *target_path = argv[1];
	char *target_file = argv[2];
	find(target_path, target_file);
	exit(0);
}
   
void find(char *path, char *target_file) {
	int fd;
	struct stat st;     //file状态结构体变量
	struct dirent de;   //用于文件系统中的direction（目录）的一个结构体变量，由于find的目的是根据目录名和文件名进行寻找，
	char buf[512], *p;
   
	if ((fd = open(path, O_RDONLY)) < 0) {   //fd关联到path目录
		fprintf(2, "ERROR: cannot open %s\n", path);
		return;
	}
   	
	if (fstat(fd, &st) < 0) {       //读fd状态存入变量st
		fprintf(2, "ERROR: cannot stat %s\n", path);
		close(fd);
		return;
	}
   
	//循环：读输入的path路径之后的每一个路径/文件，读到底 --> 每次循环读到的de依据其状态（st.type：目录还是文件）做不同处理 --> 
  //如果是文件，说明读到底了，这时候文件名和targetFile比较是否相等输出就可以了；
  //如果是路径，则说明还没读到底，则继续以当前路径递归查找，直到读到最后是文件为止。
	while (read(fd, &de, sizeof(de)) == sizeof(de)) {
		strcpy(buf, path);
		p = buf+strlen(buf);    //p只是个指针，真正变化的内容还是buf
		*p++ = '/';
		if (de.inum == 0)
			continue;
    
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
   
		if (stat(buf, &st) < 0) {   //stat函数将buf现在的文件状态保存到st结构体变量中
			fprintf(2, "ERROR: cannot stat %s\n", buf);
		}
   
		switch (st.type) {    //判断buf现在的文件类型（是文件还是目录）
		case T_FILE:
			if (strcmp(target_file, de.name) == 0) {
				printf("%s\n", buf);
			}
			break;
		case T_DIR:
      //Don't recurse into "." and ".."
			if ((strcmp(de.name, ".") != 0) && (strcmp(de.name, "..") != 0)) {
        //Use recursion to allow find to descend into sub-directories.
				find(buf, target_file);
      }
		}	
	}

	close(fd);
	return;
}