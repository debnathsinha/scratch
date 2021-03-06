# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<stdlib.h>
# include<string.h>

int myid, numprocs;
#define n 23
int adj[n][n];
int cache[n][(1<<n)];
int queue[50000][3];
int snode=0,k=200;
int front,rear;
double ans;
MPI_Status stat;

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
  static int count,count1;
  int val,best=100000;

  if(cache[city][bitv]!=0)return cache[city][bitv];

  if(bitv==0)
    return cache[city][bitv]=adj[city][snode];
  
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
  return cache[city][bitv]=best;
}

void bfs(int start, int bitv, int cost)
{
  int i,val,j,newcost,count1;
  int *t;
  int best=1000000,nsend,pid;
  int arr[3]={-1,-1,-1};

  push(snode,bitv,0);

  while(size()>0 && size()<k)
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
	      /*printf("The new cost after traversing from %d to %d through %d id %d\n",snode,i,t[0],newcost);
	      int2bit(t[1]-(1<<i));
	      printf("\n");*/
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
  /*for(i=rear;i<front;i++)
    {
      printf(" %d %d %d are the %d th elements in the queue\n",queue[i][0],queue[i][1],queue[i][2],i);
      int2bit(queue[i][1]);
      printf("\n");
      }*/  
  /*printf("This is unbelievable but this is the size: %d\n",size());*/
  nsend=0;
  while(size()>0)
    {
      t=pop();
      newcost=0;
      /*printf("Root have popped out %d %d %d\n",t[0],t[1],t[2]);
      int2bit(t[1]);
      printf("\n");
      newcost=t[2]+dfs(t[0],t[1]);
      /*Sending to each of the workers*/
      count1++;
      count1=(count1%(numprocs-1))+1;
      /*printf("I am sending %d %d %d to %d and the new size of the queue is %d\n",t[0],t[1],t[2],count1,size());*/
      MPI_Send(t,3,MPI_INT,count1,0,MPI_COMM_WORLD);
      nsend++;
      
    }
  /*printf("I hope nsend %d matches above\n",nsend);*/
  for(i=1;i<numprocs;i++)
    {
      /*printf("Root is sending -1 to %d\n",i);*/
      MPI_Send(arr,3,MPI_INT,i,0,MPI_COMM_WORLD);
      
    }
  /*printf("And now I the root does all the receiving\n");*/
  for(count1=nsend;count1>0;count1--)
    {
      MPI_Recv(&pid,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&stat);
      MPI_Recv(&newcost,1,MPI_INT,pid,0,MPI_COMM_WORLD,&stat);
      /*printf("Root received %d from %d and count1:%d\n",newcost,pid,count1);*/
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
  int i,bitv,mincost,t[3],mycost;

  /*Initiating the MPI communication headers*/

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  start=MPI_Wtime();

  init_adj();
  printf("\n");

  bitv=(1<<n)-2;
  /*int2bit(bitv);
  printf("\n");*/
  /*if(myid==0)
    {
      start=MPI_Wtime();
      mincost=dfs(snode,bitv);
      end=MPI_Wtime();
      printf("\nThe minimum cost through dfs is %d and the time taken was %lf\n",mincost,end-start);
    }
  */
  start=MPI_Wtime();
  if(myid==0)
    {
      start=MPI_Wtime();
      bfs(snode,bitv,0);
      end=MPI_Wtime();
      printf("The time taken for the bfs was %lf",end-start);
    }
  else
    {
      MPI_Recv(t,3,MPI_INT,0,0,MPI_COMM_WORLD,&stat);
      while(t[0]!=-1 || t[1]!=-1 || t[2]!=-1)
	{
	  /*printf("%d received %d %d %d from root\n",myid,t[0],t[1],t[2]);
	  /*int2bit(t[1]);
	    printf("\n");*/
	  mycost=0;
	  mycost=dfs(t[0],t[1]);
	  /*printf("%d\n",dfs(6,8124));
	    printf("PROCESSOR %d SAYS ITS DFS GIVES %d where t[0]:%d and t[1]:%d\n",myid,mycost,t[0],t[1]);*/
	  mycost=t[2]+ mycost;
	  /*int2bit(t[1]);
	    printf("\n");*/
	  /*printf("%d am sending %d to root where t[2]:%d and dfs subprob:%d\n",myid,mycost,t[2],mycost-t[2]);*/
	  MPI_Send(&myid,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  MPI_Send(&mycost,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  MPI_Recv(t,3,MPI_INT,0,0,MPI_COMM_WORLD,&stat);
	}
      if(t[0]==-1 || t[1]==-1 || t[2]==-1)
	{
	  /*mycost=-1;
	  MPI_Send(&myid,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  MPI_Send(&mycost,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  */
	  printf(" %d received -1 from root......%d is now going to sleep!!\n",myid,myid);
	  }
    }
  end=MPI_Wtime();
  /*printf("The minimum coast through bfs is %d and the time is %lf\n",mincost,end-start);
   */
  end=MPI_Wtime();
}
