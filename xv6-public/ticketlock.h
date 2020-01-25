// Mutual exclusion lock.
struct ticketlock {
    uint locked;           // Is the lock held?
    struct spinlock lk;
    int ticket;
    int waited_Pid[50];  // Array Of Waited Process
    int pHead;            // Head Of The Queue
    int pTail;            // Tail Of The Queue

    // For debugging:
    char *name;        // Name of lock.
    int pid;          // The Process holding the lock.
};
