; SPDX-License-Identifier: AGPL-3.0-or-later

BITS 32

push ebx
push ebp
push esi

mov ebx, [esp + 16] ; getProcAddress
mov ebp, [esp + 20] ; kernel32
call .eipToEsi
.gotEip:

lea edx, [esi + .LoadLibraryA - .gotEip]
push edx
push ebp ; kernel32
call ebx ; getProcAddress(kernel32, .LoadLibraryA)

lea edx, [esi + .User32dll - .gotEip]
push edx
call eax ; LoadLibraryA(.User32dll)

lea edx, [esi + .FreeLibrary - .gotEip]
push edx
push ebp ; kernel32
mov ebp, eax ; user32
call ebx ; getProcAddress(kernel32, .FreeLibrary)
mov ecx, ebx ; getProcAddress
mov ebx, eax ; FreeLibrary

lea edx, [esi + .MessageBoxA - .gotEip]
push edx
push ebp ; user32
call ecx ; getProcAddress(user32, .MessageBoxA)

push 0 ; uType
push 0 ; lpCaption
lea edx, [esi + .HelloWorld - .gotEip]
push edx
push 0 ; hWnd
call eax ; MessageBoxA(NULL, .HelloWorld, NULL, 0)

push ebp ; user32
call ebx ; FreeLibrary(user32)

xor eax, eax ; out.buf
xor edx, edx ; out.len
pop esi
pop ebp
pop ebx
ret

.eipToEsi:
mov esi, [esp]
ret

.HelloWorld db "Hello, World!", 0
.MessageBoxA db "MessageBoxA", 0
.User32dll db "User32.dll", 0
.FreeLibrary db "FreeLibrary", 0
.LoadLibraryA db "LoadLibraryA", 0
