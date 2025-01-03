//对于HRRN算法，需要为每一个进程设置一个变量，用来记录其动态优先级。
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//10个进程
#define PROCESS_NUM 10
int total=0;//总等待时间

// 进程控制块
typedef struct PCB {
    char pid[64];
    //state 状态  w 等待  r 运行 
    char state;
    float priority;
    int neededTime;
    int totalWaitTime;
    int arrival_time;
} PCB;


//函数声明
void hrrn(PCB process[], int num);
void print_hrrn(PCB process[], int num);

//hrrn调度函数
void hrrn(PCB process[], int num){

    // 按到达时间排序, 冒泡排序
    for(int i = 0; i < num - 1; i++){
        for(int j = 0; j < num - i - 1; j++){
            if(process[j].arrival_time > process[j+1].arrival_time){
                PCB temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }

    //排好序之后，开始调度
    int current_time = 0;
    int i, j, max;
    float max_priority;

    for(i = 0; i < num; i++){
        //计算动态优先级
        process[i].totalWaitTime = current_time - process[i].arrival_time;
        process[i].priority = (float)(process[i].totalWaitTime+process[i].neededTime) / process[i].neededTime;

        //寻找下一个，即相应比最高的进程
        max_priority = process[i].priority;
        max=i;
        for(j = i + 1; j < num; j++){
            //从到达的进程中挑选
             if(process[j].arrival_time <= current_time&&process[j].state=='w'){
                  //挑选高相应比的进程
                  process[j].totalWaitTime = current_time - process[j].arrival_time;
                  process[j].priority = (float)(process[j].totalWaitTime+process[j].neededTime) / process[j].neededTime;
                  if(process[j].priority > max_priority){
                      max_priority = process[j].priority;
                      max=j;
                  }
            }
        }
        //交换进程
        PCB tmp=process[i];
        process[i]=process[max];
        process[max]=tmp;

        //就是执行了进程i
        if(process[i].arrival_time > current_time){
            current_time = process[i].arrival_time;
        }

        //执行进程
        current_time += process[i].neededTime;
        process[i].totalWaitTime = current_time - process[i].arrival_time - process[i].neededTime;

        //总等待时间
        total+=process[i].totalWaitTime;

    }
}

// 打印结果(打印执行顺序，进程的等待时间以及平均等待时间)
void print_hrrn(PCB process[], int num){
    // 执行顺序
    printf("执行顺序: ");
    for(int i = 0; i < num; i++){
        printf("%s ", process[i].pid);
    }
    //进程等待时间
    printf("\n");
    printf("-------------------------\n");
    printf("进程 等待时间\n");
    for(int i = 0; i < num; i++){
        printf("%s \t%d\n", process[i].pid, process[i].totalWaitTime);
    }
    printf("-------------------------\n");
    printf("平均等待时间 %f\n", (float)total / num);
}




int main(){

    PCB process[PROCESS_NUM];
    int i=0;
    //随机种子
    srand(time(NULL));
    //初始化进程
    for(int i = 0; i < PROCESS_NUM; i++){
        // 进程id
        sprintf(process[i].pid, "P%d", i + 1);
        process[i].state = 'w';
        process[i].priority = 0;
        // 10-50之间的随机数
        process[i].neededTime = rand() % 41 + 10; 
        // 1-20之间的随机数
        process[i].arrival_time = rand() % 20 + 1;
        process[i].totalWaitTime = 0;
        printf("进程 %s生成， 到达时间 %d 运行时间 %d\n", process[i].pid, process[i].arrival_time, process[i].neededTime);
    }

    //hrrn调度
    hrrn(process, PROCESS_NUM);

    //打印结果
    print_hrrn(process, PROCESS_NUM);

    return 0;
}
