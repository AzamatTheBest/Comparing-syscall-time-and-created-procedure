#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

/*
`````````````````````````````````````````
This little program calculates how musch more 
expensive is a system call than a 
procedure call. 
`````````````````````````````````````````
*/

int foo()
{
	return 10;
}

long nanosec (struct timeval t) /* Calculate nanoseconds in a timeval structure */ 
{
	return (t.tv_sec*1000000 + t.tv_usec) * 1000;	
}

int main()
{
	int i, j, res;
	long N_iterations = 1000000; /* A million iterations */
	float avgTimeSysCall, avgTimeProcCall;
	struct timeval t1, t2;

	/* Find average time of System Call */
	res = gettimeofday(&t1, NULL); 
	assert(res == 0);

	for (i = 0; i < N_iterations; i++)
		j = getpid();

	res = gettimeofday(&t2, NULL); 
	assert(res == 0);

	avgTimeSysCall = (nanosec(t2) - nanosec(t1))/(N_iterations * 1.0);

	/* Find average time of Procedure Call  */
	res = gettimeofday(&t1 , NULL);
	assert(res == 0);
	
	for (i = 0; i < N_iterations; i++)
		j = foo();
	
	res = gettimeofday(&t2, NULL);
	assert(res == 0);

	avgTimeProcCall = (nanosec(t2) - nanosec(t1))/(N_iterations * 1.0);
	
	printf("Average time for System Call getpid(): => %f\n", avgTimeSysCall);
	printf("Average time for Function call: => %f\n", avgTimeProcCall);
}
