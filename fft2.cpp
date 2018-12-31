#include<stdio.h>
#include<math.h>
#include<stdlib.h>


typedef struct Num
{
	long double x;
	long double y;
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
		long double theta = 2*M_PI/(double)n;
		wn.x = cosl(theta);
		wn.y = sinl(theta);
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

num* invfft(num* a, int n)
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
		
		num wn;
		long double theta = -2*M_PI/(double)n;
		wn.x = cosl(theta);
		wn.y = sinl(theta);
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

int main()
{
	int n,i,m;
	scanf("%d %d",&n,&m);
	num *a;
	a=(num*)malloc(n*sizeof(num));
	num *b;
	b=(num*)malloc(m*sizeof(num));
		
	for(i=0;i<n;i++)
	{
		scanf("%Lf",&(a[i].x));
	}
	for(i=0;i<n;i++)
	{
		scanf("%Lf",&(a[i].y));
	}
	
	for(i=0;i<m;i++)
	{
		scanf("%Lf",&(b[i].x));
	}
	
	for(i=0;i<m;i++)
	{
		scanf("%Lf",&(b[i].y));
	}
	
	int n2;
	if(n+m-1!=1)
		n2 = pow(2,ceil(log((double)(n+m-1))/log(2)));
	else 
		n2 = 2;
	a = (num*)realloc(a,n2*sizeof(num));
    for(i=n;i<n2;i++)
    {
        a[i].x = 0;
        a[i].y = 0;
    }
    b = (num*)realloc(b,n2*sizeof(num));
    for(i=m;i<n2;i++)
    {
        b[i].x = 0;
        b[i].y = 0;
    }

	num* ya;
	ya = (num*)malloc(n2*sizeof(num));
	ya = recfft(a,n2);

	num* yb;
	yb = (num*)malloc(n2*sizeof(num));
	yb = recfft(b,n2);
		
	num* y;
	y = (num*)malloc(n2*sizeof(num));
	for(i=0;i<n2;i++)
	{
		y[i]=prod(ya[i],yb[i]);
	}
	/*
	for(i=0;i<n+m-1;i++)
	{
		
		printf("%0.5lf ",y[i].x);
	}
	printf("\n");
	
	for(i=0;i<n+m-1;i++)
	{
		printf("%0.5lf ",y[i].y);
	}
	printf("\n");
	*/
	num *c;
	c=(num*)malloc(n2*sizeof(num));
	c = invfft(y,n2);
	for(i=0;i<n2;i++)
	{
		c[i].x=(c[i].x)/(long double)n2;
		c[i].y=(c[i].y)/(long double)n2;
	}
		
	for(i=0;i<n+m-1;i++)
	{	
	    if(c[i].x>-pow(10,-9) && c[i].x<0)
	        printf("0.00000 ");
	    else
		    printf("%0.5Lf ",c[i].x);
	}
	printf("\n");
	
	for(i=0;i<n+m-1;i++)
	{
	    if(c[i].y>-pow(10,-9) && c[i].y<0)
	        printf("0.00000 ");
	    else
		    printf("%0.5Lf ",c[i].y);
	}
	
	return 0;
}
