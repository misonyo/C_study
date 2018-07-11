/*
 *
 *        File:list_app.c
 *  Created on: 2018Äê6ÔÂ27ÈÕ
 *      Author: misonyo
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#include "ms_def.h"
#include <windows.h>

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
struct dlist_tcb
{
    struct dlist_node* list_head;
    ms_int32_t node_count;
};
/* ============================ [ DECLARES  ] ====================================================== */
pthread_mutex_t dlist_mutex;
pthread_t product_tid, consumer_tid;
struct dlist_node* list_head = NULL;
struct dlist_tcb rand_dlist = { NULL, 0};
/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

void int_str_test()
{
    struct dlist_node* p_int_list, *p_str_list;
    struct dlist_node* pre_node;
    int n,max,sum;
    n = max = sum = 0;
    int data[10] = {11,40,32,12,67,4,52,85,21,31};
    char str1[] = "hello world!";
    char str2[] = "good luck";
    char str3[] = "beautiful";
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

void* product_fn (void* data)
{
    ms_int32_t number;
    struct dlist_node* new_node = NULL;
    while(1)
    {
        number = rand();
        new_node = dlist_create_node((void*)number);
        printf("product data is : %d \n", (int)number);
        pthread_mutex_lock(&dlist_mutex);

        if (0 == rand_dlist.node_count)
        {
            rand_dlist.list_head = new_node;
        }
        else
        {
            dlist_insert_tail(rand_dlist.list_head, new_node);
        }
        rand_dlist.node_count ++;
        pthread_mutex_unlock(&dlist_mutex);

        Sleep(1);
    }

    return NULL;
}

void* consumer_fn (void* data)
{
    struct dlist_node* new_head_node;
    while(1)
    {

        pthread_mutex_lock(&dlist_mutex);
        if (0 != rand_dlist.node_count)
        {
            printf("consumer data is : %d \n",(int)rand_dlist.list_head->data);
            rand_dlist.node_count --;
            new_head_node = rand_dlist.list_head->next;
            dlist_delete_node(rand_dlist.list_head);
            rand_dlist.list_head = new_head_node;
        }
        else
        {
            printf("not data!\n");
        }
        pthread_mutex_unlock(&dlist_mutex);

        Sleep(3);
    }

    return NULL;
}

void list_pthread_test()
{
    ms_int32_t res;

    pthread_mutex_init(&dlist_mutex, NULL);

    res = pthread_create(&product_tid, NULL, product_fn, NULL);
    if (res != 0)
    {
        printf("can't create product thread!\n");
    }

    res = pthread_create(&consumer_tid, NULL, consumer_fn, NULL);
    if (res != 0)
    {
        printf("can't create consumer thread!\n");
    }
}
void list_app_main()
{
    int_str_test();
    list_pthread_test();

}
