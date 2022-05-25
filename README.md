# barecode

Instructions to try:

1. `gcc prependlength.c -o prependlength`
2. `gcc barecode.c -ldl -o barecode`
3. `(nasm -f bin donothing.asm -o /dev/stdout | ./prependlength; true | ./prependlength ) | ./barecode`
4. `(nasm -f bin outhello.asm -o /dev/stdout | ./prependlength; true | ./prependlength ) | ./barecode`
5. `nasm -f bin exechello.asm -o /dev/stdout | ./prependlength | ./barecode`
6. `(nasm -f bin outhello.asm -o /dev/stdout | ./prependlength; nasm -f bin exechello.asm -o /dev/stdout | ./prependlength ) | ./barecode`
