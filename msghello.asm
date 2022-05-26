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

lea edx, [esi + .FreeLibrary - .gotEip]
push edx
push ebp ; kernel32
mov ebp, eax ; LoadLibraryA
call ebx ; getProcAddress(kernel32, .FreeLibrary)
mov ecx, ebp ; LoadLibraryA
mov ebp, eax ; FreeLibrary

lea edx, [esi + .User32dll - .gotEip]
push edx
call ecx ; LoadLibraryA(.User32dll)
mov ecx, ebx ; getProcAddress
mov ebx, eax ; user32

lea edx, [esi + .MessageBoxA - .gotEip]
push edx
push ebx ; user32
call ecx ; getProcAddress(user32, .MessageBoxA)

push 0 ; uType
push 0 ; lpCaption
lea edx, [esi + .HelloWorld - .gotEip]
push edx
push 0 ; hWnd
call eax ; MessageBoxA(NULL, .HelloWorld, NULL, 0)

push ebx ; user32
call ebp ; FreeLibrary(user32)

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
