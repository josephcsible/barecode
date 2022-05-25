BITS 64
mov rax, rdi
xor edi, edi
push rdi
lea rsi, [rel .environ]
call rax
mov rdx, [rax]
lea rsi, [rel .argv1]
push rsi
lea rsi, [rel .argv0]
push rsi
mov rsi, rsp
lea rdi, [rel .pathname]
mov eax, 59
syscall
mov edi, 1
mov eax, 60
syscall
.environ db "environ", 0
.pathname db "/bin/"
.argv0 db "echo", 0
.argv1 db "Hello, World!", 0
