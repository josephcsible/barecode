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

## Copying

Load and run machine code without needing any header information
Copyright (C) 2022  Joseph C. Sible

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
