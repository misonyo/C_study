/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <assert.h>
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef struct exp
{
	int ch;
	int flag;	/* 0:number,1:operator */
	struct exp *pre;
	struct exp *next;
}exp_t;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static exp_t *listhead=NULL,*listtail=NULL;
/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */
void exp_list_print(void)	/*打印链表*/
{
	exp_t *temp;
	for(temp=listhead;temp != NULL;temp=temp->next)
	{
		if(temp->flag==0)
		{
			printf("%d",temp->ch);
		}
		else
		{
			printf("%c",temp->ch);
		}
	}
	printf("\n");
}
void exp_malloc_list(int number,int flag)	/*建立链表*/
{
	exp_t *temp;
	temp=malloc(sizeof(exp_t));
	temp->ch=number;
	temp->flag=flag;
	temp->pre=listtail;
	temp->next=NULL;
	if(listtail != NULL)
	{
		listtail->next=temp;
	}
	listtail=temp;
	if(listhead == NULL)
	{
		listhead=temp;
	}
}
void exp_insert(void)	/*遍历链表，往包含乘除法的表达式里插入括号，在乘除法前后添加括号，便于后面计算*/
{
	exp_t *temp,*ch1;
	int flag2=0,flag3=0;
	for(temp=listhead;temp != NULL;temp=temp->next)
	{
		if(0==flag2)
		{
			if(temp->flag==1)
			{
				if(((temp->ch == '*') || (temp->ch == '/')) && (temp->pre->ch != ')'))
				{
					ch1=malloc(sizeof(exp_t));
					ch1->ch='(';
					ch1->flag=1;
					ch1->pre=temp->pre->pre;
					ch1->next=temp->pre;
					if(temp->pre->pre != NULL)
					{
						temp->pre->pre->next=ch1;
					}
					else
					{
						listhead=ch1;
					}
					temp->pre->pre=ch1;
					flag2=1;
				}
			}
		}
		else	//1==flag2
		{
			if(temp->flag==1)
			{

				if((temp->ch == '('))
				{
					flag3=1;
				}
				else if((temp->ch == ')'))
				{
					flag3=0;
					if(temp->next == NULL)
					{
						ch1=malloc(sizeof(exp_t));
						ch1->ch=')';
						ch1->flag=1;
						ch1->pre=temp;
						ch1->next=NULL;
						temp->next=ch1;
						listtail=ch1;
						flag2=0;
					}
				}
				else if(((temp->ch == '+') || (temp->ch == '-')) && (flag3==0))
				{
					ch1=malloc(sizeof(exp_t));
					ch1->ch=')';
					ch1->flag=1;
					ch1->pre=temp->pre;
					ch1->next=temp;
					temp->pre->next=ch1;
					temp->pre=ch1;
					flag2=0;
				}
			}
			else if((temp->flag==0) && (temp->next==NULL))
			{
				ch1=malloc(sizeof(exp_t));
				ch1->ch=')';
				ch1->flag=1;
				ch1->pre=temp;
				ch1->next=NULL;
				temp->next=ch1;
				listtail=ch1;
				flag2=0;
			}
		}
	}
}
exp_t * eval_StrToList(const char *expr)	/*表达式字符串保存为链表*/
{
	int number=0;
	while(*expr != '\0')
	{
		if((*expr >='0') && (*expr <='9')) //if char is number
		{
			while((*expr >='0') && (*expr <='9'))
			{
				number = number*10 + (*expr) - '0';
				expr++;
			}
			exp_malloc_list(number,0);/*０：数值，*字符２３４按数值２３４存放于链表里*/
		}
		if((*expr) != '\0')
		{
			exp_malloc_list(*expr,1);/*1:字符，存放字符*/
			expr++;
		}
		number=0;
	}
	return listhead;
}
int eval_list(exp_t **temp)	/*计算表达式（每个字符都放入了链表，遍历链表计算）的值，可计算加减乘除*/
{
	int number=0,result=0;
	char operator='+';
	while(*temp != NULL)
	{
		if((*temp)->flag==1)
		{
			if((*temp)->ch == '(')
			*temp=(*temp)->next;
			number = eval_list(temp);
		}
		else
		{
			number=(*temp)->ch;
			*temp=(*temp)->next;
		}
		switch(operator)
		{
			case '+':
				result=result+number;
				break;
			case '-':
				result=result-number;
				break;
			case '*':
				result=result*number;
				break;
			case '/':
				result=result/number;
				break;
		}
		if((*temp != NULL) && ((*temp)->flag==1))
		{
			if((*temp)->ch == ')')
			{
				*temp=(*temp)->next;
				break;
			}

			if((*temp)->ch != '\0')
			{
				operator=(*temp)->ch;
				*temp=(*temp)->next;
			}
		}
	}
	return result;
}
char* eval_ListToChar(exp_t *listhead)	/*把放入链表的表达式（一个一个字符存放，乘除法前后加了括号后）转化成字符串*/
{
	exp_t *temp;
	char *str;
	int len=0;
	str=malloc(512);
	assert(str != NULL);
	for(temp=listhead;temp != NULL;temp=temp->next)
	{
		if(1 == temp->flag)
		{
			len+=snprintf(&str[len],512-len,"%c",temp->ch);
		}
		else
		{
			len+=snprintf(&str[len],512-len,"%d",temp->ch);
		}
	}
	str[len]='\0';
	printf("str=%s\n",str);
	return str;
}
int eval_str(const char **expr)	/*计算包含括号的表达式（字符串）的值，不能直接计算乘除法（需先添加括号）*/
{
	int number=0;
	int result=0;
	char operator = '+';

	while(**expr != '\0')
	{
		if(**expr == '(')
		{
			(*expr)++;
			number = eval_str(expr);
		}
		else
		{
			while((**expr != ')') && (**expr != '+') && (**expr != '-') && (**expr !=  '*') && (**expr != '/') && (**expr != '\0'))
			{
				number = number*10 + (**expr) - '0';
				(*expr)++;
			}
		}

		switch(operator)
		{
			case '+':
				result=result+number;
				break;
			case '-':
				result=result-number;
				break;
			case '*':
				result=result*number;
				break;
			case '/':
				result=result/number;
				break;
		}

		if(**expr == ')')
		{
			(*expr) ++;
			break;
		}

		if(**expr != '\0')
		{
			operator=**expr;
			(*expr) ++;
		}

		number = 0;
	}
	return result;
}
void eval_CalList(const char *expr)
{
	int result;
	exp_t *head=eval_StrToList(expr);
	exp_insert();
	exp_list_print();

	result=eval_list(&head);
	printf("eval_CalList result=%d\n",result);
}
void eval_CalStr(const char *expr)
{
	int result;
	const char *str;
	exp_t *head=eval_StrToList(expr);
	exp_insert();
	exp_list_print();

	str=eval_ListToChar(head);
	result=eval_str(&str);
	printf("eval_CalStr result=%d\n",result);
}
void eval_main(const char *expr)
{

	//eval_CalList(expr);
	eval_CalStr(expr);
}
