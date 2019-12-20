#include "types.h"
#include "user.h"

int main(int argc, char const *argv[]) {
  const int fork_num = 10;
  const int N = 10;
  struct timeVariables time_variable[fork_num];
  int sum_TT = 0, sum_CBT = 0, sum_WT = 0;
  float avg_TT = 0.0, avg_CBT = 0.0, avg_WT = 0.0;

  changePolicy(1);

  for (int i=0; i<fork_num; i++)
  {
      if (fork() == 0)
      {
          for (int j=0; j<N; j++)
             printf(1,"[%d]: [%d]\n", getpid(), j);
          exit();
      }
  }

  for(int i=0; i<fork_num; i++)
  {
    printf(1, "###########__Turnaround time, CBT, and Waiting time for all children__###########\n");
    printf(1, "child id: %d\n", waitForChild(&time_variable[i]));
    printf(1, "create: %d \t terminate: %d \t sleep: %d \t ready: %d \t running: %d\n",
            time_variable[i].creationTime, time_variable[i].terminationTime,
            time_variable[i].sleepingTime, time_variable[i].readyTime, time_variable[i].runningTime);

    printf(1, "Turnaround time: %d \t CBT: %d \t Waiting time: %d\n",
        (time_variable[i].terminationTime - time_variable[i].creationTime),
        time_variable[i].runningTime,
        (time_variable[i].terminationTime - time_variable[i].creationTime - time_variable[i].runningTime));

    sum_TT += time_variable[i].terminationTime - time_variable[i].creationTime;
    sum_CBT += time_variable[i].runningTime;
		sum_WT += time_variable[i].terminationTime - time_variable[i].creationTime - time_variable[i].runningTime;
  }

  // printf(1, "\nsum Turnaround time: %d, sum CBT: %d, sum Waiting time: %d\n", sum_TT, sum_CBT, sum_WT);

  avg_TT = sum_TT/10.0;
  avg_CBT = sum_CBT/10.0;
	avg_WT = sum_WT/10.0;

  printf(1, "###########__Total Avg_TT, Avg_CBT, and Ag_WT__###########\n");
  // printf(1, "\nAverage Turnaround time: %f,  Average CBT: %f, Average Waiting time: %f\n",
  //                     avg_TT,                   avg_CBT,              avg_WT);
  printf(1, "\nAverage Turnaround time: %f,  Average CBT: %f, Average Waiting time: %f\n",
                      avg_TT,                   avg_CBT,              avg_WT);

  return 0;
}
