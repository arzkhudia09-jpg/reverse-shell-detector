#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

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
        perror("Failed to open /proc/*/comm\n");
        return false;
    }
    char *result = fgets(buffer, size, fptr);
    if (result == NULL){
        printf("Something went wrong (EOF or read error)\n");
        fclose(fptr);
        return false;
    }
    char *newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
    
    fclose(fptr);
    printf("%s  ", buffer);
    return true;
}

bool read_exe(int pid, char *buffer, size_t size){
    char path[256];
    snprintf(path, sizeof(path),  "/proc/%d/exe", pid);
    ssize_t len = readlink(path, buffer, size);
    if (len == -1){
        perror("Failed to open /proc/*/exe\n");
        return false;
    }
    buffer[len] = '\0';
    printf("%s", buffer);
    return true;
}

int main(){

    DIR *dir = opendir("/proc/");
    if (dir == NULL){
        perror("Failed to open /proc/\n");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if (is_numeric(entry->d_name)){
            int PID = atoi(entry->d_name);
            printf("\nFound file: %d  ", PID);
            char comm_buffer[256];
            read_comm(PID, comm_buffer, sizeof(comm_buffer));
            char exe_buffer[256];
            read_exe(PID, exe_buffer, sizeof(exe_buffer) - 1);
        }
    }

    closedir(dir);

    return 0;
}