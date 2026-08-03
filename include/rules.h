#ifndef RULES_H
#define RULES_H

#include <stdbool.h>
#include "process.h"

bool rule_temp_directory(const ProcessInfo *process);
bool rule_deleted_executable(const ProcessInfo *process);
bool rule_parent_process(const ProcessInfo *process);

#endif