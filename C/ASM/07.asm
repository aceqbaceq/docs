section .data
    ; Строка аргумента
    arg db "Hello, World!", 0    ; Аргумент, который будет передан

section .bss
    ; Место для хранения указателей на аргументы (argv)
    argv resd 2                   ; Массив указателей (для argv[0], argv[1]).

section .text
    global _start

_start:
    ; Шаг 1: Подготовим массив argv
    ; argv[0] указывает на программу (это путь к исполнимому файлу).
    ; argv[1] указывает на строку "Hello, World!".
    
    ; Подготовим указатель на программу в argv[0]
    lea eax, [argv]           ; eax будет указывать на массив argv
    mov ebx, arg             ; Адрес строки "Hello, World!"
    mov [argv], ebx          ; argv[1] = адрес строки "Hello, World!"
    
    ; Шаг 2: Запускаем execve() с аргументами
    ; Указываем путь к исполнимому файлу (например, /bin/echo)
    ; Запускаем execve("/bin/echo", argv, envp)
    
    ; Загружаем адрес пути к исполнимому файлу (например, /bin/echo)
;    mov ebx, 0x68732f2f      ; Низкий 32 бита строки "/bin"
;    mov ecx, 0x6e69622f      ; Высокий 32 бита строки "/bin"

;0x6f000000  onull
;0x6863652f  /ech
;0x7273752f  /bin
;0x6e69622f  /usr
 
    push dword 0x6e69622f     ; /usr
    ;push ecx                 ; Строка "/bin" будет на стеке
    mov ebx, esp             ; Теперь ebx указывает на строку "/bin"

    ; Подготовим адрес для массива argv
    lea ecx, [argv]          ; ecx указывает на массив argv
    xor edx, edx             ; NULL для envp (переменные окружения)
    
    ; Системный вызов execve
    mov eax, 11              ; Номер системного вызова execve
    int 0x80                 ; Прерывание для системного вызова

    ; Если execve вернется, выводим ошибку
    mov eax, 1               ; Номер системного вызова для выхода
    xor ebx, ebx             ; Код ошибки 0
    int 0x80                 ; Выход


