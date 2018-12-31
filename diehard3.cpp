#include <stdio.h>

int P,Q,R;
int ver; 
int left;
int right;
int inf = 100000;

typedef struct nd
{
	int key;
	struct nd* next;
}node;

node** adj;
node** ptr;


void insert(int u, int p, int q, int r)
{
    int v = left*p+right*q+r;
    node* pt = (node*)malloc(sizeof(node));
    pt->key = v;
    pt->next = NULL;
    if(adj[u] == NULL)
    {
        adj[u]=pt;
        ptr[u]=pt;
    }
    else
    {
        ptr[u]->next = pt;
        ptr[u] = pt;
    }
}

void generatevertices(int *arr, int u)
{
    int p,q,r;
    p=u/left;
 	q= (u%left)/right;
    r= (u%left)%right;
    left*p+right*q+r;
    if(p!=0)
    {
        if(arr[left*0+right*q+r]==0)
        {
            insert(u,0,q,r);
            arr[left*0+right*q+r]=1;
        }
        if(p+q<=Q)
        {
            if(arr[left*0+right*(p+q)+r]==0)
            {
                insert(u,0,p+q,r);
                arr[left*0+right*(p+q)+r]=1;
            }    
        }
        else
        {
            if(arr[left*(p-Q+q)+right*Q+r]==0)
            {
                insert(u,p-Q+q,Q,r);
                arr[left*(p-Q+q)+right*Q+r]=1;
            }
        }
        if(p+r<=R)
        {
            if(arr[left*0+right*q+r+p]==0)
            {
                insert(u,0,q,r+p);
                arr[left*0+right*q+r+p]=1;
            }    
        }
        else
        {
            if(arr[left*(p-r+R)+right*q+R]==0)
            {
                insert(u,p-R+r,q,R);
                arr[left*(p-r+R)+right*q+R]=1;
            }
        }
    }
    
    if(q!=0)
    {
        if(arr[left*p+right*0+r]==0)
        {
            insert(u,p,0,r);
            arr[left*p+right*0+r]=1;
        }
            
        if(p+q<=P)
        {
            if(arr[left*(p+q)+right*0+r]==0)
            {
                insert(u,p+q,0,r);
                arr[left*(p+q)+right*0+r]=1;
            }    
        }
        else
        {
            if(arr[left*P+right*(p-P+q)+r]==0)
            {
                insert(u,P,p-P+q,r);
                arr[left*P+right*(p-P+q)+r]=1;
            }
        }
        if(q+r<=R)
        {
            if(arr[left*p+right*0+r+q]==0)
            {
                insert(u,p,0,r+q);
                arr[left*p+right*0+r+q]=1;
            }    
        }
        
        else
        {
            if(arr[left*p+right*(q+r-R)+R]==0)
            {
                insert(u,p,q+r-R,R);
                arr[left*p+right*(q+r-R)+R]=1;
            }
        }
    }
    
    if(r!=0)
    {
        if(arr[left*p+right*q+0]==0)
        {
            insert(u,p,q,0);
            arr[left*p+right*q+0]=1;
        }
        if(r+q<=Q)
        {
            if(arr[left*p+right*(q+r)+0]==0)
            {
                insert(u,p,q+r,0);
                arr[left*p+right*(q+r)+0]=1;
            }    
        }
        
        else
        {
            if(arr[left*p+right*Q+r-Q+q]==0)
            {
                insert(u,p,Q,r-Q+q);
                arr[left*p+right*Q+r-Q+q]=1;
            }
        }
        
        if(p+r<=P)
        {
            if(arr[left*(p+r)+right*q+0]==0)
            {
                insert(u,p+r,q,0);
                arr[left*(p+r)+right*q+0]=1;
            }    
        }
        
        else
        {
            if(arr[left*P+right*q+p+r-P]==0)
            {
                insert(u,P,q,p+r-P);
                arr[left*P+right*q+p+r-P]=1;
            }
        }
    }
}

void bfs(int s, int* arr)
{
	int i;
	int colour[ver];
	int parent[ver];
	int d[ver];
	for(i=0;i<ver;i++)
	{
		colour[i]=0;
		parent[i]=-1;
		d[i]=inf;
	}
	colour[s]=1;			//gray
	parent[s]= -1;
	d[s]=0;
	int v;
	int u;
	node* pt = adj[s];
	
    int a,b,c;
    int first = 0;
    int last = 0;
    int queue[ver];
    queue[first]=s;
	while(1)
	{
	    if(first>last)
     		break;
		
		u = queue[first];
		first++;
		generatevertices(arr,u);
 		pt = adj[u];
//  		while(pt!=NULL)
//         {
//         	v = pt->key;
//         	a=v/left;
// 			b= (v%left)/right;
//     		c= (v%left)%right;
//     		printf("%d %d %d\n",a,b,c);
// 			pt=pt->next;
//         }

		while(pt!=NULL)
		{
			v = pt->key;
			if(colour[v]==0)
			{
				parent[v]=u;
				d[v]=d[u]+1;
				colour[v]=1;
				queue[last+1]=v;
				last++;
			}
			pt=pt->next;
		}
		colour[u]=2;				//black
	}
	
	int N;
	scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d %d %d",&a,&b,&c);
        u = left*a+right*b+c;
        if(u>ver-1)
        {
            printf("IMPOSSIBLE\n");
        }
        else if(arr[u]==1)
        {
            printf("%d\n",d[u]+1);
        }
        else if(arr[u]==0)
        {
            printf("IMPOSSIBLE\n");
        }
    }
}


int main()
{
    int T,i,j,k;
    scanf("%d",&T);
    int p,q,r;
    int N,u,v;
    while(T--)
    {
        scanf("%d %d %d",&P,&Q,&R);
        ver = (P+1)*(Q+1)*(R+1);
        int* arr = (int*)calloc(ver,(sizeof(int)));
        adj = (node**)malloc(ver*sizeof(node*));
        ptr = (node**)malloc(ver*sizeof(node*));
        for(i=0;i<ver;i++)
        {
            adj[i]=NULL;
            ptr[i]=NULL;
        }
        left = (Q+1)*(R+1);
        right = R+1;
        scanf("%d %d %d",&p,&q,&r);
        v = left*p+right*q+r;
        arr[v]=1;
        //printf("%d\n",v);
        bfs(v,arr);
        
        //generatevertices(arr,v);
//         node* pt = adj[v];
//         while(pt!=NULL)
//         {
//         	v = pt->key;
//         	p=v/left;
// 			q= (v%left)/right;
//     		r= (v%left)%right;
//     		printf("%d %d %d\n",p,q,r);
// 			pt=pt->next;
//         }
        //insert(v,0,0,0);
    }
}
