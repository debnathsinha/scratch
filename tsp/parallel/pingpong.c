# include<mpi.h>
# include<stdio.h>
# include<string.h>

int main(int argc, char *argv[])
{
  int numprocs;
  int myid;
  char idstr[32];
  char buff[128];
  int recv;
  MPI_Status stat;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  if(myid%2==0)
    {
      sprintf(buff,"ping from: %d",myid);
      MPI_Send(buff,128,MPI_CHAR,myid+1,0,MPI_COMM_WORLD);
      MPI_Recv(buff,128,MPI_CHAR,myid+1,0,MPI_COMM_WORLD,&stat);
      printf("%s\n",buff);
    }
  else
    {
      MPI_Recv(buff,128,MPI_CHAR,myid-1,0,MPI_COMM_WORLD,&stat);
      printf("%s\n",buff);
      sprintf(buff,"pong from %d",myid);
      MPI_Send(buff,128,MPI_CHAR,myid-1,0,MPI_COMM_WORLD);
    }
  MPI_Finalize();
  return 0;
}
