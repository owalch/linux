//*******************************************************************
// Author:	M. Thaler, ZHW
// Date:	11.12.2004
// Purpose:	helper applications to consume cpu time
//*******************************************************************

#ifndef WORKER_UTILS
#define WORKER_UTILS

void setRandom(void);

void justWork(unsigned load);

void workHard(unsigned low, unsigned high);

void randomSleep(unsigned low, unsigned high);

pid_t startWorker(void);

void stopWorker(pid_t worker);

#endif
