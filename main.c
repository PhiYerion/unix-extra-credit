#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <threshold>\n", argv[0]);
        return 1;
    }

    double threshold = atof(argv[1]);

    struct statvfs s;
    statvfs("/", &s);
    ulong total = s.f_bsize * s.f_blocks;
    ulong free = s.f_bsize * s.f_bfree;

    if ( total - free > threshold * total ) {
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
