#include<mpi.h>
#include<string.h>
#include<stdio.h>

int sendtag,recvtag;

int main(int argc, char *argv[])
{
  int numprocs;
  int myid;
  int buff;
  int recv;
  MPI_Status stat;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  printf("Number of processors %d\n",numprocs);
  if(myid%2==0)
    {
      printf("Hi in even processor %d \n",myid);
      buff=2*myid;
      printf("%d is my [ %d ] buffer\n",buff,myid);
      if(myid!=(numprocs-1))
      MPI_Send(&buff,128,MPI_INT,myid+1,1,MPI_COMM_WORLD);
      printf("I sent %d to %d \n",buff,myid+1);
      /*MPI_Barrier(MPI_COMM_WORLD);*/
      /*printf("sent the message in even proc%d\n",myid);*/
      if(myid==(numprocs-1))
	printf("You were wrong, I am even : %d\n",myid);
      if(myid!=(numprocs-1))
	MPI_Recv(&buff,128,MPI_INT,myid+1,2,MPI_COMM_WORLD,&stat);
      printf("I ( %d ) received %d\n",myid,buff);
      /*MPI_Barrier(MPI_COMM_WORLD);*/
    }
  else
    {
      printf("Hi in odd processor %d\n",myid);
      MPI_Recv(&buff,128,MPI_INT,myid-1,1,MPI_COMM_WORLD,&stat);
      /*MPI_Barrier(MPI_COMM_WORLD);*/
      printf("I {%d} received in %d \n",myid,buff);
      buff=2*myid;
      MPI_Send(&buff,128,MPI_INT,myid-1,2,MPI_COMM_WORLD);
      printf("I { %d  }sent the message in %d\n",myid,buff);
    }
  MPI_Finalize();
  return 0;
}
