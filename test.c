/*
	Name: Abhimanyu Gupta
	Roll_Number: 2019226
	
	Assignment 3
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

double performTask(long loopLimit)
{
	struct timeval tStart,tEnd;
	gettimeofday(&tStart,NULL);
	for(long i=0;i<loopLimit;i++);
	gettimeofday(&tEnd,NULL);		
	double executionTime=(tEnd.tv_sec-tStart.tv_sec)+(tEnd.tv_usec-tStart.tv_usec)/1000000.0;
	return executionTime;
}

int main()
{
	long loopLimit=100000000;
	pid_t pid=fork();
	if(pid<0)
		printf("Error while creating another process\n");
	else if(pid==0)
	{
		double factor=100;
		long realtime=loopLimit*factor; // in ns
		long returnCode=syscall(550,(int)getpid(),realtime);
		if(returnCode==1)
		{
			printf("Something went wrong while making system call to modify rt_nice, check kernel log for exact information\n");
			return 0;
		}
		double executionTime=performTask(loopLimit);
		printf("PID- %d, Time with rt_nice modified: \"%lf\" seconds\n",(int)getpid(),executionTime);
	}
	else
	{
		double executionTime=performTask(loopLimit);	
		printf("PID- %d, Time without rt_nice modified: \"%lf\" seconds\n",(int)getpid(),executionTime);
		waitpid(pid,NULL,0);
	}
	
	return 0;

}
