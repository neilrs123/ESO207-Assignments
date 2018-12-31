#include<stdio.h>
#include<stdlib.h>

long long int max1(long long int a, long long int b, long long int c)
{
	if(a>=b && a>=c)
		return a;
	else if(b>=a && b>=c)
		return b;
	else if(c>=b && c>= a)
		return c;
}

typedef struct bt_node
{
	struct bt_node *left1;
	struct bt_node* right1;
	struct bt_node* parent1;
	long long int lo;
	long long int hi;
	long long int max;
	struct bt_node *left2;
	struct bt_node* right2;
	struct bt_node* parent2;
} interval;

interval* root2 = NULL;
interval* root1 = NULL;

interval* new_node(long long int lo, long long int hi)
{
	interval* node;
	node = (interval*)malloc(sizeof(interval));
	node->lo = lo;
	node->hi = hi;
	node->max = hi;
	node->left1=NULL;
	node->right1=NULL;
	node->parent1=NULL;
	node->left2=NULL;
	node->right2=NULL;
	node->parent2=NULL;
	return node;
}

void insert1(interval *z)
{
	interval *x,*y;
    if(root1 == NULL)
	{
        root1  = z;
        return;
    }
    x = root1;
    while(x!=NULL)
	{
        y = x;
        if(z->lo < x->lo)
            x = x->left1;
        else if(z->lo == x->lo)
        {
            while(x!=NULL && x->lo==z->lo)
            {
                y=x;
                if(z->hi < x->hi)
                {
                    x=x->left1;
                }
                else
                {
                    x=x->right1;
                }
            }
        }
        else x = x->right1;
    }

    if(z->lo < y->lo)
	{
        y->left1 = z;
        z->parent1 = y;
    }
    else if(z->lo == y->lo)
    {
        if(z->hi<y->hi)
        {
            y->left1 = z;
            z->parent1 = y;
        }
        else
        {
            y->right1 = z;
            z->parent1 = y;
        }
            
    }
    else
	{
	    y->right1 = z;
        z->parent1 = y;
    }
    
    while(z!=root1)
    {
        z=z->parent1;
    	if(z->left1!=NULL && z->right1!=NULL)
    		z->max = max1(z->hi,z->left1->max,z->right1->max);
    	else if(z->left1!=NULL && z->right1==NULL)
    		z->max= max1(z->hi,z->left1->max,z->hi);
    	else if(z->left1==NULL && z->right1!=NULL)
    		z->max= max1(z->hi,z->right1->max,z->hi);
    	else z->max = z->hi;
	}
}

void insert2(interval* z)
{
	interval* x;
	interval* y;
	if(root2 == NULL)
	{
        root2  = z;
        return;
    }
    x = root2;
    while(x!=NULL)
	{
        y = x;
        if(z->hi < x->hi)
            x = x->left2;
        else if(z->hi == x->hi)
        {
            while(x!=NULL && x->hi==z->hi)
            {
                y=x;
                if(z->lo > x->lo)
                    x=x->left2;
                else
                    x=x->right2;
            }
        }
        else x = x->right2;
    }

    if(z->hi < y->hi)
	{
        y->left2 = z;
        z->parent2 = y;
    }
    else if(z->hi == y->hi)
    {
        if(z->lo > y->lo)
        {
            y->left2 = z;
            z->parent2 = y;
        }
        else
        {
            y->right2 = z;
            z->parent2 = y;
        }
            
    }
    else
	{
	    y->right2 = z;
        z->parent2 = y;
    }
}

void insert(interval * z)
{
    insert1(z);
    insert2(z);
}

interval* bst_min1(interval* nd)
{
	if(nd==NULL)	
		return NULL;
	interval* x = nd;
	while(x->left1!=NULL)
		x = x->left1;
	return x;
}

interval* bst_min2(interval* nd)
{
	if(nd==NULL)	
		return NULL;
	interval* x = nd;
	while(x->left2!=NULL)
		x = x->left2;
	return x;
}

interval* bst_max1(interval* nd)
{
	if(nd==NULL)	
		return NULL;
	interval* x = nd;
	while(x->right1!=NULL)
		x = x->right1;
	return x;
}

interval* bst_max2(interval* nd)
{
	if(nd==NULL)	
		return NULL;
	interval* x = nd;
	while(x->right2!=NULL)
		x = x->right2;
	return x;
}


