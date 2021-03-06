#include "types.h"
#include "user.h"
#include "param.h"


int main(int argc, char const *argv[]) {
  const int fork_num = 10;
  const int N = 1000;
  struct timeVariables time_variable[fork_num];
  int sum_TT = 0, sum_CBT = 0, sum_WT = 0;
  int avg_TT = 0, avg_CBT = 0, avg_WT = 0;
  int pid[fork_num];

  changePolicy(1);

  for (int i=0; i<fork_num; i++)
    if (fork() == 0)
      {
          for (int j=0; j<N; j++)
             printf(1,"[%d]: [%d]\n", getpid(), j);
          exit();
      }

  for (int i=0; i<fork_num; i++)
    pid[i] = waitForChild(&time_variable[i]);

  printf(1, "\n_______________________________________________________________________________________");
  printf(1, "\n#######################################################################################");
  printf(1, "\n####################################__QUANTUM= %d__####################################", QUANTUM);
  printf(1, "\n#######################################################################################\n");

  for(int i=0; i<fork_num; i++)
  {
    // printf(1, "###########__Turnaround time, CBT, and Waiting time for all children__###########\n");QUANTUM
    printf(1, "\n\t--------------------\tProcess: %d \t--------------------\n", i);
    printf(1, "ID: %d\n", pid[i]);
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

  avg_TT = sum_TT/10;
  avg_CBT = sum_CBT/10;
	avg_WT = sum_WT/10;

  printf(1, "\n");
  printf(1, "\n");
  printf(1, "#########################__Total Avg_TT, Avg_CBT, and Avg_WT__#########################\n");
  // printf(1, "\nAverage Turnaround time: %f,  Average CBT: %f, Average Waiting time: %f\n",
  //                     avg_TT,                   avg_CBT,              avg_WT);
  printf(1, "\nAverage Turnaround time: %d, \t Average CBT: %d, \t Average Waiting time: %d\n",
                      avg_TT,                    avg_CBT,               avg_WT);

  printf(1, "\n");
  printf(1, "\n");
  return 0;
}
