
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <stdlib.h>

#define EASY_BOUND 15

//你要完成的功能总入口
int num[4];//4 numbers

int start, end;//start and end points

int must_pass[610];//must past points

#define INF 100 //infinite

int valid_num=0;//how many points are valid

int all_num=0;//number of points

int all_exist[610]={0};

//scan the demand
void scan_demand(char* line){
    int j=0;
    int k=0;
    char* temp;

    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    while(line[j]!=','){
        temp[k++]=line[j];
        j++;
    }
    start=atoi(temp);
    
    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    j++;
    while(line[j]!=','){
        temp[k++]=line[j];
        j++;
    }
    end=atoi(temp);
    
    int iter=0;

    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    j++;

    while(line[j]!='\0'){
        if(line[j]!='|'){
            temp[k++]=line[j];
            j++;
        }
        else{
            must_pass[iter++]=atoi(temp);
            temp=(char*)malloc(sizeof(char)*10);
            k=0;
            j++;
        }
    }
    must_pass[iter++]=atoi(temp);
    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    j++;
    must_pass[iter++]=-1;
}

//scan and store each point
void scan(char* line){
    int j=0;
    int k=0;
    char* temp;

    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    while(line[j]!=','){
        temp[k++]=line[j];
        j++;
    }
    num[0]=atoi(temp);
    
    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    j++;
    while(line[j]!=','){
        temp[k++]=line[j];
        j++;
    }
    num[1]=atoi(temp);
    if(all_exist[num[1]]==0){
        all_exist[num[1]]=1;
        all_num++;
    }

    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    j++;
    while(line[j]!=','){
        temp[k++]=line[j];
        j++;
    }
    num[2]=atoi(temp);
    if(all_exist[num[2]]==0){
        all_exist[num[2]]=1;
        all_num++;
    }

    temp=(char*)malloc(sizeof(char)*10);
    k=0;
    j++;
    while(line[j]!='\0'){
        temp[k++]=line[j];
        j++;
    }
    num[3]=atoi(temp);

    //printf("%d %d %d %d\n",num[0],num[1],num[2],num[3]);
}

//struct vertex
struct vertex{
    int weight;
    int edge_id;
};

//matrix
vertex vtov[610][610];

//whether a point is dead or not
int dead[610]={0};

//validating the point
int valid_vertex(int vertex_id){
    for(int i=0;i<610;i++){
        if(all_exist[i]&&vtov[vertex_id][i].weight!=INF)
            return 1;
    }
    return 0;
}

int validation(){
    for(int i=0;i<610;i++)
        if(dead[i]==0&&valid_vertex(i)==0){
            dead[i]=1;
            return i;
        }
    return -1;
}

void validating(){
    while(1){
        int temp=validation();
        if(temp==-1)
            return;
        for(int j=0;j<610;j++){
            if(all_exist[j])
                vtov[temp][j].weight=INF;
        }
    }
}


//initialization
void initialize(char *topo[5000], int edge_num, char *demand){
    for (int i=0;i<610;i++){
        for(int j=0;j<610;j++){
            vtov[i][j].weight=INF;
            //:vtov[i][j]=0;
        }
    }

    for(int i=0;i<edge_num;i++){
        scan(topo[i]);
        if(num[3]<vtov[num[1]][num[2]].weight){
            vtov[num[1]][num[2]].weight=num[3];
            vtov[num[1]][num[2]].edge_id=num[0];
        }
    }

    scan_demand(demand);

    /*
    int i=0;
    while(must_pass[i]!=-1)
        printf("%d ",must_pass[i++]);
    printf("\n\n");
    */

    validating();

    for(int i=0;i<610;i++)
        if(dead[i]==0)
            valid_num++;
    
    /*
    for(int i=0;i<610;i++){
        if(dead[i]==0&&all_exist[i]){
            printf("%d     ",dead[i]);
            for(int j=0;j<610;j++){
                if(all_exist[j]&&vtov[i][j].weight!=INF)
                    printf("%d/%d ",vtov[i][j].edge_id,vtov[i][j].weight);
            }
            printf("\n\n");
        }
    }
    */
}

