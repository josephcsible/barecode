BITS 64
sub rsp, 8
mov rax, rdi
lea rsi, [rel .strdup]
xor edi, edi
call rax
lea rdi, [rel .helloworld]
call rax
mov edx, 14
add rsp, 8
ret
.strdup db "strdup", 0
.helloworld db `Hello, World!\n`, 0
