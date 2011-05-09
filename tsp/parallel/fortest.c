# include<mpi.h>
# include<stdio.h>
# include<string.h>
# include<stdlib.h>

int arr0[5000][5000],arr1[5000][5000];
int pid,p;

int main(int argc, char *argv[])
{
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&p);
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);
  int i,j;
  double stime,etime;

  stime=MPI_Wtime();
  for(i=0;i<5000/p;i++)
    for(j=0;j<5000;j++)
      arr0[i][j]=arr1[i][j];
  etime=MPI_Wtime();
  if(pid==1)
    printf("Time in for  loop : %lf\n",etime-stime);
  MPI_Finalize();
  return 0;
}
