#ifndef UTILS
#define UTILS

#define INPUT_OK 0
#define INPUT_EMPTY 1
#define INPUT_TOO_LONG 2

unsigned int get_random_int(unsigned int min, unsigned int max);
int get_line(const char *prmpt, char *buff, size_t sz);

#endif
