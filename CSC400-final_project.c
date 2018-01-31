/*
##################################
##		CPU Scheduler v0.1		##
##		Josiah Anderson			##
##		Duane Michael			##
##################################
*/

#include <stdio.h>

// process struct

typedef struct process
{
	int order;
	int burst;
	int priority;
	int wait;
	int turnaround;
};

// function prototypes

int GetScheduler();
int GetProcess();
void GetBurst(process procs[], int num_proc);
void GetPriority(process procs[], int num_proc);
void ShortestJobFirst(process procs[], int num_proc);
void PrioritySched(process procs[], int num_proc);
void DisplayAvgWaiting(process procs[], int num_proc);
void DisplayAvgTurnaround(process procs[], int num_proc);
void DisplayGantt(process procs[], int num_proc);


int main()
{
	bool cont = true;
	
	while(cont)
	{
		int schedType = GetScheduler();
		int numProc = GetProcess();   
		process user_processes[numProc];	// create number of processes user defines
	
		for(int i=0; i < numProc; i++)	// initialize all struct values to zero
		{
			user_processes[i].order = i + 1;	// original order from 1 to numProc-1
			user_processes[i].burst = 0;
			user_processes[i].priority = 0;
			user_processes[i].wait = 0;
			user_processes[i].turnaround = 0;
		}
	
		GetBurst(user_processes, numProc);
   
		switch(schedType)
		{
			case 0:
				ShortestJobFirst(user_processes, numProc);  // call SJF scheduler
				break;

			case 1:
				GetPriority(user_processes, numProc);
				PrioritySched(user_processes, numProc);  // call Priority scheduler
				break;

			default:
				printf("Please enter a valid scheduler choice.\n");
				break;
		}
   
		DisplayGantt(user_processes, numProc);
		DisplayAvgWaiting(user_processes, numProc);
		DisplayAvgTurnaround(user_processes, numProc);
		
		char input;
		printf("\n\nContinue? (Y/N): ");
		scanf(" %c", &input);
		
		switch(input)
		{
			case 'Y':
				cont = true;
				break;
			case 'N':
				cont = false;
				break;
			default:
				printf("\nInvalid selection\n");
				cont = false;
				break;
		}
		printf("\n\n");
	}

	return 0;
}



int GetScheduler()
{
   int scheduler = -1;

   printf("Enter your scheduler preference (0 for SJF, 1 for Priority): ");
   scanf(" %d", &scheduler);
   
   return scheduler;
}

int GetProcess()
{
   int proc = 0;

   printf("\nEnter the number of processes to schedule: ");
   scanf(" %d", &proc);
   
   return proc;
}

void GetBurst(process procs[], int num_proc)
{
   printf("\nEnter the burst times for each process: ");
   for(int i=0; i < num_proc; i++)
   {
		scanf(" %d", &procs[i].burst);
   }
}

void GetPriority(process procs[], int num_proc)
{         
   printf("\nEnter the priority for each process (1-5): ");
   for(int i=0; i < num_proc; i++)
   {
		scanf(" %d", &procs[i].priority);
   }
}

void ShortestJobFirst(process procs[], int num_proc)
{
	process temp;	// Local variable used to swap structs

	for(int i=0; i < num_proc; i++)
	{
		for(int i=0; i < num_proc; i++)
		{
			// If procs[i].burst is greater than procs[i+1].burst, swap structs
			if(procs[i].burst > procs[i+1].burst)
			{
				temp = procs[i];
				procs[i] = procs[i+1];
				procs[i+1] = temp;
			}
		}
	}
    
}

void PrioritySched(process procs[], int num_proc)
{
	process temp;	// Local variable used to swap structs

	for(int i=0; i < num_proc; i++)
	{
		for(int i=0; i < num_proc; i++)
		{
			// If procs[i].priority is greater than procs[i+1].priority, swap structs
			if(procs[i].priority > procs[i+1].priority)
			{
				temp = procs[i];
				procs[i] = procs[i+1];
				procs[i+1] = temp;
			}
		}
	}
	
}

void DisplayAvgWaiting(process procs[], int num_proc)
{
	int wait_counter = 0;
	
	for(int i=0; i < num_proc; i++)		// assign each process a wait time based on scheduler ordering
	{
		if(wait_counter == 0)
			procs[i].wait = wait_counter;
			
		wait_counter += procs[i].burst;
		procs[i].wait = wait_counter;
	}

	for(int i=0; i < num_proc; i++)		// assign each process a turnaround time based on wait/burst
	{		
		procs[i].turnaround = procs[i].wait + procs[i].burst;
	}
	
	wait_counter = 0;
		
	printf("\nAverage wait time for all processes: ");
	
    for(int i=0; i < num_proc; i++)
		wait_counter += procs[i].wait;
		
	printf("%d\n", (wait_counter / num_proc));
}

void DisplayAvgTurnaround(process procs[], int num_proc)
{
	int turnaround_counter = 0;
	
	printf("\nAverage turnaround time for all processes: ");
	
    for(int i=0; i < num_proc; i++)
		turnaround_counter += procs[i].turnaround;
		
	printf("%d\n", (turnaround_counter / num_proc));
}

void DisplayGantt(process procs[], int num_proc)
{
	int burst_counter = 0;
	
	printf("\n\n");
	for(int i=0; i < num_proc; i++)
		printf("   P%d   ", procs[i].order);		// display original process order
	
	printf("\n");
	
	for(int i=1; i <= num_proc; i++)
	{
		printf("[      ]");
	}
	
	printf("\n");
	printf("0");		// starting time on Gantt chart is always zero
	printf("\t");
	
	for(int i=1; i <= num_proc; i++)
	{
		burst_counter += procs[i-1].burst;
		printf("%d      ", burst_counter);
	}
	printf("\n\n");
}
