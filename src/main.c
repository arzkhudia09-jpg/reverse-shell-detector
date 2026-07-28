#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

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

int main(){

    DIR *dir = opendir("/proc");
    if (dir == NULL){
        perror("Failed to open /proc");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if (is_numeric(entry->d_name)){
            printf("Found file: %s\n", entry->d_name);
        }
    }

    closedir(dir);

    return 0;
};