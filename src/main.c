#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    char name[64];
    char exe[256];
    char state[32];
    int pid;
    int ppid;
    int uid;
    int threads;
} ProcessInfo;

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
    return true;
}

bool read_exe(int pid, char *buffer, size_t size){
    char path[256];
    snprintf(path, sizeof(path),  "/proc/%d/exe", pid);
    ssize_t len = readlink(path, buffer, size - 1);
    if (len == -1){
        buffer[0] = '\0';
        return false;
    }

    buffer[len] = '\0';
    return true;
}

bool read_status(int PID, ProcessInfo *process){
    char path[256];
    snprintf(path, sizeof(path),  "/proc/%d/status", PID);
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL){
        perror("Failed to open /proc/*/status\n");
        return false;
    }
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fptr) != NULL){
        if (buffer[0] == '\0' || buffer[0] == '#'){
            continue;
        }
        if (sscanf(buffer, "State:\t%31[^\n]", process->state) == 1){
        }
        if (sscanf(buffer, "Pid: %d", &process->pid) == 1){
        }
        if (sscanf(buffer, "PPid: %d", &process->ppid) == 1){
        }
        if (sscanf(buffer, "Uid: %d", &process->uid) == 1){
        }
        if (sscanf(buffer, "Threads: %d", &process->threads) == 1){
        }
    }
    
    fclose(fptr);
    return true;
}

bool load_process_info(int pid, ProcessInfo *process){
    if (!read_comm(pid, process->name, sizeof(process->name))){
        return false;
    }
    if (!read_exe(pid, process->exe, sizeof(process->exe))){
        return false;
    }
    read_status(pid, process);
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
            ProcessInfo process = {0};
            if (!load_process_info(PID, &process)){
                continue;
            }
            printf("\n========================\n");
            printf("Found file: %d\n", PID);
            printf("Name: %s\n", process.name);
            printf("State: %s\n", process.state);
            printf("PID: %d\n", process.pid);
            printf("PPID: %d\n", process.ppid);
            printf("UID: %d\n", process.uid);
            printf("Threads: %d\n", process.threads);
            printf("========================\n");
        }
    }

    closedir(dir);

    return 0;
}