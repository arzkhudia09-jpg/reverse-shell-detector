#include <stdio.h>
#include "detector.h"
#include <string.h>

DetectionResult analyze_process(const ProcessInfo *process){
    DetectionResult result = {0};
    result.suspicious = false;
    result.risk_score = 0;
    strcpy(result.reason, "No suspicious behaviour detected.");
    bool rule_temp_dir = rule_temp_directory(process);
    bool rule_deleted_exe = rule_deleted_executable(process);
    if (rule_temp_dir){

        result.risk_score += 30;
        result.suspicious = true;
        strcpy(result.reason, "⚠️ Executable is running from a temporary directory.\nConfidence: 30%%");

    }

    if (rule_deleted_exe){

        result.suspicious = true;
        result.risk_score += 40;
        strcpy(result.reason, "⚠️ Running process points to a deleted executable..\nConfidence: 40%%");
    }

    return result;
}