void transplant1(interval* u, interval* v)
{
	interval* y = u->parent1;
	if(y==NULL)
		root1 = v;
	else
	{
		if(u==y->right1)
			y->right1 = v;
		else y->left1 = v;
	}
	if(v!=NULL)
		v->parent1 = y;
	u->parent1 = NULL;
}

void transplant2(interval* u, interval* v)
{
	interval* y = u->parent2;
	if(y==NULL)
		root2 = v;
	else
	{
		if(u==y->right2)
			y->right2 = v;
		else y->left2 = v;
	}
	if(v!=NULL)
		v->parent2 = y;
	u->parent2 = NULL;
}

void fix(interval* z)
{
    if(z->left1!=NULL && z->right1!=NULL)
		z->max = max1(z->hi,z->left1->max,z->right1->max);
	else if(z->left1!=NULL && z->right1==NULL)
		z->max= max1(z->hi,z->left1->max,z->hi);
	else if(z->left1==NULL && z->right1!=NULL)
		z->max= max1(z->hi,z->right1->max,z->hi);
	else z->max = z->hi;
    while(z->parent1!=NULL)
    {
        z=z->parent1;
    	if(z->left1!=NULL && z->right1!=NULL)
    		z->max = max1(z->hi,z->left1->max,z->right1->max);
    	else if(z->left1!=NULL && z->right1==NULL)
    		z->max= max1(z->hi,z->left1->max,z->hi);
    	else if(z->left1==NULL && z->right1!=NULL)
    		z->max= max1(z->hi,z->right1->max,z->hi);
    	else z->max = z->hi;
	}
}

void delete_node(interval* z)
{

	interval* p = z->parent1;
 	interval* y;
	
	if(z->left1 == NULL)
	{
		y=z->right1;
		transplant1(z,y);
		if(y!=NULL)
		    fix(y);
		else if(p!=NULL)
		    fix(p);
	}
		
	else if(z->right1 == NULL)
	{
		y=z->left1;
		transplant1(z,y);
		if(y!=NULL)
		    fix(y);
		else if(p!=NULL)
		    fix(p);
	}
	
	else
	{
		interval* y = bst_min1(z->right1);
		interval* a = y->parent1;
		if(z!=y->parent1)
		{
			transplant1( y, y->right1);
			y->right1 = z->right1;
			y->right1->parent1 = y;
			
		}
		transplant1(z,y);
		y->left1 = z->left1;
		y->left1->parent1 = y;
		if(a!=NULL)
			fix(a);
		else if(y->right1!=NULL)
		    fix(y->right1);
		else fix(y);
	}
	
	if(z->left2 == NULL)
		transplant2(z,z->right2);
	else if(z->right2 == NULL)
		transplant2(z,z->left2);
	else
	{
		interval* y = bst_min2(z->right2);
		if(z!=y->parent2)
		{
			transplant2( y, y->right2);
			y->right2 = z->right2;
			y->right2->parent2 = y;
		}
		transplant2(z,y);
		y->left2 = z->left2;
		y->left2->parent2 = y;
	}
}


interval* losucc(interval* x)
{
	interval* y;
	if(x==NULL)
		return NULL;
	if(x->right1!=NULL)
		return bst_min1(x->right1);
	else 
	{
		y = x->parent1;
		while(y!=NULL)
		{
			if(x == y->left1)
				break;
			x = y;
			y = y->parent1;
		}
		return y;	
	}
}

interval* hisucc(interval* x)
{
	interval* y;
	if(x==NULL)
		return NULL;
	if(x->right2!=NULL)
		return bst_min2(x->right2);
	else 
	{
		y = x->parent2;
		while(y!=NULL)
		{
			if(x == y->left2)
				break;
			x = y;
			y = y->parent2;
		}
		return y;	
	}
}


interval* search(long long int lo, long long int hi)
{
	interval* x = root1;
	while(x!=NULL && x->lo!=lo)
	{
		if(lo < x->lo)
			x = x->left1;
		else x = x->right1;
	}
	if(x!=NULL && x->lo==lo)
	{
		while(x!=NULL && x->lo==lo && x->hi!=hi)
		{
		    if(x->hi < hi)
			    x=x->right1;
			else
			    x=x->left1;
		}
	}
	if(x!=NULL)
	{
	    if(x->lo==lo && x->hi==hi)
	        return x;
	    else 
	        return NULL;
	}
	return x;
}

