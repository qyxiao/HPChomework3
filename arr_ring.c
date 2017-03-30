

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
  message_out = malloc(sizeof(int)*arrSize);
  message_in = malloc(sizeof(int)*arrSize); 
  
  while(count_round<round_Num){
    if(rank  == 0)
  {
    destination = rank + 1;
    origin = size - 1;
     
      if(count_round==0){
        int index=0; 
        for(index=0;index<arrSize;index++){
          message_out[index]=index;
        }
      }else{
        message_out = message_in;
      }
        MPI_Send(message_out, arrSize, MPI_INT, destination, tag, MPI_COMM_WORLD);
        MPI_Recv(message_in,  arrSize, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
        count_round++;
        printf("At round %d array is received\n", count_round);
        /*message_in[0]=2;*/
        
      
      
      if(count_round>=round_Num){
        FILE* fd = NULL;
        char filename[256];
        snprintf(filename, 256, "output%02d.txt", count_round);
        fd = fopen(filename,"w+");
        int n;
        for(n = 0; n < arrSize; ++n)
          fprintf(fd, "  %d\n", message_in[n]);

        fclose(fd);
        printf("Array received at the end is stored in output%02d.txt\n", count_round);
      }   
  }
  else if(rank==size-1)
  {
    destination = 0;
    origin = rank -1;
    count_round++;
    MPI_Recv(message_in,  arrSize, MPI_INT, origin, tag, MPI_COMM_WORLD, &status);
    MPI_Send(message_in, arrSize, MPI_INT, destination, tag, MPI_COMM_WORLD);
    
  }
  else
  {
    destination = rank +1;
    origin = rank -1;
    count_round++;
    MPI_Recv(message_in, arrSize, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
    MPI_Send(message_in, arrSize, MPI_INT, destination, tag, MPI_COMM_WORLD);
    
  }
  
  }
  
  free(message_in);

  

  MPI_Finalize();
  
  return 0;

}