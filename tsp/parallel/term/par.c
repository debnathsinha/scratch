# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<stdlib.h>
# include<string.h>

int myid, numprocs;
#define n 14
int adj[n][n];
int queue[50000][3];
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
  for(i=count-1;i>=0;i--)
	printf("%c",str[i]);
}

double min(double a, double b)
{
  if(a<b)
    return a;
  else
    return b;
}

int * pop()
{
  int arr[3]={-1,-1,-1};
  if (size()>=0)
    return queue[rear++];
  else
    return arr;
}
void push(int a, int b, int c)
{
  queue[front][0]=a;
  queue[front][1]=b;
  queue[front][2]=c;
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
  if(bitv==0)
    return adj[city][snode];
  
  val=0;
  for(i=0;i<n;i++)
    {
      
      if(bitv&(1<<i))
	{
	  val=adj[city][i];
	  val+=dfs(i,bitv-(1<<i));
	  best=min(best,val);
	}
    }
  return best;
}

void bfs(int start, int bitv, int cost)
{
  int i,val,j,newcost;
  int *t;
  int best=1000000;

  push(snode,bitv,0);

  while(size()>0 && size()<15000)
    {
      t=pop();
      /*printf("Popped out %d %d %d and the current size is %d\n",t[0],t[1],t[2],size());*/
      if(t[1]==0)
        {
          /*printf(" newcost:%d addcost:%d\n",newcost,adj[t[0]][snode]);
	    printf("All nodes have been visited; original cost:%d I am at %d and final cost:%d\n",t[2],t[1],t[2]+adj[t[0]][snode]);*/
          best=min(best,t[2]+adj[t[0]][snode]);
        }
      else
      for(i=0;i<n;i++)
	{
	  if(t[1]&(1<<i))
	    {
	      /*printf("Going from %d to %d and cost:%d and inherited cost:%d\n",t[0],i,adj[t[0]][i],t[2]);
	      int2bit(t[1]-(1<<i));
	      printf("\n");*/
	      newcost=adj[t[0]][i]+t[2];
	      /*printf("The new cost after traversing from %d to %d through %d id %d\n",snode,i,t[0],newcost);*/
	      push(i,(t[1]-(1<<i)),newcost);
	    }/*
	  else if(t[1]==0)
	    {
	      printf("All nodes are now visited and original cost:%d and I am at %dand final cost:%d\n",t[2],t[0],newcost+adj[i][snode]);
	      best=min(best,newcost+adj[t[0]][snode]);
	      }*/
	}
      /*if(t[1]==0)
	{
	  printf(" newcost:%d addcost:%d\n",newcost,adj[t[0]][snode]);
	  printf("All nodes have been visited; original cost:%d I am at %d and final cost:%d\n",t[2],t[1],newcost+adj[t[0]][snode]);
	  best=min(best,newcost+adj[t[0]][snode]);
	  }*/
    }
  while(size()>0)
    {
      t=pop();
      newcost=t[2]+dfs(t[0],t[1]);
      best=min(best,newcost);
    }
  printf("The minimum cost through bfs is %d\n",best);
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
  if(myid==0)
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
  int i,bitv,mincost,n1=n;

  /*Initiating the MPI communication headers*/

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  printf("The number of processors is %d and the size of the problem is %d\n",numprocs,n1);

  start=MPI_Wtime();

  init_adj();

  bitv=(1<<n)-2;
  int2bit(bitv);
  printf("\n");
  start=MPI_Wtime();
  mincost=dfs(snode,bitv);
  end=MPI_Wtime();
  printf("\nThe minimum cost through dfs is %d and the time taken was %lf\n",mincost,end-start);
  
  start=MPI_Wtime();
  bfs(snode,bitv,0);
  end=MPI_Wtime();
  printf("The minimum coast through bfs is %d and the time is %lf\n",mincost,end-start);

  end=MPI_Wtime();
}
