
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <stdlib.h>

#define EASY_BOUND 15

struct sp {
    int id;
    int sNode;
    int eNode;
    int weight;
} subpath;


void dfs(vertex** vtov, int current, int parent, int* min_cost, int** min_p) {
    p[current] = parent;

    if (current == end) {
        if (cost < min_cost) {
            *min_cost = cost;
            // update path
        }
    }

    int next = 0;
    while (vtov[current][next] == INF) next++;

    if (vtov[current][next] == INF) {
        if (current == start) return;   // search complete
        vtov[parent][current] = INF;    // disable current node
        cost -= vtov[parent][current];
        dfs(vtov, parent, p[parent], min_cost, min_p);     // go back
    } else {
        cost += vtov[current][next];
        dfs(vtov, next, current, min_cost, min_p);
    }

    // go into first visitable node, if none, disable current_node and dfs(parent_node)
    // update the current cost and record the parent node

    // if current node is end node, update min_cost and min_path
        // else dfs(current_node)
    
}

void search(vertex** vtov) {
    int** min_p;
    int min_cost = 10000000;

    // init at start point
    dfs(vtov, start_num, -1, &min_cost, min_p);
    
}


//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    //unsigned short result[];


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

    
    if (vertex_num <= 15) {
        dfs();
    } else {

    }



/*
    unsigned short result[] = {2, 6, 3};//示例中的一个解

    for (int i = 0; i < 3; i++)
        record_result(result[i]);
*/
}


/*
int hash(int num) {
    int i, result = 1;
    for (i = 0; i < num; i++) {
        result <<= 1;
    }
    return result;
}


void Held_Karp(vertex** vtov) {
    int i, k;
    int hash_size = 1 << vertex_num;
    int** cost = (int**)malloc(sizeof(int*)*vertex_num);
    for (i = 0; i < vertex_num; i++) {
        cost[i] = (int*)malloc(sizeof(int)*(hash_size)); //??
    }
    
    for (k = 0; k < vertex_num; k++) {
        if (k != start_num) {
            cost[k][start_num] = vtov[start_num][k];
        }
    }

    int s;
    for (k = 3; k < vertex_num; k++) {
        for (h = 0; h < hash_size; h++) {
            int temp, cnt = 0;
            for (temp = h; temp > 0; temp >> 1) {
                if (temp % 2 == 1) {
                    
                }
            }
        }
    }
}
*/
