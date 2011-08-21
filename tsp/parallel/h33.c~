# include<mpi.h>
# include<stdio.h>
# include<string.h>
# include<stdlib.h>

double arr0[5000][5000],arr1[5000][5000];
int p;
int start,end;
int i,j,tempn;
int n=5000,pid;
double *t,*b;
double start_time,end_time;
double verify=0.0;

int min(int a,int b)
{
  if(a<b)
    return a;
  else
    return b;
}

int max(int a, int b)
{
  if(a>b)
    return a;
  else 
    return b;
}

void above()
{
  int source,destn,i,j;
  double *val;
  double time1,time3,time2;
  MPI_Status stat;

  t=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  val=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  
  /*printf("Entered above");*/
  if(start==0)
    {
      for(i=0;i<n;i++)
	t[i]=0.0;
      
      for(i=0;i<n;i++)
	{
	  val[i]=arr0[end][i];
	  /*printf("Sent %lf to %d\n",val[i],pid+1);*/
	}
      time1=MPI_Wtime(); 
      if(end!=(n-1))
	MPI_Send(val,n,MPI_DOUBLE,pid+1,0,MPI_COMM_WORLD);
     
    }
  else
    {
      if(pid!=0)
	MPI_Recv(t,n,MPI_DOUBLE,pid-1,0,MPI_COMM_WORLD,&stat);
      for(i=0;i<n;i++)
	{
	  val[i]=arr0[end][i];
	  /*printf("Sent1 %lf to %d\n",val[i],pid+1);*/
	}
      if(end!=(n-1))
	MPI_Send(val,n,MPI_DOUBLE,pid+1,0,MPI_COMM_WORLD);
    }
  /*if(pid==2)
    printf("The time taken for %d proc is %lf",p,time2-time1);
  */
}

void below()
{
  int source,destn,i,j;
  double *val;
  double time1,time2;
  MPI_Status stat;

  
  b=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  val=(double *)malloc(sizeof(MPI_DOUBLE)*(n));
  /*printf("Entered below\n");*/
  if(end==(n-1))
    {

      for(i=0;i<n;i++)
        b[i]=1+(double)i/(n-1);
      for(i=0;i<n;i++)
        {
          val[i]=arr0[start][i];
          /*printf("Sent21 %lf to %d start:%d pid:%d\n",val[i],pid-1,start,pid);*/
        }
      if(pid!=1)
	MPI_Send(val,n,MPI_DOUBLE,pid-1,0,MPI_COMM_WORLD);
      /*printf("Loop has been initialized for the last node\n");*/
    }
  else
    {
      if(pid!=(n-1))
	MPI_Recv(b,n,MPI_DOUBLE,pid+1,0,MPI_COMM_WORLD,&stat);
      for(i=0;i<n;i++)
        {
          val[i]=arr0[start][i];
          /*printf("Sent2 %lf to %d\n",val[i],pid-1);*/
        }
      if(start!=0)
        MPI_Send(val,n,MPI_DOUBLE,pid-1,0,MPI_COMM_WORLD);
      else;
      /*printf("Entered the start=0 condition for pid:%d\n",pid);*/
    }
  time2=MPI_Wtime();
}

void init()
{
  
  int i,j,flag=0;
  for(i=start;i<=end;i++)
    {
      /*printf("\npid:%d start:%d end:%d\n",pid,start,end);*/
    for(j=0;j<n;j++)
      {
	if(i==0)
	  {
	    arr0[i][j]=0.0;
	    arr1[i][j]=0.0;
	  }
	else if(i==n-1)
	  {
	    arr0[i][j]=1+(double)j/(n-1);
	    arr1[i][j]=1+(double)j/(n-1);
       
	  }
	else if(j==0)
	  {
	    arr0[i][j]=(double)i/(n-1);
	    arr1[i][j]=(double)i/(n-1);
	  }
	else if(j==(n-1))
	  {
	    arr0[i][j]=2*(double)i/(n-1);
	    arr1[i][j]=2*(double)i/(n-1);
	  
	  }
	else
	  {
	    arr0[i][j]=0.5;
	    arr1[i][j]=0.5;
	  }
	flag=0;
      }
    }
  /*Displaying the array*/
  /*for(i=start;i<=end;i++)
    {
      printf("\n");
      for(j=0;j<n;j++)
	printf("%lf(%d,%d)\t",arr0[i][j],pid,j);
    }
  */
}


