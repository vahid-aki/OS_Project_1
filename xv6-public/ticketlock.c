// Mutual exclusion Ticket locks.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "ticketlock.h"

void
initTicketlock(struct ticketlock *lk, char *name)
{
    initlock(&lk->lk, "ticket lock");
    lk->name = name;
    lk->locked = 0;
    lk->pid = 0;
    lk->ticket = 0;
    lk->pHead = -1;
    lk->pTail = 0;
}

// Acquire the lock.
void
acquireTicketlock(struct ticketlock *lk)
{
    acquire(&lk->lk);
    if (lk->locked)
    {
        lk->waited_Pid[lk->pTail] = myproc()->pid;
        fetch_and_add(&lk->pTail, 1);
    }

    fetch_and_add(&lk->ticket, 1);

    if (lk->pTail == 50)
        lk->pTail = 0;

    while (lk->locked)
        sleep(lk, &lk->lk);

    lk->locked = 1;
    lk->pid = myproc()->pid;
    release(&lk->lk);
}

// Release the lock.
void
releaseTicketlock(struct ticketlock *lk)
{
    acquire(&lk->lk);
    lk->locked = 0;
    lk->pid = 0;

    fetch_and_add(&lk->pHead, 1);

    if(lk->pHead == 50)
        lk->pHead = 0;

    if (lk->pHead == lk->pTail)
    {
        lk->pHead = -1;
        lk->pTail = 0;
    }

    wakeupTicketlock(lk->waited_Pid[lk->pHead]);
    release(&lk->lk);
}
