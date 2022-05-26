# barecode

Instructions to try:

1. `gcc prependlength.c -o prependlength`
2. `gcc barecode.c -ldl -o barecode`
3. `(nasm -f bin donothing.asm -o /dev/stdout | ./prependlength; ./prependlength < /dev/null ) | ./barecode`
4. `(nasm -f bin outhello.asm -o /dev/stdout | ./prependlength; ./prependlength < /dev/null ) | ./barecode`
5. `nasm -f bin exechello.asm -o /dev/stdout | ./prependlength | ./barecode`
6. `(nasm -f bin outhello.asm -o /dev/stdout | ./prependlength; nasm -f bin exechello.asm -o /dev/stdout | ./prependlength ) | ./barecode`
7. `(nasm -f bin savehello.asm -o /dev/stdout | ./prependlength; nasm -f bin loadout.asm -o /dev/stdout | ./prependlength; ./prependlength < /dev/null ) | ./barecode`

Or if you're on Windows:

1. `vcvarsall.bat x86`
2. `cl prependlength.c`
3. `cl barecode.c`
4. `nasm -f bin msghello.asm`
5. `(prependlength < msghello & prependlength < nul) | barecode`
