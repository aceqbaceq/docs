section .data
    msg db 'Value: ', 0x00   ; Сообщение для вывода (строка с нулевым символом в конце)
  ; Время сна: 60 секунд и 0 наносекунд
    timespec dd 60, 0  ; 60 секунд, 0 наносекунд

section .bss
    num resb 4               ; Резервируем 4 байта для числа (не инициализировано)

section .text
    global _start            ; Точка входа в программу

_start:
    ; Сохраняем текущие значения регистров и настраиваем стек
    push    ebp              ; Сохраняем указатель базы стека
    mov     ebp, esp         ; Настроим указатель стека на новый фрейм

    ; Выделяем память для локальной переменной (4 байта)
    sub     esp, 2           ; Выделяем 4 байта для локальной переменной

    ; Присваиваем значение локальной переменной
    mov     word [ebp-2], 0x0A4E  ; Присваиваем значение 123 локальной переменной

    ; Загружаем значение локальной переменной в eax для использования
    ;mov     eax, [ebp-4]     ; Загружаем значение локальной переменной в eax

    ; Печатаем сообщение "Value: "
    mov     eax, 4           ; Системный вызов sys_write (4)
    mov     ebx, 1           ; Дескриптор файла stdout (1)
    mov     ecx, msg         ; Адрес строки
    mov     edx, 7           ; Длина строки "Value: "
    int     0x80             ; Вызов системного вызова

    ; Печатаем число из стека
    mov     eax, 4           ; Системный вызов sys_write (4)
    mov     ebx, 1           ; Дескриптор файла stdout (1)
    lea     ecx, ebp-2       ; Адрес памяти для вывода числа
;    mov  word   [ecx], 0x0A4E   ; Сохраняем число в памяти для вывода
    mov     edx, 2           ; Длина данных (4 байта)
    int     0x80             ; Вызов системного вызова

    ; 
    lea ecx, num ;
    mov     dword [ecx],   0x68736173 ;
    mov     word  [ecx+4], 0x0a61;
;    mov dword [ecx+8], 0x68730a00;
    mov     eax, 4           ; Системный вызов sys_write (4)
    mov     ebx, 1           ; Дескриптор файла stdout (1)
    mov     edx, 6          ; Длина данных (4 байта)
    int     0x80             ; Вызов системного вызова

   ;   
   sub     esp, 21               ;
   mov     byte [esp],    0x73   ;
   mov     byte [esp+1],  0x68   ; 
   mov     byte [esp+2],  0x6c   ;
   mov     byte [esp+3],  0x61   ;
   mov     byte [esp+4],  0x20   ;
   mov     byte [esp+5],  0x73   ;
   mov     byte [esp+6],  0x61   ;
   mov     byte [esp+7],  0x73   ;
   mov     byte [esp+8],  0x68   ;
   mov     byte [esp+9],  0x61   ;
   mov     byte [esp+10], 0x20   ;
   mov     byte [esp+11], 0x70   ;
   mov     byte [esp+12], 0x6f   ;
   mov     byte [esp+13], 0x20   ;
   mov     byte [esp+14], 0x73   ;
   mov     byte [esp+15], 0x68   ;
   mov     byte [esp+16], 0x6f   ;
   mov     byte [esp+17], 0x73    ;
   mov     byte [esp+18], 0x73    ;
   mov     byte [esp+19], 0x65    ;
   mov     byte [esp+20], 0x0a    ;
   
   mov     eax, 4           ; Системный вызов sys_write (4)
   mov     ebx, 1           ; Дескриптор файла stdout (1)
   lea     ecx, [esp]       ;
   mov     edx, 21          ; Длина данных (4 байта)
   int     0x80             ; Вызов системного вызова


 ; Указание на аргументы для nanosleep
    mov ebx, timespec   ; Адрес структуры timespec (первый аргумент)
    xor ecx, ecx        ; Второй аргумент — NULL (пустой указатель)

    ; Системный вызов nanosleep
    mov eax, 162         ; Номер системного вызова nanosleep (для 32-битных систем)
    int 0x80             ; Вызов системного вызова через прерывание


  
    ; Восстанавливаем указатель стека
    add     esp, 23          ; Восстанавливаем значение esp

    ; Восстанавливаем старое значение ebp
    pop     ebp              ; Восстанавливаем значение ebp из стека


    ; Завершаем программу
    mov     eax, 1           ; Системный вызов sys_exit (1)
    xor     ebx, ebx         ; Код возврата 0
    int     0x80             ; Вызов системного вызова


