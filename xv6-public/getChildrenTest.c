#include "types.h"
#include "user.h"

int main (void) {
  int n1 = fork();

  int n2 = fork();

  int n3 = fork();

  int n4 = fork();

  if (n1 > 0 && n2 > 0 && n3 > 0 && n4 > 0) {
      printf(1,"#######__parent__#######\n");
      printf(1,"   getchildren = %d \n", getChildren(getpid()));
  }
  exit();
}
