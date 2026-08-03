#include <stdio.h>
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

bool rule_deleted_executable(const ProcessInfo *process){
    char searchString[] = "(deleted)";

    if (strstr(process->exe, searchString) != NULL){
        return true;
    }

    return false;
}

bool rule_parent_process(const ProcessInfo *process){
    const char *parent_name[] = {
        "python",
        "perl",
        "nc",
        "ncat",
        "socat",
        "bash",
        "sh"
    };

    size_t count_name = sizeof(parent_name)/sizeof(parent_name[0]);

    for (size_t i = 0; i < count_name; i++){
        if (strncmp(process->parent_process_name, parent_name[i], strlen(parent_name[i])) == 0){
            return true;
        }
    }
    
    return false;
}


bool rule_suspicious_name(const ProcessInfo *process){
    const char *suspicious_names[] = {
        "bash",
        "sh",
        "dash",
        "zsh",
        "python",
        "python3",
        "perl",
        "ruby",
        "lua",
        "php",
        "nc",
        "ncat",
        "netcat",
        "socat",
        "busybox",
        "curl",
        "wget"
    };

    size_t count_name = sizeof(suspicious_names)/sizeof(suspicious_names[0]);

    for (size_t i = 0; i < count_name; i++){
        if (strcmp(process->name, suspicious_names[i]) == 0){
            return true;
        }
    }
    
    return false;
}