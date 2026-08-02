#include "rules.h"
#include <string.h>

bool rule_temp_directory(const ProcessInfo *process){

    const char *prefix[] = {
        "/tmp/",
        "/var/tmp/",
        "/dev/shm/"};

    size_t count_prefix = sizeof(prefix)/sizeof(prefix[0]);

    for (size_t i = 0; i < count_prefix; i++){
        if (strncmp(process->exe, prefix[i], strlen(prefix[i])) == 0){
                return true;
            }
    }
    
    return false;
}

