; SPDX-License-Identifier: AGPL-3.0-or-later

BITS 64
push qword [rsi]
mov rax, rdi
lea rsi, [rel .strlen]
xor edi, edi
call rax
mov rdi, [rsp]
call rax
mov rdx, rax
pop rax
ret
.strlen db "strlen", 0
