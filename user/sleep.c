#include "kernel/types.h"
#include "user/user.h"
   
int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(2, "ERROR: sleep time required\n");
		exit(1);
	}
	sleep(atoi(argv[1])); // atoi把字符串转化为int
	exit(0);
}
