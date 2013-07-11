# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<stdlib.h>
# include<string.h>

int myid, numprocs;
#define n 16
int cache[n][(1<<n)];
int adj[n][n];
double queue[100][4];
int snode=0;
int front,rear;
double ans;

void int2bit(int num)
{
  if(num==0)printf("0000");
  char str[40];
  int count=0,i;
  while(num!=0)
  {
      str[count++]=num%2+'0';
      num/=2;
  }
  str[count]=0;
  for(i=count-1;i>=0;i--);
	/*printf("%c",str[i]);*/
}

double min(double a, double b)
{
  if(a<b)
    return a;
  else
    return b;
}

double * pop()
{
  double arr[4]={-1,-1,-1,-1};
  if (size()>=0)
    return queue[rear++];
  else
    return arr;
}
void push(double a, double b, double c, double d)
{
  queue[front][0]=a;
  queue[front][1]=b;
  queue[front][2]=c;
  queue[front][3]=d;
  front++;
}

int size()
{
  return front-rear;
}


int dfs(int city,int bitv)
{
  int i;
  static int count;
  int val,best=100000;
  if(cache[city][bitv]!=0)return cache[city][bitv];
  if(bitv==0)
    {
     /* printf("There are no more nodes to visit and the cost from going from %d to %d is %d\n",city,snode,adj[city][snode]);*/
      return cache[city][bitv]=adj[city][snode];
    }
  
  val=0;
  for(i=0;i<n;i++)
    {
      
      if(bitv&(1<<i))
	{
	  val=adj[city][i];
	  /*printf("Cost of going from city (%d) to i(%d) is %d\n",city,i,adj[city][i]);*/
	  val+=dfs(i,bitv-(1<<i));
	  /*printf("Cost of going from %d to %d through %d is val:%d\n",city,snode,i,val);
		*/
      best=min(best,val);
	}
    }
/*  printf("The minimum cost of going from %d  thro ",city);*/
  int2bit(bitv);
  /*printf(" is %d\n",best);*/
  return cache[city][bitv]=best;
  /*ans+=best;*/
}

void init_adj()
{
  int i,j;
  for(i=0;i<n;i++)
    for(j=i;j<n;j++)
      adj[i][j]=(int)(((double)rand()/((double)RAND_MAX+1))*100+1);
  for(i=0;i<n;i++)
    for(j=0;j<i;j++)
      adj[i][j]=adj[j][i];
  for(i=0;i<n;i++)
    {
      printf("\n");
      for(j=0;j<n;j++)
	printf("%d:%d\t",adj[i][j],myid);
    }
}

int main(int argc, char *argv[])
{
  double anssend,mytime;
  double start,end;
  int i,bitv,mincost;

  /*Initiating the MPI communication headers*/

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  start=MPI_Wtime();

  init_adj();

  bitv=(1<<n)-2;
  int2bit(bitv);
 	printf("\n"); 
  mincost=dfs(snode,bitv);
  printf("The minimum cost is %d\n",mincost);

  end=MPI_Wtime();
  if(myid==0)
    printf("Number of processors %d and the time is %lf\n",numprocs,end-start);
}