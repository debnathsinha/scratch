# include<stdio.h>
# include<math.h>
# include<mpi.h>
# include<malloc.h>

# define EP 1E-3

double queue[2000][4],tempq[2000][4];
int front=0, rear=0;
int numprocs,myid,k=3;
double sum1=0.0;
double startime;
int dfscount=0;
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
  dfscount++;
  fr=f(midx,midy);
  temp1=fabs(f(e,h)-fr);
  temp2=fabs(f(g,h)-fr);
  temp3=fabs(f(g,i)-fr);
  temp4=fabs(f(e,i)-fr);
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
  int isasked;
  double midx,midy,temp1,temp2,temp3,temp4;
  double *t,*temp;
  double sum=0.0;
  double e,g,h,i;
  int l,source,tempproc;
  double ansback;
  int count2=0,count1=0,count3=0,cont4=0;
  double temprep,temprep1;
  double shutdwn[4]={-1,-1,-1,-1};
  double **pac;
  

  push(0,4,1,2);
  /*pac=(double**)malloc(sizeof(double*)*k);
  for(count1=0;count1<k;count1++)
    pac[count1]=(double*)malloc(sizeof(double)*4);
  for(count1=0;count1<k;count1++)
    {
      printf("\n%d\n",count1);
      for(count2=0;count2<4;count2++)
	printf("%d \t",pac[count1][count2]);
	}*/
  
  while(size() && size()<k*numprocs)
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
  printf("Displaying the original queue\n");
  for(count1=rear;count1<front;count1++)
    printf("ORIGINAL %d: %lf %lf %lf %lf\n",count1%numprocs,queue[count1][0],queue[count1][1],queue[count1][2],queue[count1][3]);
  count1=0;
  /*Sending packed array to all the processors*/
  for(count1=1;count1<numprocs;count1++)
    {
      printf("\nProcessor : %d\n",count1);
      for(count2=rear,count3=0;count2<size();count2+=numprocs,count3++)
	{
	  tempq[count3][0]=queue[count1+count2][0];
	  tempq[count3][1]=queue[count1+count2][1];
	  tempq[count3][2]=queue[count1+count2][2];
	  tempq[count3][3]=queue[count1+count2][3];

	  queue[count1+count2][0]=-1.0;
          queue[count1+count2][1]=-1.0;
          queue[count1+count2][2]=-1.0;
          queue[count1+count2][3]=-1.0;
	}
      MPI_Send(tempq,4*k,MPI_DOUBLE,count1,0,MPI_COMM_WORLD);
    }
  for(count1=1;count1<numprocs;count1++)
    {
      ansback=0.0;
      MPI_Recv(&ansback,1,MPI_DOUBLE,count1,0,MPI_COMM_WORLD,&stat);
      printf("PROCESSOR 0: The answer received from %d is %lf\n",count1,ansback);
      sum1+=ansback;
    }
  printf("\nNow processor 0 does its work\n");
  for(count1=rear;count1<=front;count1++)
    {
      t=pop();
      if(t[0]!=-1.0 && t[1]!=-1.0 && t[2]!=-1.0 && t[3]!=-1.0)
	{
	  printf("%d: %lf %lf %lf %lf\n",myid,t[0],t[1],t[2],t[3]);
	  sum1+=dfs(t[0],t[1],t[2],t[3]);
	}
    }
  printf("Ireached here\n");
  /*while(size()!=0)
	    {
	    MPI_Send(temp,4,MPI_DOUBLE,isasked,0,MPI_COMM_WORLD);
	    MPI_Recv(&ansback,1,MPI_DOUBLE,tempproc,0,MPI_COMM_WORLD,&stat);
	    sum1+=ansback;
	    ansback=0.0;
	    MPI_Recv(&ansback,1,MPI_DOUBLE,temprep1,0,MPI_COMM_WORLD,&stat);
	    sum1+=ansback;
	    ansback=0.0;
	    }
	    }*/
	
    
  /*MPI_Recv(&ansback,1,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&stat);*/
  printf("\n Sum : %lf\n",sum1);  
}

int main(int argc, char *argv[])
{
  int buff,recv,ask,prep=0;
  double anssend,mytime;
  double start,end,startdfs,enddfs,startbfs,endbfs;
  int count1=0,count2=0;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  if(myid==0)
    printf("Number of processors %d\n",numprocs);
  startime=MPI_Wtime();
  ask=myid;
  start=MPI_Wtime();
  
  /*This is the new program*/

  if(myid==0)
    {
      /*Call bfs to pop and pack the array*/
      bfs();
    }
  else
    {
      anssend=0.0;
      /*Receive packed array from the node*/
      MPI_Recv(queue,4*k,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&stat);
      for(count1=0;count1<numprocs;count1++)
	{
	  printf("%d:%lf %lf %lf %lf\n",myid,queue[count1][0],queue[count1][1],queue[count1][2],queue[count1][3]);
	  /*Run a for loop tp unpack it*/
	  /*call dfs() inside the for loop*/
	  anssend+=dfs(queue[count1][0],queue[count1][1],queue[count1][2],queue[count1][3]);
	}
      printf("Processor %d sends answer %lf\n",myid,anssend);
      /*send the answer back*/
      MPI_Send(&anssend,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }
    

  end=MPI_Wtime();
  if(myid==0)
    printf("The total time taken by processor %d is %lf\n",myid,end-start);
  if(myid==3)
    printf("The total time taken by processor %d is %lf\n",myid,end-start);
  
  printf("%d:%d\n",myid,dfscount);

  /*anssend=dfs(0,4,1,2);
  printf("DFS answer : %lf\n",anssend);
  bfs();*/
  return 0;
}
