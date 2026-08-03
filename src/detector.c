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
    bool rule_parent_name = rule_parent_process(process);
    bool rule_suspicious_process = rule_suspicious_name(process);

    if (rule_temp_dir){

        result.risk_score += 30;
        result.suspicious = true;
        strcat(result.reason, "• ⚠️ Executable is running from a temporary directory.\nConfidence: 30%%\n\t");

    }

    if (rule_deleted_exe){

        result.suspicious = true;
        result.risk_score += 40;
        strcat(result.reason, "• ⚠️ Running process points to a deleted executable..\nConfidence: 40%%\n\t");
    }

    if (rule_parent_name){
        result.suspicious = true;
        result.risk_score += 20;
        strcat(result.reason, "• ⚠️ Running process points suspicious parent process.\nConfidence: 20%%\n\t");        
    }

    if (rule_suspicious_process){
        result.suspicious = true;
        result.risk_score += 10;
        strcat(result.reason, "• Suspicious executable name.\nConfidence: 10%%\n\t");        
    }

    if (!result.suspicious){
            strcat(result.reason, "No Suspicious Behaviour is Detected.");
    }

    return result;
}
