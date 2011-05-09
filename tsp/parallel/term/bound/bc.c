# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<malloc.h>

int myid, numprocs;
MPI_Status stat;
MPI_Request req;

int lgfn()
{
  
}

int main(int argc, char *argv[])
{
  double start,end,rsend=100,bcid=0;
  int count1=0,count2=100,ask,flag,i,recv=23,i1,i2=2,j;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  if(myid==0)
    printf("Number of processors %d\n",numprocs);
  ask=myid;
  start=MPI_Wtime();
  if(myid==bcid)
    {
      for(i=1;i<2;i++)
	{
	  /*MPI_Send(&i,1,MPI_INT,i,23,MPI_COMM_WORLD);
	  rsend=200;
	  i1=1;
	  i2=2;
	  MPI_Send(&i1,1,MPI_INT,i,23,MPI_COMM_WORLD);
	  start=MPI_Wtime();
	  for(j=0;j<1000000000;j++);
	  end=MPI_Wtime();
	  printf("Delay : %lf\n",end-start);
	  MPI_Send(&i2,1,MPI_INT,i,23,MPI_COMM_WORLD);
	  */
	  for(i=0;i<10;i++)
	    {
	      MPI_Send(&i,1,MPI_INT,1,23,MPI_COMM_WORLD);
	      for(j=0;j<100000000;j++);
	      printf("Sending:%d\n",i);
	    }
	}
    }
  else
    {
      /*MPI_Iprobe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&flag,&stat);
      printf("flag:%d\n",flag);
      printf("Probe speaking:I received %d from %d\n",stat.MPI_TAG,stat.MPI_SOURCE);
      MPI_Recv(&i,1,MPI_INT,0,23,MPI_COMM_WORLD,&stat);
      printf("Receiving %d from %d : I am %d speaking and count2 is %d\n",count1,stat.MPI_SOURCE,myid,count2);
      MPI_Irecv(&i1,1,MPI_INT,0,23,MPI_COMM_WORLD,&req);
      MPI_Recv(&i1,1,MPI_INT,0,23,MPI_COMM_WORLD,&stat);
      printf("%d says the values are %d %d\n",myid,i1,i2);
      */
      for(i=0;i<1000000000;i++);
      MPI_Iprobe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&flag,&stat);
      printf("Receive implemented %d\n",stat.MPI_ERROR);
      
      for(i=0;i<1;i++)
	{
	  MPI_Iprobe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&flag,&stat);
	  printf("flag:%d\n",flag);
	  MPI_Recv(&i1,1,MPI_INT,0,23,MPI_COMM_WORLD,&stat);
	  printf("Receiving:%d \n",i1);
	}
      
    }
  MPI_Finalize();
}
