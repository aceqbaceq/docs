        section .rodata
        ; strings
arg0     db "/usr/bin/echo",0
arg1     db "Hello",0
arg2     db "World",0
arg3     db "!!",0
arg4     db "YES",0



        ; arrays
        align 4
argv    dd arg0, arg1, arg2, arg3, arg4, 0
envp    dd 0

        section .text
        global _start
_start: mov eax, 11   ; SYS_execve
        mov ebx, arg0 ; filanem
        mov ecx, argv ; argv
        mov edx, envp ; envp
        int 0x80      ; syscall




