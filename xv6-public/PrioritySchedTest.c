#include "types.h"
#include "user.h"

int main(int argc, char const *argv[])
{
  const int fork_num = 25;
  const int N = 100;
  struct timeVariables time_variable[fork_num];
  int group_TT[5], group_CBT[5], group_WT[5];
  int sum_TT = 0, sum_CBT = 0, sum_WT = 0;
  float avg_TT = 0.0, avg_CBT = 0.0, avg_WT = 0.0;

  for(int i=0; i<5; i++)
  {
    group_TT[i] = 0;
    group_CBT[i] = 0;
    group_WT[i] = 0;
  }

  changePolicy(2);

  for(int i=0; i<fork_num; i++)
  {
    int f = fork();
    if(f == 0)
    {
      changePriority(5-i/5);

      for (int j=0; j<N; j++)
          printf(1,"[%d]: [%d]\n", i, j);
      exit();
    }
  }

  for(int i=0; i<fork_num; i++)
  {
    printf(1, "###########__Turnaround time, CBT, and Waiting time for all children__###########\n");
    printf(1,"%d\n",waitForChild(&time_variable[i]));

    // printf(1, "create: %d \t terminate: %d \t sleep: %d \t ready: %d \t running: %d\n",
    //         time_variable[i].creationTime, time_variable[i].terminationTime,
    //         time_variable[i].sleepingTime, time_variable[i].readyTime, time_variable[i].runningTime);

    printf(1, "Turnaround time: %d \t CBT: %d \t Waiting time: %d\n",
        (time_variable[i].terminationTime - time_variable[i].creationTime),
        time_variable[i].runningTime,
        (time_variable[i].terminationTime - time_variable[i].creationTime - time_variable[i].runningTime));

    group_TT[i/5] += time_variable[i].terminationTime - time_variable[i].creationTime;
    group_CBT[i/5] += time_variable[i].runningTime;
		group_WT[i/5] += time_variable[i].terminationTime - time_variable[i].creationTime - time_variable[i].runningTime;
    printf(1, "\n######################################################\n");
  }

  for (int i=0; i<5; i++)
  {
    printf(1, "#########__Avg_TT, Avg_CBT, and Ag_WT for each group with the same priority__#########\n");
    printf(1, "\nAverage Turnaround time: %f,  Average CBT: %f, Average Waiting time: %f\n",
                      group_TT[i]/5,           group_CBT[i]/5,      group_WT[i]/5);

    sum_TT += group_TT[i];
    sum_CBT += group_CBT[i];
    sum_WT += group_WT[i];
  }

  avg_TT = sum_TT/25.0;
  avg_CBT = sum_CBT/25.0;
  avg_WT = sum_WT/25.0;

  printf(1, "###########__Total Avg_TT, Avg_CBT, and Ag_WT__###########\n");
  printf(1, "\nAverage Turnaround time: %f,  Average CBT: %f, Average Waiting time: %f\n",
                      avg_TT,                   avg_CBT,              avg_WT);

  return 0;
}
