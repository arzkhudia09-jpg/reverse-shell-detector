#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_numeric(const char *name){
    if (name == NULL){
        return false;
    }
    while (*name != '\0'){
        if (!isdigit(*name)){
            return false;
        }
        name++;
    };

    return true;
}

bool read_comm(int pid, char *buffer, size_t size){
    char path[256];
    snprintf(path, sizeof(path),  "/proc/%d/comm", pid);
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL){
        perror("Failed to open /proc/");
        return false;
    }
    fgets(buffer, size, fptr);
    fclose(fptr);
    printf("%s", buffer);
    return true;
}

int main(){

    DIR *dir = opendir("/proc/");
    if (dir == NULL){
        perror("Failed to open /proc/");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if (is_numeric(entry->d_name)){
            int PID = atoi(entry->d_name);
            printf("Found file: %d\n", PID);
            char comm_buffer[256];
            read_comm(PID, comm_buffer, 256);
        }
    }

    closedir(dir);

    return 0;
};