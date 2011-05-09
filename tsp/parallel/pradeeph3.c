#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define NSIZE 1000


double arr[NSIZE][NSIZE];
double temp_arr[NSIZE][NSIZE];
int n;
double *t,*l,*r,*d,tl,tr,dl,dr,vsum;
int p,pid,starti,endi,startj,endj,sqrtp,ctr,x;
void topleft()
{
  int source,destn;
  double val;
  MPI_Status stat;
  if(starti==1)
    {
      tl=0.0;
      if(pid!=sqrtp-1)
	{
	  destn=pid+sqrtp+1;
	  val=arr[endi][endj];
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  if(startj==1)
    {
      tl=(double)(starti-1)/(n-1);
      if(pid!=((sqrtp-1)*sqrtp))
	{
	  destn=pid+sqrtp+1;
	  val=arr[endi][endj];
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);

	}
      return;
    }
  source=pid-sqrtp-1;

  MPI_Recv(&tl,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);
  if(endi!= n-2&&endj!=n-2)
    {
      destn=pid+sqrtp+1;
      val=arr[endi][endj];
      MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}
void downright()
{
  int source,destn;
  double val;
  MPI_Status;

  if(endi==n-2)
    {
      dr=1.00+(double)(endj+1)/(n-1);
      if(pid != (sqrtp*(sqrtp-1)) )
	{
	  destn=pid-sqrtp-1;
	  val=arr[starti][startj];
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  if(endj==n-2)
    {
      dr=2.00*(endi+1)/(n-1);
      if(pid != sqrtp-1)
	{
	  destn=pid-sqrtp-1;
	  val=arr[starti][startj];
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  source=pid+sqrtp+1;
  MPI_Status stat;
  MPI_Recv(&dr,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);

  if(starti != 1 && startj != 1)
    {
      destn=pid-sqrtp-1;
      val=arr[starti][startj];
      MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}
void top()
{
  int source,destn,i,j;
  double *val;
  MPI_Status stat;
  t=(double *)malloc(sizeof(MPI_DOUBLE)*(endj-startj+1));
  val=(double *)malloc(sizeof(MPI_DOUBLE)*(endj-startj+1));
  if(starti==1)
    {
      for(i=0;i<endj-startj+1;i++)
	t[i]=0;
      destn=pid+sqrtp;
      if(destn<p&&destn>=0)
	{

	  for(i=0,j=startj;i<endj-startj+1;i++,j++)
	    val[i]=arr[endi][j];
	  MPI_Send(val,endj-startj+1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  source=pid-sqrtp;

  MPI_Recv(t,endj-startj+1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);
  if(endi!=n-2)
    {
      for(i=0,j=starti;i<endj-startj+1;i++,j++)
	val[i]=arr[endi][j];
      destn=pid+sqrtp;
      MPI_Send(val,endj-startj+1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}
void down()
{
  int source,destn,j,i;
  double *val;
  MPI_Status stat;
  d=(double *)malloc(sizeof(MPI_DOUBLE)*(endj-startj+1));
  val=(double *)malloc(sizeof(MPI_DOUBLE)*(endj-startj+1));
  if(endi==n-2)
    {
      for(i=0,j=startj;i<endj-startj+1;i++,j++)
	{
	  d[i]=1+(double)j/(n-1);
	}
      destn=pid-sqrtp;
      if(destn>=0&&destn<p)
	{
	  for(i=0,j=startj;i<endj-startj+1;i++,j++)
	    {
	      val[i]=arr[starti][j];
	    }

	  MPI_Send(val,endj-startj+1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  source=pid+sqrtp;
  MPI_Recv(d,endj-startj+1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);
  if(starti!=1)
    {
      for(i=0,j=startj;i<endj-startj+1;i++)
	{
	  val[i]=arr[starti][j];
	}
      destn=pid-sqrtp;
      MPI_Send(val,endj-startj+1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}
void left()
{
  int source,destn,i,j;
  MPI_Status stat;
  double *val;
  l=malloc(sizeof(MPI_DOUBLE)*(endi-starti+1));
  val=malloc(sizeof(MPI_DOUBLE)*(endi-starti+1));
  if(startj==1)
    {
      for(i=0,j=starti;i<(endi-starti+1);i++,j++)
	{
	  l[i]=(double)j/(n-1);
	}
      if(endj!=n-2)
	{
	  int destn=pid+1;
	  for(i=0,j=starti;i<(endi-starti+1);i++,j++)
	    {
	      val[i]=arr[j][endj];
	    }
	  MPI_Send(val,(endi-starti+1),MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return ;
    }
  source=pid-1;
  MPI_Recv(l,endi-starti+1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);
  if(endj!=n-2)
    {
      destn=pid+1;
      for(i=0,j=starti;i<endi-starti+1;i++,j++)
	{
	  val[i]=arr[j][endj];
	}
      MPI_Send(val,endi-starti+1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}
void right()
{
  int source,destn,i,j;
  MPI_Status stat;
  double *val;
  r=malloc(sizeof(MPI_DOUBLE)*(endi-starti+1));
  val=malloc(sizeof(MPI_DOUBLE)*(endi-starti+1));
  if(endj==n-2)
    {
      for(i=0,j=starti;i<endi-starti+1;i++,j++)
	{
	  r[i]=2.00*(double)j/(n-1);
	}
      if(startj!=1)
	{
	  for(i=0,j=starti;i<endi-starti+1;i++,j++)
	    {
	      val[i]=arr[j][startj];
	    }
	  destn=pid-1;
	  MPI_Send(val,endi-starti+1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  source=pid+1;
  MPI_Recv(r,endi-starti+1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);
  if(startj!=1)
    {
      destn=pid-1;
      for(i=0,j=starti;i<endi-starti+1;i++,j++)
	{
	  val[i]=arr[j][startj];
	}
      MPI_Send(val,endi-starti+1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}
void topright()
{
  int source,destn,i;
  MPI_Status stat;
  double val;
  if(starti==1)
    {
      tr=0;
      if(pid!=0)
	{
	  val=arr[endi][startj];
	  destn=pid+sqrtp-1;
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  if(endj==n-2)
    {
      tr=2.00*(double)(starti-1)/(n-1);
      if(pid!=p-1)
	{
	  val=arr[endi][startj];
	  destn=pid+sqrtp-1;
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  source=pid-sqrtp+1;
  MPI_Recv(&tr,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);
  if(endi!=n-2&&startj!=1)
    {
      val=arr[endi][startj];
      destn=pid+sqrtp-1;
      MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}
void downleft()
{
  int source,destn,i;
  MPI_Status stat;
  double val;
  if(endi==n-2)
    {
      dl=1+(double)(endj+1)/(n-1);
      if(pid!=p-1)
	{
	  destn=pid-sqrtp+1;
	  val=arr[starti][endj];
	  destn=pid-sqrtp+1;
	  val=arr[starti][endj];
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  if(startj==1)
    {
      dl=(double)(endi-1)/(n-1);
      if(pid!=0)
	{
	  destn=pid-sqrtp+1;
	  val=arr[starti][endj];
	  MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
	}
      return;
    }
  source=pid+sqrtp-1;
  MPI_Recv(&dl,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,&stat);
  if(starti!=1&&endj!=n-2)
    {
      destn=pid-sqrtp+1;
      val=arr[starti][endj];
      MPI_Send(&val,1,MPI_DOUBLE,destn,0,MPI_COMM_WORLD);
    }
}

int minim(int a,int b)
{
  return a<b?a:b;
}
int maxim(int a,int b)
{
  return a>b?a:b;
}
void initialize(int a,int b,int c,int d)
{
  int i,j;
  for(i=a;i<=c;i++)
    {
      for(j=b;j<=d;j++)
	{
	  if(i==0&&j>=0&&j<=n-1)
	    {
	      arr[i][j]=0.00;
	      continue;
	    }
	  if(i==n-1&&j>=0&&j<=n-1)
	    {
	      arr[i][j]=1+(double)j/(n-1);
	      continue;
	    }
	}
      if(i==n-1&&j>=0&&j<=n-1)
	{
	  arr[i][j]=1+(double)j/(n-1);
	  continue;
	}
      if(i>=1&&i<=n-2&&j==0)
	{
	  arr[i][j]=(double)i/(n-2);
	  continue;
	}
      if(i>=1&&i<=n-2&&j==n-1)
	{
	  arr[i][j]=(double)(2.00*i)/(n-1);
	  continue;
	}
      arr[i][j]=0.5;
    }

}
void verification_sum()
{
double sum=0.00;
int i;
if(pid!=0)
{
  int maxi=maxim(starti,startj);
  for(i=maxi;i<=endi&&i<=endj;i++)
    sum+=arr[i][i];
  double val=sum;
  MPI_Send(&val,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
}
 else
   {
     MPI_Status stat;
     for(i=1;i<=endi&&i<=endj;i++)
       {
	 sum+=arr[i][i];
       }
     for(i=1;i<p;i++)
       {
	 int val;
	 MPI_Recv(&val,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&stat);
	 sum+=val;
       }
     vsum=sum;
   }
}

int main(int argc,char *argv[])
{
  MPI_Init(&argc,&argv);
  int i,j,tempn;
  n=NSIZE;
  double start_time,end_time;
  MPI_Comm_size(MPI_COMM_WORLD,&p);
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);

  if(pid==0)
    {
      printf("There are %d processors\n",p);
    }


  sqrtp=sqrt((double)p);
  tempn=n-1;
  starti=1+(int)tempn/sqrt((double)p)*(int)(pid/sqrt((double)p));
  startj=1+pid%(int)sqrt((double)p)*(int)tempn/sqrt((double)p);
  endi=minim(starti+(n-1)/sqrtp-1,n-2);
    
               
       temp_arr[endi][startj]=4*arr[endi][startj]+2*(d[0]+arr[endi-1][startj])+2*(arr[starti][startj+1]+l[endi-starti])+l[endi-starti-1]+dl+arr[endi-1][startj+1]+d[1];
               
  temp_arr[endi][endj]=4*arr[endi][endj]+2*(arr[endi-1][endj]+d[endj-endi])+2*(arr[endi][endj-1]+r[endi-starti])+arr[endi-1][endj-1]+d[endj-startj-1]+r[endi-starti-1]+dr;

  for(i=startj+1;i<=endj-1;i++)
    {
                       
      temp_arr[starti][i]=4*arr[starti][i]+2*(arr[starti][i+1]+arr[starti][i-1])+2*(arr[starti+1][i]+t[i-startj])+t[i-startj-1]+t[i-startj+1]+arr[starti+1][i-1]+arr[starti+1][i+1];
    }
  for(i=startj+1;i<=endj-1;i++)
    {
                       
      temp_arr[endi][i]=4*arr[endi][i]+2*(arr[endi][i+1]+arr[endi][i-1])+2*(arr[endi-1][i]+d[i-startj])+d[i-startj-1]+d[i-startj+1]+arr[endi-1][i-1]+arr[endi-1][i+1];
    }
  for(i=starti+1;i<=endi-1;i++)
    {
                       
      temp_arr[i][startj]=4*arr[i][startj]+2*(arr[i][startj+1]+l[i-starti])+2*(arr[i-1][startj]+arr[i+1][startj])+l[i-starti-1]+l[i-starti+1]+arr[i+1][startj+1]+arr[i-1][startj+1];
    }
  for(i=starti+1;i<=endi-1;i++)
    {
                       
      temp_arr[i][endj]=4*arr[i][endj]+2*(arr[i][endj-1]+r[i-starti])+2*(arr[i-1][endj]+arr[i+1][endj])+r[i-starti-1]+r[i-starti+1]+arr[i-1][endj-1]+arr[i+1][endj-1];
    }
  for(i=starti+1;i<=endi-1;i++)
    {
      for(j=startj+1;j<=endj-1;j++)
	{
                               
	  temp_arr[i][j]=(4*arr[i][j]+2*(arr[i+1][j]+arr[i-1][j])+2*(arr[i][j+1]+arr[i][j-1])+arr[i+1][j-1]+arr[i+1][j+1]+arr[i-1][j+1]+arr[i-1][j-1]);
	}

    }

  for(i=starti;i<=endi;i++)
    {
      for(j=startj;j<=endj;j++)
	{
	  arr[i][j]=temp_arr[i][j]/16.00;
	}
    }

  MPI_Barrier(MPI_COMM_WORLD);

verification_sum();
if(pid==0)
{
  end_time=MPI_Wtime();
  printf("Elapsed time is %lf and the verification sum is %lf\n",end_time-start_time,vsum);
}
MPI_Finalize();
return 0;
}
