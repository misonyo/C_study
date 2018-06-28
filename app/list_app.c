#include "list.h"


void list_app_main()
{
    struct dlist_node* int_list;
    struct dlist_node* pre_node,new_node;
    int n;
    int data[10] = {11,40,32,12,67,4,52,85,21,31};

    int_list = dlist_init();
    pre_node = int_list;

    for(n =0;n < 10;n++)
    {
        new_node = malloc(sizeof(struct dlist_node));

        dlist_insert_after(pre_node,new_node);

        new_node->data = (void*)data[n];

        pre_node = new_node;
    }




}
