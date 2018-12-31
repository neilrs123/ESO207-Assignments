
#include<stdio.h>
#include<stdlib.h>

typedef struct inp
{
	char s;
	int type;
	int pri;
}ch;

typedef struct Stack
{
	ch *c;
	int top;
}stack;

// void make_empty(stack s)
// {
// 	s.top=1;
// }

int is_empty(stack s)
{
	return s.top==1;
}

// int is_full(stack s)
// {
// 	return s.top == 1001;
// }

int push(stack s, ch c)
{
		s.c[s.top] = c;
		return 1;
}

ch top(stack s)
{
	if(is_empty(s))
	{
		ch c;
		c.type=10;
		return c;
	}
		
	else return s.c[s.top-1];
}

ch pop(stack s)
{
	if(is_empty(s))
	{
		ch c;
		c.type=10;
		return c;
	}
	else
	{
		ch val = s.c[s.top-1];
		return val;
	} 
}

int main()
{
	int i,T;
	int flag = 0;
	stack st;
	st.c = (ch*)malloc(1000*sizeof(ch));
	ch *exp;
	int j=0;
	
	ch *post;
	post = (ch*)malloc(1000*sizeof(ch));
    scanf("%d\n",&T);
	char s[1000];
	
	while(T--)
	{
	    exp = (ch*)malloc(1000*sizeof(ch));
	    flag =0;
		gets(s);
		int n2 = 0;
		while(1)
		{
		    if(s[n2]=='\0')
    			break;
    		n2++;
    		
		}
	    j=0;
    	for(i=0;i<=n2;i++)
    	{
    		if(s[i]==EOF || s[i]=='\n')
    			break;
    		else if(s[i]=='(')
    		{
    			exp[j].s='(';
    			exp[j].type = 3;
    			exp[j].pri = 1;
    			j++;
    		}
    		else if(s[i]==')')
    		{
    			exp[j].s=')';
    			exp[j].type = 3;
    			exp[j].pri = 2;
    			j++;
    		}
    		else if(s[i]=='/')
    		{
    			exp[j].s='/';
    			exp[j].type = 2;
    			exp[j].pri = 3;
    			j++;
    		}
    		else if(s[i]=='%')
    		{
    			exp[j].s='%';
    			exp[j].type = 2;
    			exp[j].pri = 3;
    			j++;
    		}
    		else if(s[i]=='*')
    		{
    			exp[j].s='*';
    			exp[j].type = 2;
    			exp[j].pri = 2;
    			j++;
    		}
    		else if(s[i]=='+')
    		{
    			exp[j].s='+';
    			exp[j].type = 2;
    			exp[j].pri = 1;
    			j++;
    		}
    		else if(s[i]=='-')
    		{
    			exp[j].s = '-';
    			exp[j].type = 2;
    			exp[j].pri = 1;
    			j++;
    		}
    		else if(s[i]>='0' && s[i]<='9')
    		{
    			int y = 0;
    			while(s[i]>='0' && s[i]<='9')
    			{
    				y = 10*y + (s[i]-'0');
    				i++;
    			}
    			i--;
    			exp[j].pri = y;
    			exp[j].type = 1;
    			j++;
    		}
    		else if(s[i]=='^')
    		{
    		    exp[j].s = '^';
    		    exp[j].type = 5;
    		    j++;
    		}
    	}
    	int n = j;
//     	for(j=0;j<n;j++)
// 		{
// 			if(exp[j].type==1)
// 				printf("%d ",exp[j].pri);
// 			else
// 				printf("%c ",exp[j].s);
// 		} 
// 		printf("\n");
		
    	
    	if(n<=2)
    	{
    	    flag = 1;
    	}
    	if(!(exp[n-1].type==1 || exp[n-1].s==')'))
    	{
    	    flag = 1;
    	}
    	if(exp[0].type==2 || exp[0].type==5)
    	{
    	    flag = 1;
    	}
    	for(j=0;j<n-1;j++)
    	{
    	    if(exp[j].type==1 && exp[j+1].s == '(')
    	    {
    	        flag = 1;
    	        break;
    	    }
    	    if(exp[j+1].type==1 && exp[j].s==')')
    	    {
    	        flag = 1;
    	        break;
    	    }
    	    if(exp[j+1].type==2 && exp[j].s == '(')
    	    {
    	        flag = 1;
    	        break;
    	    }
    	    if(exp[j].type==2 && exp[j+1].s==')')
    	    {
    	        flag = 1;
    	        break;
    	    }
    	    if(exp[j].type==exp[j+1].type)
    	    {
    	        if(exp[j].s=='(' || exp[j].s == ')')
    	            continue;
    	        flag = 1;
    	        break;
    	    }
    	    if(exp[j].type == 2 )
    	    {
    	        if(exp[j+1].s == '^')
    	        {
    	            flag = 1;
    	            break;
    	        }
    	    }
    	    if(exp[j].s == '(' && exp[j+1].s=='^')
    	    {
    	        flag =1;
    	        break;
    	    }
    	    if(exp[j].s == '^')
    	    {
    	        if(exp[j+1].type ==2)
    	        {
    	            flag =1;
    	            break;
    	        }
    	        if(exp[j+1].s==')')
    	        {
    	            flag =1;
    	            break;
    	        }
    	    }
    	}
    	int bracket=0;
    	for(j=0;j<n;j++)
    	{
    	    if(exp[j].s == '(')
    	        bracket++;
    	    if(exp[j].s==')')
    	        bracket--;
    	    if(bracket<0)
    	    {
    	        flag = 1;
    	        break;
    	    }
    	}
    	if(bracket!=0)
    	{
    	    flag = 1;
    	}

		
		
// 		printf("%d",n);
        st.top=1;
        if(flag!=1)
        {
    		i = 0;
    		for(j=0;j<n;j++)
    		{
    			if(exp[j].type==1)
    			{
    				post[i] = exp[j];
    				i++;
    			}
    			else if(exp[j].s == '(')
    			{
    				push(st,exp[j]);
    				st.top = st.top+1;
    			}
    			
    			else if(exp[j].s == ')')
    			{
    				flag = 0;
    				int flag2 =0;
    				int count = 0;
    				while(1)
    				{
    					ch d = pop(st);
    					if(d.pri==10)
    					{
    						flag = 1;
    						break;
    					}
    					st.top = st.top-1;
    					count ++;
    					if(d.s=='(')
    					{
    					    flag2=1;
    					    count--;
    						break;
    					}
    						
    					post[i] = d;
    					i++;
    				}
    				if(count == 0 || flag2==0)
    				    flag = 1;
    				if(flag==1)
    					break;
    			}
    			else if(exp[j].type == 2)
    			{
    				ch tp = top(st);
    				if(tp.type==10 || tp.s=='(' )
    				{	
    					push(st,exp[j]);
    					st.top = st.top+1;
    				}
    				else
    				{
    					//while(!(is_empty(st)) && ((tp.type == 2 && tp.pri>=exp[j].pri)||(tp.s=='^')))
    					while(1)
    					{
    					    if(is_empty(st))
    					        break;
    						else if(tp.type==3)
    							break;
    						else if(tp.s=='^')
    						{
    						    ch d = pop(st);
    						    st.top = st.top-1;
    						    post[i] = d;
    						    i++;
    						    tp = top(st);
    						}
    						else if((tp.type == 2 && tp.pri>=exp[j].pri))
    						{
    						    ch d = pop(st);
    						    st.top = st.top-1;
    						    post[i] = d;
    						    i++;
    						    tp = top(st);
    						}
    						else break;
    					}
    					push(st,exp[j]);
    					st.top = st.top + 1;
    				}
    			}
    			else if(exp[j].s == '^')
    			{
    			    push(st,exp[j]);
    			    st.top = st.top + 1;
    			}
    		}
        }
		if(flag==1)
		{
		    printf("INVALID");
		}
		if(flag!=1)
		{
    		while(!(is_empty(st)))
    		{
    			ch d=pop(st);
    			if(d.type == 10)
				    break;
    			st.top = st.top-1;
    			if(d.s=='(')
    			{
    			    printf("INVALID");
    			    flag = 1;
    			    break;
    			}
    			post[i]=d;
    			i++;
    		}
		}
		if(flag!=1)
		{
    		int nf=i;
    		for(j=0;j<nf;j++)
    		{
    			if(post[j].type==1)
    				printf("%d ",post[j].pri);
    			else
    				printf("%c ",post[j].s);
    		}
		}
		
		if(T!=0)
		    printf("\n");
    }
    return 0;
}




