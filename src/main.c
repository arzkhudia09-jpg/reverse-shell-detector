#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "process.h"
#include "detector.h"


int main(){

    DIR *dir = opendir("/proc/");
    if (dir == NULL){
        perror("Failed to open /proc/\n");
        return 1;
    }


    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if (proc_is_numeric(entry->d_name)){
            int PID = atoi(entry->d_name);
            ProcessInfo process = {0};
            if (!load_process_info(PID, &process)){
                continue;
            }
            DetectionResult result = analyze_process(&process);

            printf("\n========================\n");
            printf("Found file: %d\n", PID);
            printf("Name: %s\n", process.name);
            printf("State: %s\n", process.state);
            printf("PID: %d\n", process.pid);
            printf("PPID: %d\n", process.ppid);
            printf("UID: %d\n", process.uid);
            printf("Threads: %d\n", process.threads);
            
            printf("Risk Score: %d\n", result.risk_score);
            printf("Suspicious %s\n", result.suspicious ? "Yes" : "No");
            printf("Reason\t: %s\n", result.reason);
            printf("========================\n");
        }
    }

    closedir(dir);

    return 0;
}