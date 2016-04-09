
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <stdlib.h>

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


void search_route(char *topo[5000], int edge_num, char *demand)
{
    //unsigned short result[] = {2, 6, 3};//示例中的一个解
    initialize(topo,edge_num,demand);
    /*for (int i = 0; i < 3; i++)
        record_result(result[i])*/;
}