void verification_sum()
{
  double sum=0.00,vsum=0.0;
  int i,j;
  double val;
  MPI_Status stat;

  if(pid!=0)
    {
      for(i=start;i<=end;i++)
	for(j=0;j<n;j++)
	  if(i==j)
	    sum+=arr0[i][j];
      val=sum;
      MPI_Send(&val,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }
  else
    {
      for(i=start;i<=end;i++)
        for(j=0;j<n;j++)
          if(i==j)
            sum+=arr0[i][j];

      for(i=1;i<p;i++)
	{
	  
	  MPI_Recv(&val,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&stat);
	  sum+=val;
	}
      vsum=sum;
    }
  MPI_Barrier(MPI_COMM_WORLD);
  if(pid==0)
    printf("\nVerification sum %lf\n",vsum);
}

int main(int argc,char *argv[])
{  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&p);
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);

  double stime,etime;

  int i,j,k,i1,j1;
  int count;

 

  if(pid==0)
    {
      printf("There are %d processors and a %d X %d array\n",p,n,n);
    }
  if(p!=1)
    {
      if(n%(p-1)==0)
	{
	  if(pid==p-1)
	    {
	      start=n/p*pid;
	      end=n-1;
	    }
	  else
	    {
	      start=n/p*pid;
	      end=start+n/p-1;
	    }
	}
      else if(pid!=p-1)
	{
	  start= n/(p-1)*pid;
	  end= min(start+n/(p-1)-1,n-1);
	}
      else
	{
	  start= n/(p-1)*pid;
	  end= n-1;
	}
    }
  else
    {
      start=0;
      end=n-1;
    }
  if(p==1)
    {
      start=0;
      end=n-1;
    }
  init();
  
  /*printf(" Processor %d takes from %d to %d\n",pid,start,end);*/
  start_time=MPI_Wtime();
  for(k=0;k<1;k++)
  {
    /*if(pid==1)
      printf("iter : %d\n",k);
    */
    if(p!=1)
      {
	above();
	below();
      }
    if(start!=0)
      for(j=0;j<n;j++)
	arr0[start-1][j]=t[j];
    if(end!=(n-1))
      for(j=0;j<n;j++)
	arr0[end+1][j]=b[j];
    if(p==1)
      for(i=1;i<n-1;i++)
	for(j=1;j<n-1;j++)
	  arr1[i][j]=(4*arr0[i][j]+2*arr0[i+1][j]+2*arr0[i-1][j]+2*arr0[i][j+1]+2*arr0[i][j-1]+arr0[i+1][j+1]+arr0[i-1][j-1])/16;
    
    if(start==0)
      {
	for(i=start+1;i<=end;i++)
	  for(j=1;j<n-1;j++)
	    {
	      arr1[i][j]=(4*arr0[i][j]+2*arr0[i+1][j]+2*arr0[i-1][j]+2*arr0[i][j+1]+2*arr0[i][j-1]+arr0[i+1][j+1]+arr0[i-1][j-1])/16;
	      /*if(pid==0)
              {
                printf("    arr1[i][j]  %lf : (%d,%d)\n",arr1[i][j],i,j);
                printf("    arr0[i][j]  %lf : (%d,%d)\n",arr0[i][j],i,j);
                printf("    arr0[i+1][j]  %lf : (%d,%d)\n",arr0[i+1][j],i+1,j);
                printf("    arr0[i-1][j]  %lf : (%d,%d)\n",arr0[i-1][j],i-1,j);
                printf("    arr0[i][j+1]  %lf : (%d,%d)\n",arr0[i][j+1],i,j+1);
                printf("    arr0[i][j-1]  %lf : (%d,%d)\n",arr0[i][j-1],i,j-1);
                printf("    arr0[i+1][j+1]  %lf : (%d,%d)\n",arr0[i+1][j+1],i+1,j+1);
                printf("    arr0[i-1][j-1]  %lf : (%d,%d)\n",arr0[i-1][j-1],i-1,j-1);
                printf("End of print\n");
		}*/
	    }
      }
    else if(end==(n-1))
      {
	for(i=start;i<end;i++)
          for(j=1;j<n-1;j++)
	    {
	      arr1[i][j]=(4*arr0[i][j]+2*arr0[i+1][j]+2*arr0[i-1][j]+2*arr0[i][j+1]+2*arr0[i][j-1]+arr0[i+1][j+1]+arr0[i-1][j-1])/16;
	      /*if(pid==p-1)
		{
		  printf("    arr1[i][j]  %lf : (%d,%d)\n",arr1[i][j],i,j);
		  printf("    arr0[i][j]  %lf : (%d,%d)\n",arr0[i][j],i,j);
		  printf("    arr0[i+1][j]  %lf : (%d,%d)\n",arr0[i+1][j],i+1,j);
		  printf("    arr0[i-1][j]  %lf : (%d,%d)\n",arr0[i-1][j],i-1,j);
		  printf("    arr0[i][j+1]  %lf : (%d,%d)\n",arr0[i][j+1],i,j+1);
		  printf("    arr0[i][j-1]  %lf : (%d,%d)\n",arr0[i][j-1],i,j-1);
		  printf("    arr0[i+1][j+1]  %lf : (%d,%d)\n",arr0[i+1][j+1],i+1,j+1);
		  printf("    arr0[i-1][j-1]  %lf : (%d,%d)\n",arr0[i-1][j-1],i-1,j-1);
		  printf("End of print\n");
		  }*/
	    }
      }
    else
      {
	for(i=start;i<=end;i++)
          for(j=1;j<n-1;j++){
            arr1[i][j]=(4*arr0[i][j]+2*arr0[i+1][j]+2*arr0[i-1][j]+2*arr0[i][j+1]+2*arr0[i][j-1]+arr0[i+1][j+1]+arr0[i-1][j-1])/16;
	    /*if(pid==4)
	      {
		printf("    arr1[i][j]  %lf : (%d,%d)\n",arr1[i][j],i,j);
		printf("    arr0[i][j]  %lf : (%d,%d)\n",arr0[i][j],i,j);
		printf("    arr0[i+1][j]  %lf : (%d,%d)\n",arr0[i+1][j],i+1,j);
		printf("    arr0[i-1][j]  %lf : (%d,%d)\n",arr0[i-1][j],i-1,j);
		printf("    arr0[i][j+1]  %lf : (%d,%d)\n",arr0[i][j+1],i,j+1);
		printf("    arr0[i][j-1]  %lf : (%d,%d)\n",arr0[i][j-1],i,j-1);
		printf("    arr0[i+1][j+1]  %lf : (%d,%d)\n",arr0[i+1][j+1],i+1,j+1);
		printf("    arr0[i-1][j-1]  %lf : (%d,%d)\n",arr0[i-1][j-1],i-1,j-1);
		printf("End of print\n");
		}*/
	  }  
      }
    MPI_Barrier(MPI_COMM_WORLD);

    /*
    arr1[i][j]=(4*arr0[i][j]+2*arr0[i+1][j]+2*arr0[i-1][j]+2*arr0[i][j+1]+2*arr0[i][j-1]+arr0[i+1][j+1]+arr0[i-1][j-1])/16;
    */
    if(p==1)
      for(i=start+1;i<end;i++)
	for(j=1;j<n;j++)
	  arr0[i][j]=arr1[i][j];
    else 
    for(i=start;i<=end;i++)
      for(j=1;j<n-1;j++)
	arr0[i][j]=arr1[i][j];
    MPI_Barrier(MPI_COMM_WORLD);
  }
    

  end_time=MPI_Wtime();
  /*
  printf("arr0[1][1]:%lf from %d\n",arr0[1][1],pid);
  */
  double sum1 =0.0;
  if(p==1)
    {
      for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	  if(i==j)
	    sum1+=arr1[i][j];
      printf("Sum : %lf",sum1);
    }
  
  if(p!=1)
    verification_sum();

    /*for(i=start;i<=end;i++){
    
    for(j=0;j<n;j++)
      if((i==j)&&(arr0[i][j]!=0.3828125))
      printf("Values:%lf(%d,%d)  ",arr0[i][j],i,j);
      }*/
  MPI_Barrier(MPI_COMM_WORLD);
  /*printf("After the iterations : %d\n",pid);*/
  MPI_Barrier(MPI_COMM_WORLD);
  if(pid==2)
    printf("Reached here\n");
  /*for(i=start;i<=end;i++)
    {
      printf("\n");
        printf("%lf(%d,%d)\n",arr0[i][0],i,0);
    }
  */
  /*if(pid==0)
    for(i=0;i<n;i++)
      printf("%lf(%d,%d)\n",arr0[0][i],0,i);
  */
  /*if(pid==0)
    for(i=0;i<n;i++)
      printf("%lf(%d,%d)\n",arr0[2][i],2,i);
  */
  if(pid==0)
    printf("\nTime taken is %lf\n",end_time-start_time);
  
  MPI_Finalize();
  return 0;
}


