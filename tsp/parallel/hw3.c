# include<mpi.h>
# include<stdio.h>
# include<string.h>
# include<math.h>

char idstr[32];
char buff[128];
int numprocs=4;
int myid,pid=2;
int i,j,p,tempn,n,starti,startj,endi,endj;
int row,col,st_row,st_col;
int stime,etime,proctime;
double arr[10][10];
MPI_Status stat;


void init();
void above();
void below();
void left();
void right();
void topleft();
void topright();

int max(int a,int b)
{
  if(a>b)
    return a;
  else
    return b;
}

int min(int a, int b)
{
  if(a<b)
    return a;
  else
    return b;
}

int main(int argc, char *argv[])
{
  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);

  int i,j;
  
  p=sqrt((double)numprocs);    

  row=(pid/p);
  col=pid%p;

  st_row = row*n/p;
  st_col = col*n/p;

  int iter;
  

  
  stime=MPI_Wtime();
  n=10;
  tempn=n-1;
  starti=1+(int)tempn/p*(int)(pid/p);
  startj=1+pid%(int)p*(int)tempn/p;
  endi=min(starti+(n-1)/p-1,n-2);
  endj=min(startj+(n-1)/p-1,n-2);
  printf("\n%d %d %d %d\n",starti,startj,endi,endj);
  
  init(starti,startj,endi,endj);
  for(iter=0;iter<2;iter++);
    
  for(i=starti;i<endi;i++)
    {
      for(j=startj;j<endj;j++)
	printf("%lf \t",arr[i][j]);
      printf("\n");
    }
  
  
  etime=MPI_Wtime();
  if(pid==0)
    {
      proctime=stime-etime;
      printf("Root says the time is : %f",proctime);
    }
  MPI_Finalize();
  return 0;
}


void init()
{
  int i,j;
  for(i=starti;i<endi;i++)
    for(j=startj;j<endj;j++)
      {
	if(i==0)
	  arr[i][j]=0.0;
	else if(i==n-1)
	  arr[i][j]=1+j/(n-1);
	else if(j==0)
	  arr[i][j]=i/(n-1);
	else if(j==(n-1))
	  arr[i][j]=2*i/(n-1);
	else
	  arr[i][j]=0.5;
      }
}
   
void top()
{

  /*If the processor has the top part of the array*/
  if(starti==1)
    {
      /*Compute top elements*/
    }
  else
    {
      /*Receive the elements*/
    }
}

void bottom()
{
  if(endi==n-1)
    {
      /*Compute the bottom elements*/
    }
  else
    {
      /*Receive the botton elemets of the array*/
    }
}

void left()
{
  if(startj==1)
    {
      /*Compute the left elements*/
    }
  else
    {
      /*Receive the left elements*/
    }
}

void right()
{
  if(endj==n-1)
    {
      /*Compute right*/
    }
  else
    {
      /*Receive the right element*/
    }
}
