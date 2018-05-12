//
// Created by juangod on 18/04/18.
//

#ifndef TP2_TEMPORARY_SCHEDULERTEST_H
#define TP2_TEMPORARY_SCHEDULERTEST_H

#include "process.h"
#include "scheduler.h"
#include "testLib.h"
#include "videoDriver.h"
#include "memorymanager.h"
#include "processQueue.h"

void given3Processes();

void whenPollingAProcess();

void then3NotNullProcessesArePolled();

void add3ProcessesTest();

void schedulerTestRun();
#endif //TP2_TEMPORARY_SCHEDULERTEST_H
