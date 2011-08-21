# include<stdio.h>
# include<math.h>
# include<mpi.h>

# define EP 1E-1

double queue[1000][4];
int front=0, rear=0;
int numprocs,myid;
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
  return queue[rear++];
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
  printf("count:%d\n",count++);
  if(max(temp1,max(temp2,max(temp3,temp4)))<=EP*fr)
    {
      /*printf("%lf %lf %lf %lf %lf\n",f(midx,midy)*(i-h)*(g-e),e,g,h,i);*/
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
  double midx,midy,temp1,temp2,temp3,temp4;
  double *t,*temp;
  double sum=0.0;
  double e,g,h,i;
  int k;
  double ansback;
  push(0,4,1,2);
  while(size() && size()<numprocs-1)
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
      printf("count:%d\n",count++);
      if(max(temp1,max(temp2,max(temp3,temp4)))<=EP*fr)
	{
	  /*printf("%lf %lf %lf %lf %lf\n",f(midx,midy)*(i-h)*(g-e),e,g,h,i);*/
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
  for(k=1;k<numprocs;k++)
    {
      temp=pop();
      MPI_Send(temp,4,MPI_DOUBLE,k,0,MPI_COMM_WORLD);
      printf("Sent %lf %lf %lf %lf to processor %d\n",temp[0],temp[1],temp[2],temp[3],k);
      MPI_Recv(&ansback,1,MPI_DOUBLE,k,0,MPI_COMM_WORLD,&stat);
      sum+=ansback;
      ansback=0;
    }
  printf("\n Sum : %lf\n",sum);  
}

int main(int argc, char *argv[])
{
  int buff,recv;
  double anssend;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  if(myid==0)
    printf("Number of processors %d\n",numprocs);

  if(myid==0)
    {
      printf("This is processor %d\n",myid);
      bfs();
    }
  else
    {
      MPI_Recv(queue[0],4,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&stat);
      printf(" I %d have received %lf %lf %lf %lf from proc0\n",myid,queue[0][0],queue[0][1],queue[0][2],queue[0][3]);
      anssend=dfs(queue[0][0],queue[0][1],queue[0][2],queue[0][3]);
      printf("The answer sent from proc %d is %lf\n",myid,anssend);
      MPI_Send(&anssend,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }
  
  /*anssend=dfs(0,4,1,2);
  printf("DFS answer : %lf\n",anssend);
  bfs();*/
  return 0;
}
