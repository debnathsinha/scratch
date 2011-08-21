# include<stdio.h>
# include<mpi.h>

int myid,numprocs;
MPI_Status stat;
MPI_Request req;

int main(int argc, char *argv[])
{
  int anssend=2,mytime;
  double start,end;
  int i,bitv,mincost,t[3],mycost,flag;

  /*Initiating the MPI communication headers*/

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  if(myid==0)
    {
      for(i=0;i<2000000000;i++);
      printf("%lf\n",MPI_Wtime());
      for(i=0;i<10;i++)
	{
	  start=MPI_Wtime();
	  MPI_Iprobe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&flag,&stat);
	  end=MPI_Wtime();
	  printf("Time to probe: %lf\n",end-start);
	  if(flag==1)
	    {
	      printf("Received message\n");
	      flag=0;
	    }
	  else
	    {
	      printf("Cencelling message %d as it was not in time\n",i);
	      MPI_Cancel(&req);
	    }
	  stat.MPI_TAG=2;
	}
      for(i=0;i<2000000000;i++);
      printf("%d %d %d\n",anssend,stat.MPI_SOURCE,stat.MPI_TAG);
      MPI_Cancel(&req);
      MPI_Wait(&req,&stat);
      MPI_Cancel(&req);
      MPI_Test_cancelled(&stat,&flag);
      printf("flag:%d and ans:%d received at %lf\n",flag,anssend,MPI_Wtime());
    }
  else
    {
      anssend=32;
      for(i=0;i<10;i++)
	MPI_Send(&anssend,1,MPI_INT,0,23,MPI_COMM_WORLD);
      printf("Sent at time %lf\n",MPI_Wtime());
    }

}
