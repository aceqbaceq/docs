#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main() {
    // Инициализируем системный журнал
    openlog("MyProgram", LOG_PID | LOG_CONS, LOG_USER);
    
    // Закрываем журнал
    closelog();

    return 0;
}


