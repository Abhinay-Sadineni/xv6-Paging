#include "types.h"
#include "user.h"
#include "date.h"
#define N  1000
//use atleast 2000000 to 5000000 to get more directory entries
int arrGlobal[N];
int main(int argc, char *argv[])
{
  //some arrays and small code to stop warnings such uinitilized variables
    int arrLocal1[N];
    int arrLocal2[N];
    int arrLocal3[N];
    for (int i = 0; i < 10; i++)
    { 
        arrLocal3[i]=arrLocal2[i]=i;
        arrLocal1[i]=arrGlobal[i]=i+arrLocal3[i];
        arrLocal3[i+1]=arrLocal2[i]%10+arrLocal1[i];
    }
    
    //system call pgtPrint
    pgtPrint();

  exit();
}
