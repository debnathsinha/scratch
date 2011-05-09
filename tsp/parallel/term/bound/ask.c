/*Adaptive lower bound with communication....master slave mode*/
/*Seems to be a surprisingly large number*/
/*Broadcasting is not possible.....so trying Isends*/
/*Distributed worker*/
# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<stdlib.h>
# include<string.h>

int myid, numprocs;
#define n 17
int adj[n][n];
int cache[n][(1<<n)];
int queue[25000][3],upperb;
int snode=0,ubupdate,k=200;
int front,rear,suc,suc1;
int ubtag=56,rsend=36,rrecv=46;
MPI_Status stat;
MPI_Request req;
int lbcostarr[n],lbposiarr[n],inilb,k1;
double lastupdated;

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
	tmin=0;
	
      lbcostarr[i]=tmin;
      lbposiarr[i]=tempj;
    }
  for(i=0;i<n;i++)
    {
      sum+=lbcostarr[i];
    }
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
  
  for(i=0;i<n;i++)
    optimal[i]=0;
  upperb=0;
  for(i=node,count2=0;count2<n;count2++)
    {
      if(bitv!=0)
	{
	  tempmin=10000;
	  flag=0;
	  for(j=0;j<n;j++)
	    {
	      if((bitv&(1<<j))==(1<<j))
		{
		  tempmin=min(tempmin,adj[i][j]);
		  if(tempmin==adj[i][j])
		    {
		      flag=1;
		      tempj=j;
		    }
		}
	    }
	  if(flag==1)
	    {
	      optimal[count2]=tempj;
	      upperb=upperb+adj[i][tempj];
	      i=tempj;
	      bitv=bitv-(1<<i);
	    }
	}
    }

  upperb+=adj[i][snode];

  /*for(i=0;i<n;i++)
    printf(" %d ", optimal[i]);
  printf("\n");
  */

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
	  ubupdate++;
	  /*printf("Upper bound is being revised by %d to %d:%d\n",myid,cost+adj[city][snode],upperb);
	  /*Sending the upper bound to all processors*/
	  /*if(MPI_Wtime()-lastupdated>4.0)
	    {  
	      printf("Sending....\n");
	      for(i=1;i<numprocs;i++)
		{
		  if(i==myid)
		    continue;
		  MPI_Send(&upperb,1,MPI_INT,i,ubtag,MPI_COMM_WORLD);
		  printf("%d SENT %d time(%lf)\n",myid,i,MPI_Wtime());
		}
	      lastupdated=MPI_Wtime();
	    }
	  else
	  printf("I know the value was updated but its too early to communicate\n");*/
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
  int i,val,j,newcost,count1=0;
  int *t,ask;
  int best=1000000,nsend,pid,sendtag=5,recvtag=4;
  int arr[3]={-1,-1,-1};

  push(snode,bitv,0);

  while(size()>0 && size()<k)
    {
      t=pop();
      if(t[1]==0)
        {
          best=min(best,t[2]+adj[t[0]][snode]);
        }
      else
      for(i=0;i<n;i++)
	{
	  if(t[1]&(1<<i))
	    {
	      newcost=adj[t[0]][i]+t[2];
	      push(i,(t[1]-(1<<i)),newcost);
	    }
	}
    }
  nsend=0;
  k1=size();
  /*printf("SIZE:%d k/numprocs : %d\n",size(),(int)(k-numprocs*(k/numprocs)));
  while(size()>0)
    {
      t=pop();
      newcost=0;
      /*printf("Root have popped out %d %d %d\n",t[0],t[1],t[2]);
      int2bit(t[1]);
      printf("\n");
      newcost=t[2]+dfs(t[0],t[1]);
      /*Sending to each of the workers*//*
      count1++;
      count1=(count1%(numprocs-1))+1;
      /*printf("I am sending %d %d %d to %d and the new size of the queue is %d\n",t[0],t[1],t[2],count1,size());*//*
      MPI_Send(t,3,MPI_INT,count1,rsend,MPI_COMM_WORLD);
      printf("[%d]Sent: Queue[%d] %d %d %d to %d\n",myid,count1,t[0],t[1],t[2],count1);
      nsend++;
      
    }*/
  for(i=0;i<(k1/numprocs);i++)
    {
      for(j=1;j<numprocs;j++)
	{
	  t=pop();
	  MPI_Send(t,3,MPI_INT,j,rsend,MPI_COMM_WORLD);
	  /*printf("[%d]Sent: Queue[%d] %d %d %d\n",myid,j,t[0],t[1],t[2]);*/
	}
    }
  for(j=1;j<numprocs;j++)
    MPI_Send(arr,3,MPI_INT,j,rsend,MPI_COMM_WORLD);
  printf("There should now be %d elements in the queue and nsend:%d\n",size(),nsend);
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
  int i,bitv,mincost,mycost,sflag=0,tupperb,best=10000;
  int *t;

  /*Initiating the MPI communication headers*/

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  start=MPI_Wtime();


  init_adj();
  printf("\n");

  bitv=(1<<n)-2;
  lower();
  inilb=glower(bitv);
  glower(bitv-(1<<3));
  upper(snode,bitv);
  start=MPI_Wtime();
  lastupdated=MPI_Wtime();
  if(myid==0)
    {
      start=MPI_Wtime();
      bfs(snode,bitv,0);
      end=MPI_Wtime();
      printf("The time taken for the bfs was %lf and %d nodes were successful\n",end-start,suc);
      /*At this point every processor has an equal amount of work*/
      start=MPI_Wtime();
      while(size()>0)
	{
	  t=pop();
	  mycost=0;
	  mycost=dfs(t[0],t[1],t[2])+t[2];
	  best=min(best,mycost);
	  /*printf("[[%d]] best:%d mycost:%d\n",myid,best,mycost);*/
	}
      printf("%d says the best was %d and ubsuc:%d lbsuc:%d\n",myid,best,ubupdate,suc);
    }
  else
    {
      t[0]=t[1]=t[2]=1;
      while(t[0]!=-1 || t[1]!=-1 || t[2]!=-1)
	{
	  MPI_Recv(t,3,MPI_INT,0,rsend,MPI_COMM_WORLD,&stat);
	  push(t[0],t[1],t[2]);
	  /*At this point every processor has an equal amount of work*/
	}
      k1=size();
      front--;
      /*At this point all procs have equal amount of work*/
      while(size()>0)
        {
          t=pop();
          mycost=0;
          mycost=dfs(t[0],t[1],t[2])+t[2];
          best=min(best,mycost);
	  /*printf("[[%d]] best:%d mycost:%d size:%d orig size:%d\n",myid,best,mycost,size(),k1);*/
        }
      printf("%d says the best was %d and ubsuc:%d lbsuc:%d\n",myid,best,ubupdate,suc);
    }
  end=MPI_Wtime();
  printf("TIME:%lf\n",end-start);
}
