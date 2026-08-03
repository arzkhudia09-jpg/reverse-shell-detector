#ifndef DETECTOR_H
#define DETECTOR_H

#include <stdbool.h>
#include "process.h"
#include "rules.h"


typedef struct {
    bool suspicious;
    int risk_score;
    char reason[512];
} DetectionResult;

DetectionResult analyze_process(const ProcessInfo *process);


#endif