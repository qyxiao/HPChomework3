

#include <stdio.h>
#include <unistd.h>
#include <mpi.h>



int main( int argc, char *argv[])
{
  int rank, tag, origin, destination;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;     /* define threads used */
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int round_Num=1;
  if(argc>=2){
  	sscanf(argv[1], "%d", &round_Num);
  }
  


  int message_out;
  int message_in;
  tag = 99;

  if(rank  == 0)
  {
    destination = rank + 1;
    origin = size - 1;
    message_out = 0;
    MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
    MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
    printf("At round %d the main thread receive message: %d\n", round_Num, message_in);
  }
  else if(rank<size-1)
  {
    destination = rank +1;
    origin = rank -1;
    
    MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
    message_out = message_in + rank;
    MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
    printf("thread %d the output message is: %d, message in is:%d\n", rank, message_out,message_in);
  }
  else
  {
  	destination = 0;
    origin = rank -1;
    
    MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
    message_out = message_in + rank;
    MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
    printf("thread %d the output message is: %d, message in is:%d\n", rank, message_out,message_in);
  }
  /*	
  printf("rank %d hosted on %s received from %d the message %d\n", rank, hostname, origin, message_in);
  */
  MPI_Finalize();
  return 0;

}