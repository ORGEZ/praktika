#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	pid_t pid;
	int fd[2];
	size_t flag, size;
	char stroka[100];
	if(pipe(fd)<0){
		printf("Can\'t create pipe\n");
		exit(-1);
	}
	switch (pid=fork()){
	case -1: printf("Some error happened\n");
	case 0:
		close(fd[0]);
		flag=execl("/tmp/ls","ls","-l", NULL);
		if(flag==-1){
			printf("ERROR\n");
			exit(-1);
		}
		close (fd[1]);
	default:
		close (fd[1]);
		size=read(fd[0], stroka, 100);
		printf("output string:%s\n", stroka);
		close (fd[0]);
	}
 return 0;
}
