; SPDX-License-Identifier: AGPL-3.0-or-later

BITS 64
push rsi
mov rax, rdi
lea rsi, [rel .strdup]
xor edi, edi
call rax
lea rdi, [rel .helloworld]
call rax
pop rsi
mov [rsi], rax
xor eax, eax
xor edx, edx
ret
.strdup db "strdup", 0
.helloworld db `Hello, World!\n`, 0
