#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <threshold>\n", argv[0]);
        return 1;
    }

    double threshold = atof(argv[1]);
    #ifdef DEBUG
    printf("Threshold: %f\n", threshold);
    #endif

    struct statvfs s;
    statvfs("/", &s);
    #ifdef TEST
    printf("Simulating disk usage above threshold\n");
    s.f_bfree = threshold * s.f_blocks * 1.1;
    #endif

    ulong total = s.f_bsize * s.f_blocks;
    ulong free = s.f_bsize * s.f_bfree;

    #ifdef DEBUG
    printf("Total: %lu\n", total);
    printf("Free: %lu\n", free);
    #endif
    #ifdef TEST
    assert(total - free > threshold * total);
    #endif

    if ( total - free > threshold * total ) {
        #ifdef DEBUG
        printf("Free (%f) is above threshold absolute (%f)\n", total - free, threshold * total);
        printf("Logging to /var/log/disk_usage_alert.log\n");
        #endif
        FILE* out = fopen("/var/log/disk_usage_alert.log", "a");
        if (!out) {
            fprintf(stderr, "Failed to open log file\n");
            return 1;
        }

        time_t t = time(NULL);
        char* t_str = ctime(&t);
        // strip newline
        t_str[strlen(t_str) - 1] = '\0';

        fprintf(out, "[%s] Disk usage is above threshold: %f\n", t_str, threshold);

        fclose(out);
    }
}
