#include "Clock/headers.h"

/* Modify this file as needed*/
int turn_shmid; // to know if its their turn
int *turn_shmaddr;
int remainingtime;
int prev, curr;

void SIGCONThandler(int signum);
void sigtstphandler(int signum);

int main(int agrc, char *argv[])
{
  initClk();
  int runningtime = atoi(argv[1]);
  int arrivaltime = atoi(argv[2]);
  signal(SIGCONT, SIGCONThandler);

  // TODO it needs to get the remaining time from somewhere
  // remainingtime = ??;
  remainingtime = runningtime;
  printf("Starting process with ID = %d - Remaining time = %d - Started at time = %d\n", getpid(), remainingtime, getClk());

  prev = getClk();
  //  printf("Start run ID: %d at time: %d and rem time = %d\n", getpid(), getClk(), remainingtime);
  while (remainingtime > 0)
  {
    curr = getClk();
    if(curr != prev)
    {
      // printf("Process ID = %d prev = %d curr = %d\n", getpid(), prev, curr);
      if (curr > prev)
      {
        remainingtime--;
        printf("Process ID = %d - Remaining time = %d - Current time = %d\n", getpid(), remainingtime, getClk());
      }
      prev = getClk();
    }
  }
  printf("Process with pid = %d - Finish time = %d\n", getpid(), prev);
  prev = getClk();
  // kill(getppid(), SIGUSR1);
  kill(getppid(), SIGUSR2);
  destroyClk(false);
  raise(SIGTERM);

  return 0;
}

void SIGCONThandler(int signum)
{
  prev = curr = getClk();
}

void sigtstphandler(int signum)
{
  raise(SIGSTOP);
}