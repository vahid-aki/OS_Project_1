#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getppid(void) {
  return getppid(myproc());
}

int
sys_getChildren(void) {
  int parent_id;
  if(argint(0,&parent_id) < 0)
    return -1;
  return getChildren(parent_id);
}

int
sys_getCount(void) {
  int index;
  if (argint(0,&index) < 0)
    return -1;
  return getCount(index);
}

int
sys_changePriority(void) {
  int priority_num;
  if(argint(0,&priority_num) < 0)
    return -1;
  if(priority_num > 5 || priority_num < 1)
    return -1;
  myproc()->priority = priority_num;
    return 0;
}

int
sys_changePolicy(void) {
  int policy_num;
  if(argint(0,&policy_num) < 0)
    return -1;
  if(policy_num > 2 || policy_num < 0)
    return -1;

  changeTrapPolicy(policy_num);
  return changePolicy(policy_num);
}

int
sys_waitForChild(void)
{
  struct timeVariables *time_variable;
  if (argptr(0, (void*)&time_variable, sizeof(*time_variable)) < 0)
    return -1;
  return waitForChild(time_variable);
}
