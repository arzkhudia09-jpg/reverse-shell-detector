#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>
#include <stdbool.h>

typedef struct{
    char name[64];
    char exe[256];
    char state[32];
    int pid;
    int ppid;
    int uid;
    int threads;
} ProcessInfo;

bool proc_is_numeric(const char *name);
bool proc_read_comm(int pid, char *buffer, size_t size);
bool proc_read_exe(int pid, char *buffer, size_t size);
bool proc_read_status(int PID, ProcessInfo *process);
bool load_process_info(int pid, ProcessInfo *process);

#endif
