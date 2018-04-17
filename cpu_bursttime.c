#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct process{
  int rt;
  bool status;
}proc[5];

int int_arr[100],count=0,bt[5];

void readFromFile(){
  int fd,sz;
  char *c = (char *) calloc(1000, sizeof(char));
  const char delm[2]="\n";
  const char delm1[2]=" ";
  char *split;
  char *split2;
  fd = open("CPU_BURST.txt", O_RDONLY);
  sz = read(fd, c, 100);
  split=strtok(c,delm);
  split2=strtok(split,delm1);

  while( split2 != NULL ) {
      int_arr[count]=atoi(split2);
      count++;
      split2 = strtok(NULL, delm1);
   }
}

 void getBurstTime(){
   for(int i,j=0;i<=count;i++){
     if(int_arr[i]>0){
       bt[j]=int_arr[i];
       j++;
     }
     if(j>5){
       break;
     }
   }
 }
void schedulerSJF()
{
  int processCount=0;
  for(int i=0;i<5;i++){
    proc[i].status=false;
  }
  for(int i=0;i<5;i++){
    proc[i].rt=bt[i];
  }
  int minRT,sj=0;
  while(processCount!=5){
    int minRT=100000;
    for(int i=0;i<5;i++){
      if(minRT>proc[i].rt&&proc[i].status!=true){
        minRT=proc[i].rt;
        sj=i;
      }
    }
      if(minRT>0)
      proc[sj].rt--;
      if(proc[sj].rt==0){
      proc[sj].status=true;
      printf("\nProcess %d exited",sj+1);
      processCount++;
      }

  }
}

int main()
{
readFromFile();
getBurstTime();
printf("_____________________________________SCHEDULER___________________________________");
printf("\n\t\tBurst Time\t\tArrival Time");
for(int i=0;i<5;i++){
  printf("\n Process %d \t\t %d \t\t 0",i+1,bt[i]);
}
printf("\n");
schedulerSJF();
}
