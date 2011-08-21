/*Adaptive lower bound with communication....master slave mode*/
/*Seems to be a surprisingly large number*/
/*Broadcasting is not possible.....so trying Isends*/
/*Distributed worker*/
/*Here I implement load balancing*/
# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<stdlib.h>
# include<string.h>

int myid, numprocs;
#define n 11
int adj[n][n];
int cache[n][(1<<n)];
int queue[25000][3],upperb;
int snode=0,ubupdate,k=20;
int front,rear,suc,suc1;
int ubtag=56,rsend=36,rrecv=46;
MPI_Status stat;
MPI_Request req;
int lbcostarr[n],lbposiarr[n],inilb,k1,c,dfsleaf=0,dfscount=0;
double lastupdated,dfstime=0.0;
int askwork=25,sendwork=26,term=12,chg,chg1;
double thresh=1000;
int test1,test2,test3;

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



int dfs1(int city,int bitv1, int cost)
{
  int i,allsend=562,allrecv=-5653;
  static int count,count1;
  int val,best=100000,flag=0,tupperb;
  int *t;
  double dfstend=0.0,dfststart=0.0;

  
  c++;
  dfscount++;
  dfststart=MPI_Wtime();
  if(bitv1==0)
    {
      dfsleaf++;
      return adj[city][snode];
      /*return cache[city][bitv]=adj[city][snode];*/
    }
  
  val=0;
  for(i=0;i<n;i++)
    {
      
      if(bitv1&(1<<i))
	{
	  val=adj[city][i];
	  /*printf("History:%d new:%d tot:%d\n",cost,val,cost+val);*/
	  val+=dfs1(i,bitv1-(1<<i),val+cost);
	  best=min(best,val);
	}
    }
  dfstend=MPI_Wtime();
  dfstime+=(dfstend-dfststart);
  return best;
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
  /*for(i=rear;i<front;i++)
    printf("Original queue: %d %d %d\n",queue[i][0],queue[i][1],queue[i][2]);
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
  int anssend1;
  double start,end,sendtag=4,recvtag=5;
  int i,bitv,mincost,mycost,sflag=0,tupperb,best=10000,askproc,askingproc,askflag=0;
  int *t;
  int fact,tfact,j;

  /*Initiating the MPI communication headers*/

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  start=MPI_Wtime();
  

  init_adj();
  printf("\n");


  bitv=(1<<n)-2;

  dfscount=0;
  fact=0;
  for(i=1;i<=n;i++)
    {
      tfact=1;
      for(j=1;j<=i;j++)
	tfact*=j;
      fact+=tfact;
      printf("%d\n",tfact);
      tfact=1;
    }
  printf("\n\n\n%d %d %d %d\n\n",dfs1(0,bitv,0),dfscount,dfsleaf,fact);
  dfscount=0;
  dfsleaf=0;
  
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
          /*printf("[[%d]] %d %d %d",myid,t[0],t[1],t[2]);*/
          mycost=dfs1(t[0],t[1],t[2])+t[2];
          best=min(best,mycost);
          int2bit(t[1]);
          printf("   %d Entered dfs %d times\n",myid,dfscount);
          /*printf("[[%d]] best:%d mycost:%d\n",myid,best,mycost);*/
        }
      printf("PROC 0 now out of work and its best is %d\n",best);
      /*Processor 0*/
      /*Asking for work....ring topology*/


      end=MPI_Wtime();
      printf("Time taken by processor 0 is %lf\n",end-start);


      for(i=1;i<numprocs;i++)
        {
          MPI_Recv(&anssend1,1,MPI_INT,i,rsend,MPI_COMM_WORLD,&stat);
          best=min(best,anssend1);
        }
      printf("\n%d says the best was %d and ubsuc:%d lbsuc:%d\n",myid,best,ubupdate,suc);
      printf("%d eneter dfs %d times and time was %lf and upperbound changed %d times and did not %d times\n",myid,c,dfstime,chg,chg1);
      printf("[%d]:NUMBER OF LEAVES %d\n",dfsleaf);
    }
  else
    {
      t[0]=t[1]=t[2]=1;
      while(t[0]!=-1 || t[1]!=-1 || t[2]!=-1)
        {
          MPI_Recv(t,3,MPI_INT,0,rsend,MPI_COMM_WORLD,&stat);
          /*printf("RECEIVED[[%d]] %d %d %d\n",myid,t[0],t[1],t[2]);*/
          push(t[0],t[1],t[2]);
          /*At this point every processor has an equal amount of work*/
        }
      k1=size();
      front--;
      /*
      for(i=rear;i<front;i++)
      printf("queue[%d] : %d %d %d\n",myid,queue[i][0],queue[i][1],queue[i][2]);*/
      /*At this point all procs have equal amount of work*/
      while(size()>0)
        {
          t=pop();
          mycost=0;
          /*printf("[[%d]] %d %d %d\n",myid,t[0],t[1],t[2]);*/
          mycost=dfs1(t[0],t[1],t[2])+t[2];
          best=min(best,mycost);
          int2bit(t[1]);
          printf("   %d Entered dfs %d times\n",myid,dfscount);
          dfscount=0;
          /*printf("[[%d]] best:%d mycost:%d size:%d orig size:%d\n",myid,best,mycost,size(),k1);*/
        }
      printf("Processor %d is now out of work and its best is %d!!!\n",myid,best);
      /*anssend1=best;
      MPI_Send(&anssend1,1,MPI_INT,0,rsend,MPI_COMM_WORLD);
      */
      /*Asking for work....ring topology*/
      term=1;

      anssend1=best;
      MPI_Send(&anssend1,1,MPI_INT,0,rsend,MPI_COMM_WORLD);
      printf("%d says the best was %d and ubsuc:%d lbsuc:%d\n",myid,best,ubupdate,suc);
      printf("%d entered dfs %d times and time : %lf ; upperb changed:%d times and did not %d times\n",myid,c,dfstime,chg,chg1);
      printf("[%d]:NUMBER OF LEAVES %d\n",myid,dfsleaf);
    }


  printf("%d %d %d\n",(1101&(1<<0))>>0,(1101&(1<<1))>>1,(1101&(1<<2))>>2);

  end=MPI_Wtime();
  printf("TIME:%lf\n",end-start);
}
