#include<stdio.h>
#include<math.h>
#include<stdlib.h>


typedef struct Num
{
	double x;
	double y;
}num;

num prod(num n1, num n2)
{
	num n;
	n.x = (n1.x)*(n2.x) - (n1.y)*(n2.y);
	n.y = (n1.x)*(n2.y) + (n1.y)*(n2.x);
	return n; 
}

num sum(num n1, num n2)
{
	num n;
	n.x = (n1.x) + (n2.x);
	n.y = (n1.y) + (n2.y);
	return n; 
}

num* recfft(num* a, int n)
{
	if(n==1)
		return a;
	else
	{
		num *aodd;
		num *aeven;
		aodd=(num*)malloc((n/2)*sizeof(num));
		aeven=(num*)malloc((n/2)*sizeof(num));
		int i,j=0,k=0;
		for(i=0;i<n;i++)
		{
			aeven[k] = a[i];
			k++;
			i++;
			aodd[j] = a[i];
			j++;
		}
		num *yodd, *yeven;
		yodd=(num*)malloc((n/2)*sizeof(num));
		yeven=(num*)malloc((n/2)*sizeof(num));
		yodd = recfft(aodd, n/2);
		yeven = recfft(aeven,n/2);
		num* y;
		y=(num*)malloc(n*sizeof(num));
		
		num wn;
		double theta = 2*M_PI/(double)n;
		wn.x = cos(theta);
		wn.y = sin(theta);
		num w;
		w.x=1;
		w.y=0;
		num sign;
		sign.x=-1;
		sign.y=0;
		for(i=0;i<n/2;i++)
		{
			num a1 = prod(w,yodd[i]);
			y[i]= sum(yeven[i],a1);
			y[i+n/2]= sum(yeven[i],prod(sign,a1));
			w = prod(w,wn);	
		}
		return y;
		
	}
}

/*
num* invfft(num a[], int n)
{
	if(n==1)
		return a;
	else
	{
		num *aodd;
		num *aeven;
		aodd=(num*)malloc((n/2)*sizeof(num));
		aeven=(num*)malloc((n/2)*sizeof(num));
		int i,j=0,k=0;
		for(i=0;i<n;i++)
		{
			aeven[k] = a[i];
			k++;
			i++;
			aodd[j] = a[i];
			j++;
		}
		num *yodd, *yeven;
		yodd=(num*)malloc((n/2)*sizeof(num));
		yeven=(num*)malloc((n/2)*sizeof(num));
		yodd = invfft(aodd, n/2);
		yeven = invfft(aeven,n/2);
		num* y;
		y=(num*)malloc(n*sizeof(num));
		j=0;
		for(i=0;i<n;i++)
		{
			y[i] = yeven[i];
			i++;
			y[i] = yodd[j];
			j++;
		}
		
		num wn;
		double theta = 6.2831853/(double)n;
		wn.x = cos(theta);
		wn.y = sin(theta);
		num w;
		w.x=1;
		w.y=0;
		num sign;
		sign.x=-1;
		sign.y=0;
		for(i=0;i<n/2;i++)
		{
			num a1 = prod(w,yodd[i]);
			y[i]= sum(yeven[i],a1);
			y[i+n/2]= sum(yeven[i],prod(sign,a1));
			w = prod(w,wn);	
		}
		for(i=0;i<n;i++)
		{
			y[i].x=(y[i].x)/(double)n;
			y[i].y=(y[i].y)/(double)n;
		}
		
		return y;
		
	}
}*/

int main()
{
	int n,i,d;
	scanf("%d",&d);
	num *a;
	a=(num*)malloc(d*sizeof(num));
		
	for(i=0;i<d;i++)
	{
		scanf("%lf",&(a[i].x));
	}
	
	for(i=0;i<d;i++)
	{
		scanf("%lf",&(a[i].y));
	}
	scanf("%d",&n);
    a = (num*)realloc(a,n*sizeof(num));
    for(i=d;i<n;i++)
    {
        a[i].x = 0;
        a[i].y = 0;
    }
	
	num* y;
	y = (num*)malloc(n*sizeof(num));
	y=recfft(a,n);
	//num *b;
	//b=(num*)malloc(n*sizeof(num));
	//b = invfft(y,n);
	for(i=0;i<n;i++)
	{
		printf("%0.5lf ",y[i].x);
	}
	printf("\n");
	
	for(i=0;i<n;i++)
	{
		printf("%0.5lf ",y[i].y);
	}
	
	/*for(i=0;i<n;i++)
	{
		printf("%0.2lf (%0.2lf)\n",b[i].x,b[i].y);
	}*/
	return 0;
}
