#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

// PUT YOUT SHELLCODE HERE! DO NOT FORGET THE LENGTH
unsigned int payload_len = 118;
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
