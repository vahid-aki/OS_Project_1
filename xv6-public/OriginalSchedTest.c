#include "types.h"
#include "user.h"

int main(int argc, char const *argv[]) {
  const int fork_num = 10;
  const int N = 10;
  struct timeVariables time_variable[fork_num];

  for (int i=0; i<fork_num; i++)
  {
      if (fork() == 0)
      {
          for (int j=0; j<N; j++)
             printf(1,"[%d]: [%d]\n", getpid(), j);
          exit();
      }
      else
      {
        printf(1, "child id: %d\n", waitForChild(&time_variable[i]));
        printf(1, "create: %d \t terminate: %d \t sleep: %d \t ready: %d \t running: %d\n",
                time_variable[i].creationTime, time_variable[i].terminationTime,
                time_variable[i].sleepingTime, time_variable[i].readyTime, time_variable[i].runningTime);

        printf(1, "TT: %d \t WT: %d \t CBT: %d\n",
            (time_variable[i].terminationTime - time_variable[i].creationTime),
            (time_variable[i].terminationTime - time_variable[i].creationTime - time_variable[i].runningTime),
            time_variable[i].runningTime);
      }
  }

  return 0;
}
