# include<mpi.h>
# include<stdio.h>
# include<string.h>

int main(int argc, char *argv[])
{
  char idstr[32];
  char buff[128];
  int numprocs;
  int myid;
  int i;
  MPI_Status stat;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  
  if(myid==0){
    printf("We have %d processors\n",numprocs);
  }
  printf("My processor id is : %d\n",myid);
  MPI_Finalize();
  return 0;
}
