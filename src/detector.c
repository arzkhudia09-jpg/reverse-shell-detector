#include <stdio.h>
#include "detector.h"
#include <string.h>

DetectionResult analyze_process(const ProcessInfo *process){
    DetectionResult result = {0};
    result.suspicious = false;
    result.risk_score = 0;
    result.reason[0] = '\0';
    bool rule_temp_dir = rule_temp_directory(process);
    bool rule_deleted_exe = rule_deleted_executable(process);
    bool rule_parent = rule_parent_process(process);
    if (rule_temp_dir){

        result.risk_score += 30;
        result.suspicious = true;
        strcat(result.reason, "\n\t• ⚠️ Executable is running from a temporary directory.\nConfidence: 30%%");

    }

    if (rule_deleted_exe){

        result.suspicious = true;
        result.risk_score += 40;
        strcat(result.reason, "\n\t• ⚠️ Running process points to a deleted executable..\nConfidence: 40%%");
    }

    if (rule_parent){
        result.suspicious = true;
        result.risk_score += 20;
        strcat(result.reason, "\n\t• ⚠️ Running process points suspicious parent process.\nConfidence: 20%%");        
    }

    if (!result.suspicious){
            strcat(result.reason, "No Suspicious Behaviour is Detected.");
    }

    return result;
}
