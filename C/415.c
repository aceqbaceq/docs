#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main() {
    // Инициализируем системный журнал
    openlog("415.exe", LOG_PID | LOG_CONS, LOG_USER);
    
    // Записываем сообщение в системный журнал
    syslog(LOG_INFO, "vasya");

    // Закрываем журнал
    closelog();

    return 0;
}