interval* search1(long long int lo, long long int hi)
{
	interval* x = root1;
	while(x!=NULL && x->lo!=lo)
	{
		if(lo < x->lo)
			x = x->left1;
		else x = x->right1;
	}
	return x;
}

interval* search2(long long int lo, long long int hi)
{
	interval* x = root2;
	while(x!=NULL && x->hi!=hi)
	{
		if(hi < x->hi)
			x = x->left2;
		else x = x->right2;
	}
	return x;
}


void overlap(interval* z)
{
	interval* x = root1;
	while(x!=NULL)
	{
		if(z->lo <= x->hi && x->lo <= z->hi)
		{
			printf("1\n");
			return;
		}
		else if(x->left1!=NULL && x->left1->max >= z->lo)
			x = x->left1;
		else x = x->right1;
	}
	printf("0\n");
}

void print(interval * b)
{
    if(b==NULL) 
        return;
    if(b->parent1!=NULL) 
        printf("%lld-",b->parent1->lo);
    printf("lo: %lld Max: %lld\n",b->lo,b->max);
    print(b->left1);
    print(b->right1);
    return;
}

int main()
{
    long long int i,M,N;
    char c;
    scanf("%lld ",&M);
    while(M--)
    {
    	scanf("%lld ",&N);
    	while(N--)
    	{
    		scanf("%c",&c);
    		//if(!(c=='+'||c=='-'||c=='m'||c=='l'||c=='h'||c=='o'||c=='i'))
    		if(c==' ')
    		{
    		    N++;
    		    continue;
    		}
			switch(c)
			{
				case '+':
				{
					long long int lo,hi;
					scanf("%lld %lld",&lo,&hi);
					scanf("%c",&c);
					interval *a;
					a = new_node(lo,hi);
					insert(a);
					break;
				}
				case '-':
				{
					long long int lo,hi;
					scanf("%lld %lld",&lo,&hi);
					scanf("%c",&c);
					interval* a = search(lo,hi);
					if(a!=NULL)
					{
						delete_node(a);
					}
					break;
				}
				case 'm':
				{
					scanf("%c",&c);
					scanf("%c",&c);
					if(c=='n')
					{
						interval* a=bst_min1(root1);
						if(a==NULL)
						    printf("INVALID\n");
						else
						    printf("[%lld %lld]\n",a->lo, a->hi);
					}
					else if(c=='x')
					{
					    
						interval* a = bst_max2(root2);
						if(a==NULL)
						    printf("INVALID\n");
						else
						    printf("[%lld %lld]\n",a->lo, a->hi);
					}
					scanf("%c",&c);
					break;		
				}
				case 'l':
				{
					for(i=0;i<4;i++)
					{
						scanf("%c",&c);
					}
					long long int lo,hi;
					scanf("%lld %lld",&lo,&hi);
					interval* a = search1(lo,hi);
					if(lo>hi)
					{
					    printf("INVALID\n");
					}
					else if(a==NULL)
					{
						printf("INVALID\n");
					}
					else if(a==bst_max1(root1))
					{
						printf("INVALID\n");
					}
					else 
					{
						a = losucc(a);
						printf("[%lld %lld]\n",a->lo, a->hi);
					}
					scanf("%c",&c);
					break;
				}
				case 'h':
				{
					for(i=0;i<4;i++)
					{
						scanf("%c",&c);
					}
					long long int lo,hi;
					scanf("%lld %lld",&lo,&hi);
					interval* a = search2(lo,hi);
					if(lo>hi)
					{
					    printf("INVALID\n");
					}
					else if(a==NULL)
					{
						printf("INVALID\n");
					}
					else if(a==bst_max2(root2))
					{
						printf("INVALID\n");
					}
					else 
					{
						a = hisucc(a);
						printf("[%lld %lld]\n",a->lo, a->hi);
					}
					scanf("%c",&c);
					break;
				}
				case 'o':
				{
					for(i=0;i<6;i++)
					{
						scanf("%c",&c);
					}
					long long int lo,hi;
					scanf("%lld %lld",&lo,&hi);
					scanf("%c",&c);
					if(root1==NULL)
					{
					    printf("0\n");
					    break;
					}
					interval* a = new_node(lo,hi);
					overlap(a);
					break;
				}
				case 'i':
				{
					scanf("%c",&c);
					print(root1);
					break;
				}
			}	
		}
		root1=NULL;
		root2=NULL;
	}
    return 0;
}

