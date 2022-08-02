	#include<stdio.h>
	#include<stdlib.h>
	extern int RandInt(int i, int j);
	
	void Swap(int *p,int *q)
	{int t=*p; *p=*q; *q=t;}
	
	void RandomPermutation1(int n)
	{
		if (n-(int)n!=0||n<=0){
			printf("error");
		}else{
			int *A;
			A=(int*)calloc(n,sizeof(int));
			int i,j,m;
			for(m=0;m<n;m++)
	 		{
			 	A[m]=RandInt(1,n);
	  			for(j=0;j<m;j++)
	    			if(A[j]==A[m]){
	    				m--;
	    				break;
					}
			}
	
			for(i=0;i<n;i++)
			{
				printf("%d,",A[i]);
			}
			printf("0\n");
		} 
	 } 
	
	void RandomPermutation2(int n)
	{
		if (n-(int)n!=0||n<=0){
			printf("error");
		}else{
			int *A;
			A=(int*)calloc(n,sizeof(int));
			int *Used;
			Used=(int*)calloc(n,sizeof(int));
			int i,m;
			for(m=0;m<n;m++)
				{
					A[m]=RandInt(1,n);
					if(Used[A[m]]==1)
					{
						m--;
					}
				    else{	
				    	Used[A[m]]=1;
					}
				}
	
			for(i=0;i<n;i++)
			{
				printf("%d,",A[i]);
			}
			printf("0\n");
		} 
	}
	
	void RandomPermutation3(int n){
		if (n-(int)n!=0||n<=0){
			printf("error");
		}else{
			int *A;
			A=(int*)calloc(n,sizeof(int));
			int i,j,k;
			for(j=0;j<n;j++)
			{	
				A[j]=j+1;
			}
			for(i=1;i<n;i++)
			{
				Swap(&A[i],&A[RandInt(0,i)]);
			}
	
			for(k=0;k<n;k++)
			{
				printf("%d,",A[k]);
			}
			printf("0\n");
		} 
	}
	
	int main()
	{
		void RandomPermutation1(int n);
		void RandomPermutation2(int n);
		void RandomPermutation3(int n);
		float n;
		scanf("%f",&n);
		if (n-(int)n!=0||n<=0){
			printf("error");
		}else{
			n=(int)n;
			RandomPermutation1(n);
			RandomPermutation2(n);
			RandomPermutation3(n);
		}
		return 0;
	}
