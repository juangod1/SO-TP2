#include "include/process.h"

void freeProcessMemory(process_t process) {
    free(process);
}
