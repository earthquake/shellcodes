/*
Linux shellcode executer. Reserving RWX memory and running shellcode
from there.
Balazs Bucsay
@xoreipeip | earthquake <at@> rycon <do.t> hu  
http://rycon.hu
no error handling. just for testing purposes
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

// PUT YOUT SHELLCODE HERE! DO NOT FORGET THE LENGTH
unsigned int payload_len = ;
char *payload = ""

int main(int argc, char *argv[])
{
	void *addr = NULL;

	addr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	memcpy(addr, payload, sizeof(char)*payload_len);
	void (*shellcode)(int) = addr;
	(*shellcode)(123);

	return 0;
}
