#include<stdio.h>
#include<stdlib.h>
#define MAX_NUM (10)//站点最大个数
#define clockwise (0)
#define counter_clockwise (1)
#define get_off (2)
#define FCFS (0)//先来先服务策略,first come first serve
#define SSTF (1)//最短寻找时间优先策略,shortest seek time first
#define SCAN (2)//顺便服务策略,by the way service
#define dis_max 99

struct _CAR
{
    int id;
    int flag;
    int pos;
    int direction;
    int target = -1;//用于最短寻找时间策略中，标记当前车的目标站点
};
typedef struct _CAR car;

struct _REQUEST
{
    int id;
    int direction;
    int distance;
    int status;//表示请求种类
    struct _REQUEST* next;
}
typedef _REQUEST request;


int sta_dis=2;//站点距离
int sta_num=5;//站点数
int length=10;//总长度
int strategy=FCFS;

station* head = NULL;//链表头
int status[MAX_NUM][3]//输出时更新，表示站点的请求状态
//0表示顺时针，1表示逆时针，2代表下车请求

/*
大致思路：
1.先来先服务，将上下车请求都用链表存储，
到达站点后检查后续节点是否为同一站点，若相同则一并完成，
每次输出时，遍历链表来检查请求状态

2.最短寻找时间，根据时间对链表重排序(时间相同时顺时针请求优先,target取最短时间)，
取表头请求，更新小车状态，
当小车destination不为-1，出现新的请求，压入链表，
路过站点时检查链表内是否有同方向的该站点请求，若有，则停，
到达目标时，遍历该链表找到所有该站点请求
每次输出时，遍历链表来检查请求状态

3.顺便服务策略，同样将请求用链表存储，
行驶方向确定后，每次检查最短完成时间，根据最短完成时间更新方向，
到达站点后，将所有该站点请求完成(无视方向、上下车)
(PS:这个策略直接用bool数组存储该站点是否有请求就行
但考虑到后续版本可能涉及到策略的变化，故仍用链表存储)
*/
