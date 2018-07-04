#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include<ctype.h>

struct dlist_node int_list;
struct dlist_node* p_int_list = &int_list;


void list_app_main()
{
    struct dlist_node* p_int_list, *p_str_list;
    struct dlist_node* pre_node;
    int n,max,sum;
    n = max = sum = 0;
    int data[10] = {11,40,32,12,67,4,52,85,21,31};
    char str1[] = "hello world!";
    char str2[] = "luojiao";
    char str3[] = "wangfan";
    char* p_str[] = {str1, str2, str3};

    p_int_list = dlist_init(10);
    p_str_list = dlist_init(3);

    pre_node = p_int_list;

    do{
        pre_node->data = (void*)data[n];
        n++;
        pre_node = pre_node->next;

    }while((pre_node != p_int_list) && (n < 10));

    n = 0;
    pre_node = p_str_list;

    do{
        pre_node->data = p_str[n];
        n++;
        pre_node = pre_node->next;

    }while((pre_node != p_str_list) && (n < 3));

    dlist_foreach(p_int_list,print_int,NULL);
    dlist_foreach(p_int_list,find_max,&max);
    dlist_foreach(p_int_list,cal_total,&sum);

    dlist_foreach(p_str_list,print_str,NULL);
    dlist_foreach(p_str_list,str_toupper,NULL);
    dlist_foreach(p_str_list,print_str,NULL);
    printf("\n the max value is : %d\n",max);
    printf("\n the total value is : %d\n",sum);

}
