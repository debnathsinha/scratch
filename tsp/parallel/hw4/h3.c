# include<stdio.h>
# include<math.h>
# include<mpi.h>

# define EP 0.316251E-4

double queue[2000][4];
int front=0, rear=0;
int numprocs,myid;
double sum1=0.0;
double startime;
MPI_Status stat;

double f(double x, double y)
{
  return ((sqrt(x*y+1.0))+(sin(x+y)*sin(x+y)));
}

double max(double a, double b)
{
  if(a>b)
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


double dfs(double e, double g, double h, double i)
{
  static int count=0;
  double midx, midy;
  double val;
  double ans=0.0;
  double temp1,temp2,temp3,temp4;
  midx=(e+g)/2;
  midy=(h+i)/2;
  double fr;
  fr=f(midx,midy);
  temp1=fabs(f(e,h)-fr);
  temp2=fabs(f(g,h)-fr);
  temp3=fabs(f(g,i)-fr);
  temp4=fabs(f(e,i)-fr);
  if(max(temp1,max(temp2,max(temp3,temp4)))<=EP*fr)
    {
      return fr*(i-h)*(g-e);
    }
  else
    {
      ans+=dfs(e,midx,h,midy);
      ans+=dfs(midx,g,h,midy);
      ans+=dfs(midx,g,midy,i);
      ans+=dfs(e,midx,midy,i);
    }
}

void bfs()
{
  static int count;
  int isasked;
  double midx,midy,temp1,temp2,temp3,temp4;
  double *t,*temp;
  double sum=0.0;
  double e,g,h,i;
  int k,l,source,tempproc;
  double ansback;
  int count1=0;
  double temprep,temprep1;
  double shutdwn[4]={-1,-1,-1,-1};
  push(0,4,1,2);
  while(size() && size()<40)
    {
      t=pop(); 
      e=t[0];
      g=t[1];
      h=t[2];
      i=t[3];
      midx=(e+g)/2;
      midy=(h+i)/2;
      double fr;
      fr=f(midx,midy);
      temp1=fabs(f(e,h)-fr);
      temp2=fabs(f(g,h)-fr);
      temp3=fabs(f(g,i)-fr);
      temp4=fabs(f(e,i)-fr);
      if(max(temp1,max(temp2,max(temp3,temp4)))<=EP*fr)
	{
	  sum+=fr*(i-h)*(g-e);
	}
      else
	{
	  push(e,midx,h,midy);
	  push(midx,g,h,midy);
	  push(midx,g,midy,i);
	  push(e,midx,midy,i);
	}

    }
  while(size()!=0)
    {
      /*Check if asked
	If asked, then pop and send work
	Check if size is 0
	If 0 then send everyone -1 
	Wait for all answers and add to sum
      */
      /*Receiving from an arbitrary source*/
      MPI_Recv(&isasked,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&stat);
      if(isasked>0)
	{
	  temp=pop();
	  count1++;
	  MPI_Send(temp,4,MPI_DOUBLE,isasked,0,MPI_COMM_WORLD);
	}
      if(isasked<0)
	{
	  /*Receiving answer*/
	  tempproc=-1*isasked;
	  MPI_Recv(&ansback,1,MPI_DOUBLE,tempproc,0,MPI_COMM_WORLD,&stat);
          count1--;
	  sum1+=ansback;
          ansback=0.0;
	}
    }
  ansback=0.0;
  while(count1>=1)
    {
      MPI_Recv(&isasked,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&stat);
      if(isasked>0)
	MPI_Send(shutdwn,4,MPI_DOUBLE,isasked,0,MPI_COMM_WORLD);
      else
	{
	  temprep1=-1*isasked;
	  MPI_Recv(&ansback,1,MPI_DOUBLE,temprep1,0,MPI_COMM_WORLD,&stat);
	  count1--;
	  sum1+=ansback;
	  ansback=0.0;
	}
    }
  printf("\n Sum : %lf\n",sum1);  
}

int main(int argc, char *argv[])
{
  int buff,recv,ask,prep=0;
  double anssend,mytime;
  double start,end,startdfs,enddfs,startbfs,endbfs;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  if(myid==0)
    printf("Number of processors %d\n",numprocs);
  startime=MPI_Wtime();
  ask=myid;
  start=MPI_Wtime();
  if(myid==0)
    {
      startbfs=MPI_Wtime();
      bfs();
      endbfs=MPI_Wtime();
    }
  else
    {
      MPI_Send(&ask,1,MPI_INT,0,0,MPI_COMM_WORLD);
      MPI_Recv(queue[0],4,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&stat);
      while(queue[0][0]!=-1 && queue[0][1]!=-1 && queue[0][2]!=-1 && queue[0][3]!=-1)
	{
	  startdfs=MPI_Wtime();
	  anssend=dfs(queue[0][0],queue[0][1],queue[0][2],queue[0][3]);
	  enddfs=MPI_Wtime();
	  prep=-1*myid;
	  MPI_Send(&prep,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  MPI_Send(&anssend,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	  MPI_Send(&ask,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  MPI_Recv(queue[0],4,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&stat);
	}
      mytime=MPI_Wtime();
      printf("Processor %d is out of work in time %lf\n",myid,mytime-startime);
    }
  end=MPI_Wtime();
  if(myid==0)
    printf("The total time taken by processor %d is %lf\n",myid,end-start);
  if(myid==3)
    printf("The total time taken by processor %d is %lf\n",myid,end-start);
  
  /*anssend=dfs(0,4,1,2);
  printf("DFS answer : %lf\n",anssend);
  bfs();*/
  return 0;
}
