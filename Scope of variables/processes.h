#ifndef PROCESS_H
#define PROCESS_H

extern int processescount;

struct Process{
  int ID;
  char name[30];
};

extern struct Process processes[5];

static int nextprocessid();

int createnewprocess(char *name);

int stopprocess(int number);

void printprocess();

#endif