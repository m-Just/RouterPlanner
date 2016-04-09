
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
#define EASY_BOUND 15
=======
//你要完成的功能总入口
int num[4];//4 numbers

int start,end;//start and end points

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

    printf("%d %d %d %d\n",num[0],num[1],num[2],num[3]);
}

//struct vertex
struct vertex{
    int weight;
    int edge_id;
};

//matrix
vertex vertex_to_vertex[610][610];

//whether a point is dead or not
int dead[610]={0};

//validating the point
int valid_vertex(int vertex_id){
    for(int i=0;i<610;i++){
        if(all_exist[i]&&vertex_to_vertex[vertex_id][i].weight!=INF)
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
                vertex_to_vertex[temp][j].weight=INF;
        }
    }
}


//initialization
void initialize(char *topo[5000], int edge_num, char *demand){
    for (int i=0;i<610;i++){
        for(int j=0;j<610;j++){
            vertex_to_vertex[i][j].weight=INF;
            //:vertex_to_vertex[i][j]=0;
        }
    }

    for(int i=0;i<edge_num;i++){
        scan(topo[i]);
        if(num[3]<vertex_to_vertex[num[1]][num[2]].weight){
            vertex_to_vertex[num[1]][num[2]].weight=num[3];
            vertex_to_vertex[num[1]][num[2]].edge_id=num[0];
        }
    }

    scan_demand(demand);

    int i=0;
    while(must_pass[i]!=-1)
        printf("%d ",must_pass[i++]);
    printf("\n\n");

    validating();

    for(int i=0;i<610;i++)
        if(dead[i]==0)
            valid_num++;
    
    for(int i=0;i<610;i++){
        if(dead[i]==0&&all_exist[i]){
            printf("%d     ",dead[i]);
            for(int j=0;j<610;j++){
                if(all_exist[j]&&vertex_to_vertex[i][j].weight!=INF)
                    printf("%d/%d ",vertex_to_vertex[i][j].edge_id,vertex_to_vertex[i][j].weight);
            }
            printf("\n\n");
        }

    }
}
>>>>>>> fd222c531d23badb64a9e0c36fa7511f7463d843

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
<<<<<<< HEAD
    //unsigned short result[];


=======
    initialize(topo,edge_num,demand);
    
>>>>>>> fd222c531d23badb64a9e0c36fa7511f7463d843
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