typedef struct sp {
    int id;
    int sNode;
    int eNode;
    int weight;
} subpath;


int* p;
int* visited;
int* min_path;
int* breakpoint;
int cost;
int min_cost;

int all_visited() {
    int i = 0;
    int mp_num = 0;
    while (must_pass[i] != -1) {
        mp_num++;
        i++;
    }

    int current = end;
    while (p[current] != start) {
        i = 0;
        while (must_pass[i] != -1) {
            if (p[current] == must_pass[i]) {
                mp_num--;
                break;
            }
            i++;
        }
        current = p[current];
    }
    printf("mp_num = %d\n", mp_num);

    if (mp_num == 0) return 1;
    else return 0;
}

void dfs(int current, int parent) {

    printf("Now at node %d\n", current);

    p[current] = parent;

    int i;
    if (current == end && all_visited()) {
        if (cost < min_cost) {
            for (i = 0; i < all_num + 1; i++) min_path[i] = -1;

            min_cost = cost;
            // update path in a reverse order
            min_path[0] = p[end];
            for (i = 1; i < all_num + 1; i++) {
                int temp = p[min_path[i-1]];
                if (temp == start) {
                    break;
                } else {
                    min_path[i] = p[min_path[i-1]];
                }
            }
        }
    }

    //printf("Breakpoint of point %d = %d\n", current, breakpoint[current]);
    int next = breakpoint[current];
    while (next <= 610 && (vtov[current][next].weight == INF || visited[next])) next++;

    if (next > 609) {
        printf("Cannot expand anymore...\n");
        if (current == start) {
            printf("Search complete!\n");
            return;   // search complete
        }
        cost -= vtov[parent][current].weight;
        breakpoint[current] = 0;
        visited[current] = 0;
        dfs(parent, p[parent]);     // go back
    } else {
	    if (cost + vtov[current][next].weight >= min_cost) {      // cut-off
            //printf("Cost = %d\n", cost + vtov[current][next].weight);
            //printf("Min-cost = %d\n", min_cost);
            printf("Cut off\n");
            breakpoint[current] = next+1;
	        vtov[current][next].weight = INF;
            dfs(current, parent);
	    } else {                           // go deeper
            printf("Expand...\n");
            breakpoint[current] = next+1;
            cost += vtov[current][next].weight;
            visited[next] = 1;
            dfs(next, current);
        }
    }


}

void force_search() {
    cost = 0;
    min_cost = 10000000;

    int arr_size = sizeof(int) * (all_num + 1);
    printf("Array size = %d\n", all_num + 1);
    p = (int*)malloc(arr_size);
    min_path = (int*)malloc(arr_size);
    visited = (int*)malloc(arr_size);
    breakpoint = (int*)malloc(arr_size);
    
    int i;
    for (i = 0; i < all_num+1; i++) {
        visited[i] = 0;
        breakpoint[i] = 0;
    }

    // init at start point
    visited[start] = 1;
    dfs(start, -1);
    
}

void print_path() {
    if (min_path[0] == -1) {
        printf("No path found!\n");
        return;
    } else {
        printf("The path found: ");
    }
    
    int i;
    for (i = all_num; i >= 0; i--) {
        if (min_path[i] != -1) {
            printf("%d ", min_path[i]);
        }
    }
    printf("\n");
}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    //unsigned short result[];

    initialize(topo,edge_num,demand);
    
    subpath* sp = (subpath*)malloc(sizeof(subpath) * edge_num);
    
    int i;
    for (i = 0; i < edge_num; i++) {
        scan(topo[i]);
        sp[i].id = num[0];
        sp[i].sNode = num[1];
        sp[i].eNode = num[2];
        sp[i].weight = num[3];
    }

    
    if (all_num <= 15) {
        force_search();
    } else {

    }

    print_path();

/*
    unsigned short result[] = {2, 6, 3};//示例中的一个解

    for (int i = 0; i < 3; i++)
        record_result(result[i]);
*/
}
