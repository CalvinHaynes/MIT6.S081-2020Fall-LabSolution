//
//Process-related system calls
//

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
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

uint64
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

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_trace(void)
{
  //读取user-space中trace调用中的mask参数，并将其存入当前进程的proc结构体中
  int n;
  if(argint(0, &n) < 0){
    return -1;
  }
  myproc()->syscallMask = n;
  
  return 0;
}

uint64
sys_sysinfo(void)
{
  uint64 u; // user pointer to struct sysinfo
  struct sysinfo s; // kernal计算sysinfo的临时变量, 利用copyout将这个再传递回user层
  struct proc *p = myproc();

  //取user层函数sysinfo的参数(sysinfo结构体指针)赋给p
  if(argaddr(0, &u) < 0)
    return -1;

  //统计计算sysinfo
  s.freemem = kfreemem_getamount();
  s.nproc = proc_gettotalnum();

  //sysinfo needs to copy a struct sysinfo back to user space
  if(copyout(p->pagetable, u, (char *)&s, sizeof(s)) < 0)
    return -1;
  
  return 0;
}