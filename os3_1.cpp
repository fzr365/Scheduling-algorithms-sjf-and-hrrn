#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//10������
#define PROCESS_NUM 10
int total=0;//�ܵȴ�ʱ��

// ���̿��ƿ�
typedef struct PCB {
    char pid[64];
    //state ״̬  w �ȴ�  r ���� 
    char state;
    int neededTime;
    int totalWaitTime;
    int arrival_time;
} PCB;


//��������
void sjf(PCB process[], int num);
void print_sjf(PCB process[], int num);

//sjf���Ⱥ���
void sjf(PCB process[], int num){

    // ������ʱ������, ð������
    for(int i = 0; i < num - 1; i++){
        for(int j = 0; j < num - i - 1; j++){
            if(process[j].arrival_time > process[j+1].arrival_time){
                PCB temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }

    //�ź���֮�󣬿�ʼ����
    int current_time = 0;
    int i, j, min;
    for(i = 0; i < num; i++){
        //Ѱ����һ���������������ʱ����̵Ľ���
        min = i;
        for(j = i + 1; j < num; j++){
            if(process[j].arrival_time <= current_time && process[j].neededTime < process[min].neededTime){
                min = j;
            }
        }
        //��������
        PCB tmp=process[i];
        process[i]=process[min];
        process[min]=tmp;

        //����ִ���˽���i
        if(process[i].arrival_time > current_time){
            current_time = process[i].arrival_time;
        }

        //ִ�н���
        current_time += process[i].neededTime;
        process[i].totalWaitTime = current_time - process[i].arrival_time - process[i].neededTime;

        //�ܵȴ�ʱ��
        total+=process[i].totalWaitTime;

    }
}

// ��ӡ���(��ӡִ��˳�򣬽��̵ĵȴ�ʱ���Լ�ƽ���ȴ�ʱ��)
void print_sjf(PCB process[], int num){
    // ִ��˳��
    printf("ִ��˳��: ");
    for(int i = 0; i < num; i++){
        printf("%s ", process[i].pid);
    }
    //���̵ȴ�ʱ��
    printf("\n");
    printf("-------------------------\n");
    printf("���� �ȴ�ʱ��\n");
    for(int i = 0; i < num; i++){
        printf("%s \t%d\n", process[i].pid, process[i].totalWaitTime);
    }
    printf("-------------------------\n");
    printf("ƽ���ȴ�ʱ�� %f\n", (float)total / num);
}




int main(){

    PCB process[PROCESS_NUM];
    int i=0;
    //�������
    srand(time(NULL));
    //��ʼ������
    for(int i = 0; i < PROCESS_NUM; i++){
        // ����id
        sprintf(process[i].pid, "P%d", i + 1);
        process[i].state = 'w';
        // 10-50֮��������
        process[i].neededTime = rand() % 41 + 10; 
        // 1-20֮��������
        process[i].arrival_time = rand() % 20 + 1;
        process[i].totalWaitTime = 0;
        printf("���� %s���ɣ� ����ʱ�� %d ����ʱ�� %d\n", process[i].pid, process[i].arrival_time, process[i].neededTime);
    }

    //SJF����
    sjf(process, PROCESS_NUM);

    //��ӡ���
    print_sjf(process, PROCESS_NUM);

    return 0;
}
