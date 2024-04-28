#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>



void memTest(long chunk, long total) {
    struct timeval prev, cur = {0,0}, lastProgress = {0,0};
    int i, j;
    int num = total / chunk;
    int p, progress = -1;
    uint8_t *data[num];

    get_now(&prev);

    for (i = 0; i < num; i++) {
        data[i] = malloc(chunk);
        for (j = 0; j < chunk; j += 4096) {
            data[i][j] = rand()%265;
        }

        get_now(&cur);
        add(delta(&prev, &cur));
        prev = cur;

        p = (i * 20) / num * 5;

        if (p != progress) {
            if (lastProgress.tv_sec == 0) {
                printf("%s: %02d%%\n", format(&cur), p);
            } else {
                double elapsed = delta(&lastProgress, &cur);
                printf("%s: %02d%% (%gms)\n", format(&cur), p, elapsed);
            }
            lastProgress = cur;
            progress = p;
        }
    }
}

