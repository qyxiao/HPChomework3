

#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#include "util.h"


int main( int argc, char *argv[])
{
  int rank, tag, origin, destination;
  MPI_Status status;

  int round_Num=1;
  if(argc>=2){
    sscanf(argv[1], "%d", &round_Num);
  }

  

  MPI_Init(&argc, &argv);

  timestamp_type time1, time2;
  get_timestamp(&time1);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;     /* define threads used */
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  int count_round=0;

  int* message_out;
  int* message_in;
  tag = 99;
  int arrSize = 2000;  /* 524288 */
  
  while(count_round<round_Num){
    if(rank  == 0)
  {
    destination = rank + 1;
    origin = size - 1;
    
      count_round++;
      if(count_round==1){
        message_out = malloc(sizeof(int)*arrSize);
        int index=0; 
        for(index=0;index<arrSize;index++){
          message_out[index]=index;
          MPI_Send(message_out, arrSize, MPI_INT, destination, tag, MPI_COMM_WORLD);
        }
      }else{
        message_in = malloc(sizeof(int)*arrSize);
        MPI_Recv(message_in,  arrSize, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
        printf("At round %d the main thread receive message: %d\n", count_round, message_in[0]);
        message_in[0]=2;
        MPI_Send(message_in, arrSize, MPI_INT, destination, tag, MPI_COMM_WORLD);
      }   
  }
  else if(rank==size-1)
  {
    destination = 0;
    origin = rank -1;
    count_round++;
    message_in = malloc(sizeof(int)*arrSize);
    MPI_Recv(message_in,  arrSize, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
    MPI_Send(message_in, arrSize, MPI_INT, destination, tag, MPI_COMM_WORLD);
    printf("thread %d the output message is: %d\n", rank,message_in[rank]);
  }
  else
  {
    destination = rank +1;
    origin = rank -1;
    count_round++;
    message_in = malloc(sizeof(int)*arrSize);
    MPI_Recv(message_in, arrSize, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
    MPI_Send(message_in, arrSize, MPI_INT, destination, tag, MPI_COMM_WORLD);
    printf("thread %d the output message is: %d\n", rank, message_in[rank]);
  }
  
  }
  
  /*	
  printf("rank %d hosted on %s received from %d the message %d\n", rank, hostname, origin, message_in);
  */
  if(rank==0){
    get_timestamp(&time2);
    double elapsed = timestamp_diff_in_seconds(time1,time2);
    printf("Time elapsed is %f seconds.\n", elapsed);
  }

  MPI_Finalize();
  
  return 0;

}