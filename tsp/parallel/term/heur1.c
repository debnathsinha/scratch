# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<stdlib.h>
# include<string.h>

int myid, numprocs;
#define n 8
int adj[n][n];
int queue[50000][3];
int snode=0;
int front,rear;
double ans;
int hcost;

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

int min(int,int);

int heuristic()
{

  int i,j,vis[n],tempmin,tempj,flag=0;
  int optimal[n],count2;

  /*This is the heuristic algorithm*/
  for(i=0;i<n;i++)
    vis[i]=0;
  vis[0]=1;
  for(i=snode,count2=0;count2<n;count2++)
    {
      tempmin=10000;
      flag=0;
      for(j=0;j<n;j++)
        {
          if(vis[j]==0)
            {
              tempmin=min(tempmin,adj[i][j]);
              /*printf("%d MIGHT BE a part of the optimal route since the cost was %d\n",j,adj[i][j]);*/
              if(tempmin==adj[i][j])
                {
                  flag=1;
                  tempj=j;
                }
            }
        }
      if(flag==1)
        {
          /*printf("%d IS a part of optimal route and cost of going from %d to %d is %d\n",tempj,i,tempj,adj[i][tempj]);*/
          optimal[count2]=tempj;
          hcost=hcost+adj[i][tempj];
          /*printf("hcost now is %d\n",hcost);*/
          i=tempj;
          vis[i]=1;
          /*printf(" %d is now a part of the optimal route\n",i);*/
        }
    }

  hcost=hcost+adj[i][snode];

  /*for(i=0;i<n;i++)
    printf(" %d ", optimal[i]);
  printf("\n");
  */

  printf("The hueristic cost is %d\n",hcost);

}


/*
double min(double a, double b)
{
  if(a<b)
    return a;
  else
    return b;
}
*/
int min(int a,int b)
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

  while(size()>0)
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
  int i,bitv,mincost,j;

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
  printf("\nThe minimum cost through dfs is %d\n",mincost);


  /*This is the heuristic algorithm*/
  /*for(i=0;i<n;i++)
    vis[i]=0;
  vis[0]=1;
  for(i=snode,count2=0;count2<n;count2++)
    {
      tempmin=10000;
      flag=0;
      for(j=0;j<n;j++)
	{
	  if(vis[j]==0)
	    {
	      tempmin=min(tempmin,adj[i][j]);
	      /*printf("%d MIGHT BE a part of the optimal route since the cost was %d\n",j,adj[i][j]);*//*
	      if(tempmin==adj[i][j])
		{
		  flag=1;
		  tempj=j;
		}
	    }
	}
      if(flag==1)
	{
	  printf("%d IS a part of optimal route and cost of going from %d to %d is %d\n",tempj,i,tempj,adj[i][tempj]);
	  optimal[count2]=tempj;
	  hcost=hcost+adj[i][tempj];
	  printf("hcost now is %d\n",hcost);
	  i=tempj;
	  vis[i]=1;
	  printf(" %d is now a part of the optimal route\n",i);
	}
	    
	
    }*/
  heuristic();
  printf("The hueristic cost is %d\n",hcost);


  /*for(i=0;i<n;i++)
    printf(" %d ", optimal[i]);
  printf("\n");
  */
  bfs(snode,bitv,0);
  printf("The minimum coast through bfs is %d\n",mincost);

  end=MPI_Wtime();
  if(myid==0)
    printf("Number of processors %d and the time is %lf\n",numprocs,end-start);
}
