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
sys_date(void){
     struct rtcdate *r;
    
    if(argptr(0, (void*)&r, sizeof(*r)) < 0){
      return -1;
    }
  else{
     
    cmostime(r);         
    return 0;
  }
}


int
sys_pgtPrint(void){
   struct proc* curpoc=myproc();

   //get page directory's pointer for current process
   pde_t* pgdir=curpoc->pgdir;

  int w=1;
  int k=0;
   
  pte_t* prev=0;
  for (uint va = 0,i=0; va <KERNBASE; va=va+PGSIZE,i++)
   {

       pte_t* pgt=(pte_t*)P2V(PTE_ADDR(pgdir[PDX(va)]));//get the virtual address of the i'th page entry in page directory 
       //check the present bit AND USER BIT
       
       if((pgt) &&(*pgt & PTE_P) &&(*pgt & PTE_U)){

        if (i!=0 && prev!=pgt)
        {
            w=w+1;
        }
               //CHECK THE PRESENT BIT AND USER BIT
                if((pgt[PTX(va)] & PTE_P )&& (pgt[PTX(va)] & PTE_U) ){

                  uint pa = PTE_ADDR(pgt[PTX(va)]);//GET THE PHYSICAL ADDRESS OF THE PAGE ENTRY IN THE PAGE TABLE
     
          
                   cprintf("Entry number: %d , Virtual Address : 0x%x ,Physical address: 0x%x \n",i,va,pa);
                
                   k=k+1;
                }
            
           }
          prev=pgt;
          
   
   }
    cprintf("\nNo of valid pages : %d\n",k);
    cprintf("No of invalid pages where it is valid page directory entry: %d\n",(w)*NPTENTRIES-k);
    cprintf("No of valid page directory entries : %d\n",w);
    cprintf("No of invalid page directory entries: %d\n\n",NPDENTRIES-w);

return 0;

}