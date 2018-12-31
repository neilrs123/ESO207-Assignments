#include<stdio.h>
#include<stdlib.h>

typedef struct nd
{
	int key;
	nd* next;
}node;


int *colour;
int *disc;
int *finish;
int *parent;
int time;
int state;
int ans;

void dfsvisit(int u,int a, int b, node** adj)
{
	int v;
	time++;
	disc[u]=time;
	colour[u]=1;					//gray
	node* ptr;
	ptr = adj[u];
	while(ptr!=NULL)
	{
		v=ptr->key;
		if(u==a && v == b || u==b && v==a)
		{
			if(colour[v]==1)
			{
				ans=1;
				state=1;
				return;
			}
			else if(colour[v]==0)
			{
				parent[v]=u;
				state=2;
				dfsvisit(v,a,b,adj);
			}
		}
		else
		{
			if(state==2 && colour[a]==1 && colour[b]==1)
			{
				if(colour[v]==1)
				{
					if(disc[v]<disc[a] && disc[v] < disc[b])
					{
						ans=1;
						return;
					}
				}
			}
			else if(colour[v]==0)
			{
				colour[v]=1;
				parent[v]=1;
				dfsvisit(v,a,b,adj);
			}
		}
		ptr=ptr->next;
	}
	colour[u]=2;						//black
	time++;
	finish[u]=time;
	
	if(u==a || u==b)
		return;								
}

int dfs(int ver, node** adj, int a, int b)
{
	int i;
	time=0;
	state =0;
	ans =0;
	for(i=1;i<=ver;i++)
	{
		colour[i]=0;				//white
		parent[i]=-1;
	}
	dfsvisit(a,a,b,adj);
	return ans;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int i,v;
		scanf("%d",&v);
		node** adj;
		adj = (node**)malloc((v+1)*sizeof(node*));
		for(i=1;i<=v;i++)
		{
			adj[i]=NULL;
		}
		int e;
		scanf("%d",&e);
		int n1,n2;
		node* ptr;
		for(i=0;i<e;i++)
		{
			scanf("%d",&n1);
			scanf("%d",&n2);				//undirected graph
			node* nd1,* nd2;
			nd1=(node*)malloc(sizeof(node));
			nd2=(node*)malloc(sizeof(node));
			nd1->key=n1;
			nd2->key=n2;
			//printf("%d %d\n",nd1->key, nd2->key);
			nd1->next = NULL;
			nd2->next = NULL;
			if(adj[n1]==NULL)
				adj[n1]=nd2;
			else
			{
				ptr = adj[n1];
				while(ptr->next!=NULL)
				{
					ptr = ptr->next;
				}
				ptr->next=nd2;
			}
			
			if(adj[n2]==NULL)
				adj[n2]=nd1;
			else
			{
				ptr = adj[n2];
				while(ptr->next!=NULL)
				{
					ptr = ptr->next;
				}
				ptr->next=nd1;
			}	
		}
		int a,b;
		scanf("%d %d",&a,&b);
		disc=(int*)malloc(v*sizeof(int));
		parent=(int*)malloc(v*sizeof(int));
		finish=(int*)malloc(v*sizeof(int));
		colour=(int*)malloc(v*sizeof(int));
		int ans = dfs(v,adj,a,b);
		if(ans==1)
		{
			printf("Not Bridge\n");
		}
		if(ans==0)
		{
			printf("Bridge\n");
		}
		free(disc);
		free(parent);
		free(finish);
		free(colour);
	}
}
