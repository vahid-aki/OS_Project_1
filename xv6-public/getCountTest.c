#include "types.h"
#include "user.h"

int main(int argc, char const *argv[])
{
  int index = atoi(argv[1]);
  int n1 = fork();
  int n2 = fork();
  sleep(1);
  sleep(1);

  if (n1 > 0 && n2 > 0) {
    wait();
    printf(1,"#######__getCount__#######\n");
    printf(1,"index: %d   getcount = %d \n", index, getCount(index));
  }
  exit();
}
