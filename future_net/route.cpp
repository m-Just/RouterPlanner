
#include "route.h"
#include "lib_record.h"
#include <stdio.h>

struct sp {
    int id;
    int sNode;
    int eNode;
    int weight;
} subpath;


//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    subpath* sp = (subpath*)malloc(sizeof(subpath) * edge_num);
    
    int i;
    char *ptr;
    for (i = 0; i < edge_num; i++) {
        scan(topo[i]);
        sp[i].id = num[0];
        sp[i].sNode = num[1];
        sp[i].eNode = num[2];
        sp[i].weight = num[3];
    }

    


/*
    unsigned short result[] = {2, 6, 3};//示例中的一个解

    for (int i = 0; i < 3; i++)
        record_result(result[i]);
*/
}
