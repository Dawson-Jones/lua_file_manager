#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "dirent.h"


extern int remove_file;
extern int remove_dir;
extern int rest;

static bool is_expired(const char *file_name, time_t timestamp, int mode) {
    time_t now;
    struct stat buf;

    if (stat(file_name, &buf)) {
        perror("get file info failed");
        exit(1);
    }

    time(&now);
    if (mode == 2)
        return now - buf.st_mtime > timestamp;
    else
        return now - buf.st_ctime > timestamp;
}

static unsigned int strcatf(char *dest, unsigned int tail, const char *src) {
    while (*src != '\0') {
        dest[tail++] = *src++;
    }
    dest[tail] = '\0';
    return tail;
}

unsigned int remove_expired_file(const char *base_path, time_t timestamp, int mode) {
    /*
     * mode:
     *  1: create date
     *  2: modify date
     */

    DIR *dir;
    struct dirent *ptr;
    char file_name[1000];
    unsigned int file_nums = 0;
    unsigned int file_name_len;

    if ((dir = opendir(base_path)) == NULL) {
        perror("open dir error...");
        exit(1);
    }

    while ((ptr = readdir(dir)) != NULL) {
        if (strcmp(ptr->d_name, "..") == 0 || strcmp(ptr->d_name, ".") == 0)  // current dir or parent dir
            continue;

        memset(file_name, '\0', 1000);
        file_name_len = strcatf(file_name, 0, base_path);
        file_name_len = strcatf(file_name, file_name_len, "/");
        strcatf(file_name, file_name_len, ptr->d_name);
        switch (ptr->d_type) {
            case 8:  // file
                // Determine whether the file is out of date
                if (is_expired(file_name, timestamp, mode)) {
                    remove(file_name);
                    remove_file++;
                } else {
                    file_nums++;
                }
                break;
            case 4:  // dir
                if (remove_expired_file(file_name, timestamp, mode) == 0) {
                    remove(file_name);
                    remove_dir++;
                }
                break;
            default:
                break;
        }
    }

    rest += file_nums;
    return file_nums;
}
