#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	pid_t pid;
	int fd[2];
	size_t size;
	char stroka[14];
	if(pipe(fd)<0){
		printf("Can\'t create pipe\n");
		exit(-1);
	}
	switch (pid=fork()){
	case -1: printf("Some error happened\n");
	case 0:
		printf("input string:");
		close(fd[0]);
		gets (stroka);
		size = write(fd[1],stroka,14);
		if(size != 14){
			printf("Can\'t write all string\n");
			exit(-1);
		}
		close (fd[1]);
	default:
		close (fd[1]);
		size=read(fd[0], stroka,14);
		if (size!=14){
			printf("Can\'t read strings\n");
			exit(-1);
		}
		printf("parrent process %d\n", getpid());
		printf("output string:%s\n", stroka);
		close (fd[0]);
	}
 return 0;
}
