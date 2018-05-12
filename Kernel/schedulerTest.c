#include "schedulerTest.h"
//
// Created by juangod on 18/04/18.
//
process_t p1;
process_t p2;
process_t p3;
process_t p4;
process_t p5;
process_t p6;
process_t p10;
process_t t1;

void given3Processes(){
    p1 = malloc(sizeof(struct process_t_CDT));
    if(p1==NULL) perror("Malloc returned NULL.");
    p2 = malloc(sizeof(struct process_t_CDT));
    if(p2==NULL) perror("Malloc returned NULL.");
    p3 = malloc(sizeof(struct process_t_CDT));
    if(p3==NULL) perror("Malloc returned NULL.");

    p1->pid = 2;
    p2->pid = 2;
    p3->pid = 2;
    p1->sleeps=0;
    p2->sleeps=0;
    p3->sleeps=0;
}

void given3OtherProcesses(){
    p4 = malloc(sizeof(struct process_t_CDT));
    if(p4==NULL) perror("Malloc returned NULL.");
    p5 = malloc(sizeof(struct process_t_CDT));
    if(p5==NULL) perror("Malloc returned NULL.");
    p6 = malloc(sizeof(struct process_t_CDT));
    if(p6==NULL) perror("Malloc returned NULL.");

    p4->pid = 2;
    p5->pid = 2;
    p6->pid = 2;
    p4->sleeps=0;
    p5->sleeps=0;
    p6->sleeps=0;
}


void whenQueueing3Processes() {
    queueProcess(p1);
    queueProcess(p2);
    queueProcess(p3);
}

void whenQueueing3OtherProcesses() {
    queueProcess(p4);
    queueProcess(p5);
    queueProcess(p6);
}

void thenNNotNullProcessesAreReceived(int n){
    char okFlag=1;
    int i;
    for(i=0;i<n;i++) {
        t1 = getNextProcess();
        //printString("\n",0,0,0);
        //printInt(t1,0,255,0);
        //printString("\n",0,0,0);
        if (t1 == NULL)
            okFlag = 0;
    }

    if(okFlag)
        ok();
    else
        perror("Polled NULL process when non-null expected.");
}

void thenQueueIsEmpty(){
    if(getAmountOfProcesses()!=0)
        perror("Queue not empty when expected to be empty.");
    else
        ok();
}

void thenQueueIsNotEmpty(){
    if(getAmountOfProcesses()==0)
        perror("Queue is empty when expected to be not empty.");
    else
        ok();
}

void whenSleepingProcess10(){
    sleepProcess(10);
}

process_t thenNextProcessHasCertainPID(pid_t pid){
    t1 = getNextProcess();
    if(t1->pid != pid){
        fail("");
        printString("Expected PID: ",TB_FAIL,TG_FAIL,TR_FAIL);
        printInt(pid,TB_FAIL,TG_FAIL,TR_FAIL);
        printString(", Received: ",TB_FAIL,TG_FAIL,TR_FAIL);
        printInt(t1->pid,TB_FAIL,TG_FAIL,TR_FAIL);
        printString("\n",TB_FAIL,TG_FAIL,TR_FAIL);
        return t1;
    }
    else {
        ok();
        return t1;
    }
}

void givenAProcessWithPID10(){
    p10 = malloc(sizeof(struct process_t_CDT));
    if(p10==NULL) perror("Malloc returned NULL.");
    p10->pid = 10;
    p10->sleeps=0;
}

void whenQueueingProcessWithPID10(){
    queueProcess(p10);
}

void whenDestroyingQueue(){
    destroyProcessQueue();
}

void add3ProcessesTest(){
    printString("Testing 3 Processes Test\n",TB,TG,TR);

    given3Processes();

    whenQueueing3Processes();

    thenNNotNullProcessesAreReceived(3);
    thenQueueIsEmpty();

    freeProcessMemory(p1);
    freeProcessMemory(p2);
    freeProcessMemory(p3);
}

void checkSleepTest(){

    printString("Testing Sleep Test\n",TB,TG,TR);

    given3Processes();
    givenAProcessWithPID10();
    whenQueueingProcessWithPID10(); //p10 is queued first
    whenQueueing3Processes();
    whenSleepingProcess10();
    thenNextProcessHasCertainPID(2); // Default PID is 2, if it is 10 then the sleeping process was incorrectly returned
    thenNNotNullProcessesAreReceived(2);
    thenQueueIsNotEmpty();

    freeProcessMemory(p1);
    freeProcessMemory(p2);
    freeProcessMemory(p3);
    destroyProcessQueue();
}

void queueDestructionTest(){
    printString("Testing Queue Destruction Test\n",TB,TG,TR);

    givenAProcessWithPID10();
    given3OtherProcesses();
    given3Processes();
    whenQueueing3OtherProcesses();
    whenQueueing3Processes();
    whenQueueingProcessWithPID10();
    whenDestroyingQueue();
    thenQueueIsEmpty();
}

void given100QueuedProcesses(){
    int i = 0;
    for (i=0;i<100;i++){
        void * p = malloc(sizeof(struct process_t_CDT));
        if (p==NULL)
            perror("Malloc returned NULL.\n");
        queueProcess(p);
    }
}

void given2Processes(){
    given3Processes();
    freeProcessMemory(p3);
}

void whenQueueing2Processes(){
    queueProcess(p1);
    queueProcess(p2);
}

void sequentialQueueTest(){
    printString("Testing Sequential Queues Test\n",TB,TG,TR);

    given2Processes();
    whenQueueing2Processes();

    process_t t;
    int i;
    for(i=0;i<10;i++){
        t = thenNextProcessHasCertainPID(2);
        queueProcess(t);
    }

    whenDestroyingQueue();
    thenQueueIsEmpty();
}

void stressTest100Processes(){
    printString("Testing Stress Test\n",TB,TG,TR);

    given100QueuedProcesses();
    whenDestroyingQueue();
    thenQueueIsEmpty();
}

void schedulerTestRun(){
    add3ProcessesTest();
    checkSleepTest();
    queueDestructionTest();
    stressTest100Processes();
    //sequentialQueueTest();
}
