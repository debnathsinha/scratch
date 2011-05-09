# include<mpi.h>
# include<stdio.h>
# include<string.h>
# include<stdlib.h>

double arr[2][1000][1000];
int p;
int start,end;
int i,j,tempn;
int n=1000,pid;
double *t,*b;
double start_time,end_time;

int min(int a,int b)
{
  if(a<b)
    return a;
  else
    return b;
}


void above()
{
  int source,destn,i,j;
  double *val;
  MPI_Status stat;
  t=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  val=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  /*printf("Entered above");*/
  if(start==0)
    {
      
      for(i=0;i<n;i++)
	t[i]=0;
      for(i=0;i<n;i++)
	{
	  val[i]=arr[0][end-1][i];
	  /*printf("Sent %lf to %d\n",val[i],pid+1);*/
	}
      MPI_Send(val,n,MPI_DOUBLE,pid+1,0,MPI_COMM_WORLD);
      /*printf("Loop has been initialized for the first node\n");*/
    }
  else
    {
      MPI_Recv(t,n,MPI_DOUBLE,pid-1,0,MPI_COMM_WORLD,&stat);
      for(i=0;i<n;i++);
      /*printf("Received1 %lf from %d\n",t[i],pid-1);*/
      for(i=0;i<n;i++)
	{
	  val[i]=arr[0][end][i];
	  /*printf("Sent1 %lf to %d\n",val[i],pid+1);*/
	}
      if(end!=(n-1))
	MPI_Send(val,n,MPI_DOUBLE,pid+1,0,MPI_COMM_WORLD);
    }
}

void below()
{
  int source,destn,i,j;
  double *val;
  MPI_Status stat;
  b=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  val=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  /*printf("Entered below\n");*/
  if(end==(n-1))
    {

      for(i=0;i<n;i++)
        b[i]=1+(double)i/(n-1);
      for(i=0;i<n;i++)
        {
          val[i]=arr[0][start][i];
          /*printf("Sent21 %lf to %d start:%d pid:%d\n",val[i],pid-1,start,pid);*/
        }
      MPI_Send(val,n,MPI_DOUBLE,pid-1,0,MPI_COMM_WORLD);
      /*printf("Loop has been initialized for the last node\n");*/
    }
  else
    {
      MPI_Recv(b,n,MPI_DOUBLE,pid+1,0,MPI_COMM_WORLD,&stat);
      for(i=0;i<n;i++);
      /*printf("Received2 %lf from %d\n",b[i],pid+1);*/
      for(i=0;i<n;i++)
        {
          val[i]=arr[0][start][i];
          /*printf("Sent2 %lf to %d\n",val[i],pid-1);*/
        }
      if(start!=0)
        MPI_Send(val,n,MPI_DOUBLE,pid-1,0,MPI_COMM_WORLD);
      else;
      /*printf("Entered the start=0 condition for pid:%d\n",pid);*/
    }
}

void init()
{
  
  int i,j,flag=0;
  for(i=start;i<=end;i++)
    {
      printf("\npid:%d start:%d end:%d\n",pid,start,end);
    for(j=0;j<n;j++)
      {
	if(i==0)
	  {
	    arr[0][i][j]=0.0;
	    arr[1][i][j]=0.0;
	  }
	else if(i==n-1)
	  {
	    arr[0][i][j]=1+(double)j/(n-1);
	    arr[1][i][j]=1+(double)j/(n-1);
       
	  }
	else if(j==0)
	  {
	    arr[0][i][j]=(double)i/(n-1);
	    arr[1][i][j]=(double)i/(n-1);
	  }
	else if(j==(n-1))
	  {
	    arr[0][i][j]=2*(double)i/(n-1);
	    arr[1][i][j]=2*(double)i/(n-1);
	  
	  }
	else
	  {
	    arr[0][i][j]=0.5;
	    arr[1][i][j]=0.5;
	  }
	flag=0;
      }
    }
}


int main(int argc,char *argv[])
{  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&p);
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);

  int i,j,k,i1,j1;

  start_time=MPI_Wtime();

  if(pid==0)
    {
      printf("There are %d processors\n",p);
    }

  start= n/(p-1)*pid;
  end= min(start+p-2,n-1);
  init();
  printf(" Processor %d takes from %d to %d",pid,start,end);
  above();
  below();
  for(k=0;k<500;k++)
  {
    /*printf("iter : %d\n",k);*/
    above();
    below();
    for(i=start;i<=end;i++)
    {
      for(j=0;j<n;j++)
	{
	  
	  for(i1=0;i1<n;i1++)
	    for(j1=0;j1<n;j1++)
	      arr[0][i1][j1]=arr[1][i1][j1];
	  
	 }
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  printf("\n");
  /*for(i=start;i<=end;i++)
    {
      printf("\n");
      for(j=0;j<n;j++)
	printf("arr0:%lf arr1:%lf pid:%d\t",arr[0][i][j],arr[1][i][j],pid);
	}*/
  printf("\n");
  end_time=MPI_Wtime();
  if(pid==0)
    printf("\nTime taken is %lf",end_time-start_time);
  MPI_Finalize();
  return 0;
}


