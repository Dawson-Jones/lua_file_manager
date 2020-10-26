#include <time.h>

unsigned int remove_file = 0;
unsigned int remove_dir = 0;
unsigned int rest = 0;

extern unsigned int remove_expired_file(const char *base_path, time_t timestamp, int mode);