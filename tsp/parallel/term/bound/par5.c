/*Adaptive lower bound with communication....master slave mode*/
/*Seems to be a surprisingly large number*/

# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<stdlib.h>
# include<string.h>

int myid, numprocs;
#define n 11
int adj[n][n];
int cache[n][(1<<n)];
int queue[50000][3],upperb;
int snode=0,k=10;
int front,rear,suc,suc1;
int ubtag=5,rsend=3,rrecv=4;
MPI_Status stat;
int lbcostarr[n],lbposiarr[n];

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

int min(int a, int b)
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
void push(int i, int bitv, int cost)
{
  queue[front][0]=i;
  queue[front][1]=bitv;
  queue[front][2]=cost;
  front++;
}

int size()
{
  return front-rear;
}

int glower(int bitv)
{
  int i,j,tmin=0,tempj,sum=0;
  for(i=0;i<n;i++)
    {
      tmin=1000;
      if((bitv&(1<<i))>>i)
	{
	  for(j=0;j<n;j++)
	    {
	      tmin=min(tmin,adj[i][j]);
	      if(tmin==adj[i][j])
		tempj=j;  
	    }
	}
      else
	{
	  /*printf("Could not enter %d\n",i);*/
	  tmin=0;
	}
      lbcostarr[i]=tmin;
      lbposiarr[i]=tempj;
    }
  /*printf("Generalized!!!\n");*/
  for(i=0;i<n;i++)
    {
      /*printf("%d:%d  ",lbcostarr[i],lbposiarr[i]);*/
      sum+=lbcostarr[i];
    }
  /*printf("Sum:%d\n",sum);*/
  return sum;
}

void lower()
{
  int i,j,tmin=0,tempj;
  for(i=0;i<n;i++)
    {
      tmin=1000;
      for(j=0;j<n;j++)
	{
	  tmin=min(tmin,adj[i][j]);
	  if(tmin==adj[i][j])
	    tempj=j;
	}
      lbcostarr[i]=tmin;
      lbposiarr[i]=tempj;
    }
  for(i=0;i<n;i++)
    {
      printf("%d:%d  ",lbcostarr[i],lbposiarr[i]);
    }
  printf("\n");
}

int upper(int node, int bitv)
{

  int i,j,tempmin,tempj,flag=0;
  int optimal[n],count2;

  /*This is the heuristic algorithm*/
  /*
  printf("Initial int2bit\n");
  int2bit(bitv);
  printf("\n");*/
  for(i=0;i<n;i++)
    optimal[i]=0;
  upperb=0;
  for(i=node,count2=0;count2<n;count2++)
    {
      /*printf("Entered the initial loop with %d\n",i);
      int2bit(bitv);
      printf("\n");*/
      if(bitv!=0)
	{
	  tempmin=10000;
	  flag=0;
	  for(j=0;j<n;j++)
	    {
	      /*printf("Inner loop\n");
		    int2bit(bitv);
		        printf("  ");
			    int2bit((bitv&(1<<j))>>j);
			    printf("\n");*/
	      if((bitv&(1<<j))==(1<<j))
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
	      upperb=upperb+adj[i][tempj];
	      /*printf("hcost now is %d from %d to %d\n",hcost,i,tempj);*/
	      i=tempj;
	      /*
		    vis[i]=1;
		        
		    printf("This is the new(%d) bitv :   ",i);*/
	      bitv=bitv-(1<<i);
	      /*int2bit(bitv);
		printf("\n");
		
		printf(" %d is now a part of the optimal route\n",i);*/
	    }
	}
    }

  upperb+=adj[i][snode];

  for(i=0;i<n;i++)
    printf(" %d ", optimal[i]);
  printf("\n");
  

  printf("The upper bound is %d\n",upperb);
  return upperb;
}


int dfs(int city,int bitv, int cost)
{
  int i,allsend=-5625,allrecv=-5653;
  static int count,count1;
  int val,best=100000;

  /*if(cache[city][bitv]!=0)return cache[city][bitv];*/

  if((glower(bitv)+cost)>upperb)
    {
      suc++;
      return 100000;
    }
  else
    suc1++;
  if(bitv==0)
    {
      if(upperb>(cost+adj[city][snode]))
	{
	  upperb=cost+adj[city][snode];
	  printf("Upper bound is being revised by %d to %d:%d\n",myid,cost+adj[city][snode],upperb);
	  /*Sending the upper bound to all processors*/
	  MPI_Bcast(&upperb,1,MPI_INT,myid,MPI_COMM_WORLD);
	  printf("Sent %d to all\n",upperb);
	}
      return adj[city][snode];
      /*return cache[city][bitv]=adj[city][snode];*/
    }
  
  val=0;
  for(i=0;i<n;i++)
    {
      
      if(bitv&(1<<i))
	{
	  val=adj[city][i];
	  /*printf("History:%d new:%d tot:%d\n",cost,val,cost+val);*/
	  val+=dfs(i,bitv-(1<<i),val+cost);
	  best=min(best,val);
	}
    }
  return best;
  /*return cache[city][bitv]=best;*/
}

void bfs(int start, int bitv, int cost)
{
  int i,val,j,newcost,count1;
  int *t;
  int best=1000000,nsend,pid,sendtag=5,recvtag=4;
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
      MPI_Send(t,3,MPI_INT,count1,rsend,MPI_COMM_WORLD);
      nsend++;
      
    }
  /*printf("I hope nsend %d matches above\n",nsend);*/
  for(i=1;i<numprocs;i++)
    {
      /*printf("Root is sending -1 to %d\n",i);*/
      MPI_Send(arr,3,MPI_INT,i,rsend,MPI_COMM_WORLD);      
    }
  /*printf("And now I the root does all the receiving\n");*/
  for(count1=nsend;count1>0;count1--)
    {
      MPI_Recv(&newcost,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);
      printf("I the root received %d tag from %d\n",stat.MPI_TAG,stat.MPI_SOURCE);
      /*printf("Root received %d from %d and count1:%d\n",newcost,pid,count1);*/
      best=min(best,newcost);
    }
  printf("The minimum cost through bfs is %d....signing off from inside the bfs function!!!\n",best);
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
  double start,end,sendtag=4,recvtag=5;
  int i,bitv,mincost,mycost,sflag=0;
  int t[3]={1,1,1};

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
  lower();
  glower(bitv-(1<<3));
  upper(snode,bitv);
  start=MPI_Wtime();
  if(myid==0)
    {
      start=MPI_Wtime();
      bfs(snode,bitv,0);
      end=MPI_Wtime();
      printf("The time taken for the bfs was %lf and %d nodes were successful\n",end-start,suc);
    }
  else
    {
      /*MPI_Recv(t,3,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);
	printf("%d received %d tag from root\n",myid,stat.MPI_TAG);*/
      while(t[0]!=-1 || t[1]!=-1 || t[2]!=-1)
	{
	  /*printf("%d received %d %d %d from root\n",myid,t[0],t[1],t[2]);
	  /*int2bit(t[1]);
	    printf("\n");*/
	  /*mycost=0;
	  mycost=dfs(t[0],t[1],t[2]);
	  /*printf("%d\n",dfs(6,8124));
	    printf("PROCESSOR %d SAYS ITS DFS GIVES %d where t[0]:%d and t[1]:%d\n",myid,mycost,t[0],t[1]);*/
	  /*mycost=t[2]+ mycost;
	  /*int2bit(t[1]);
	    printf("\n");*/
	  /*printf("%d am sending %d to root where t[2]:%d and dfs subprob:%d\n",myid,mycost,t[2],mycost-t[2]);*/
	  

	  /*MPI_Send(&mycost,1,MPI_INT,0,rrecv,MPI_COMM_WORLD);*/
	  
	  MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);
	  if(stat.MPI_TAG==rsend)
	    {
	      MPI_Recv(t,3,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);
	      mycost=0;
	      mycost=dfs(t[0],t[1],t[2]);
	      mycost=t[2]+mycost;
	      MPI_Send(&mycost,1,MPI_INT,0,rrecv,MPI_COMM_WORLD);
	    }
	  else if(stat.MPI_SOURCE!=0)
	    {
	      MPI_Recv(&upperb,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);
	      printf("This is the upper bound tag and the upperbound has been changed to %d!!!\n",upperb);
	    }
	}
      if(t[0]==-1 || t[1]==-1 || t[2]==-1)
	{
	  /*mycost=-1;
	  MPI_Send(&myid,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  MPI_Send(&mycost,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  */
	  printf(" %d received -1 from root......%d is now going to sleep!!\n",myid,myid);
	  printf("Btw...%d nodes were successful and %d were not\n",suc,suc1);
	  }
    }
  end=MPI_Wtime();
  /*printf("The minimum coast through bfs is %d and the time is %lf\n",mincost,end-start);
   */
  end=MPI_Wtime();
}
