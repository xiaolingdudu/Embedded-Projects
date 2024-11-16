//初始化贪吃蛇游戏的棋盘代码
#include "gluttonous_snake_initial.h"

/*贪吃蛇运行数组，其中，元素的值
为2向右移动，为3向左移动
为4向上运动，为5向下运动
为1组成蛇的身体，为0表示空白
为6表示为要吃的球*/
char data_str[440/20][560/20]={0};

//初始化贪吃蛇的游戏界面
void lcd_draw_gluttonous_snake()
{
    //显示墙壁
    for(int i=0;i<30;i++)
    {    
        lcd_draw_bmp(i*20,0,"wall.bmp");
        lcd_draw_bmp(i*20,460,"wall.bmp");
    }
    for(int i=1;i<23;i++)
    {
        lcd_draw_bmp(0,20*i,"wall.bmp");
        lcd_draw_bmp(580,20*i,"wall.bmp");
    }
}

//随机产生贪吃蛇要吃的球
void rand_str_data()      //产生数组中的随机数
{
    srand((unsigned)time(NULL));
    int i,j;
    while(1)
    {
        i=rand()%22;    //取0-21的随机数
        j=rand()%28;    //取0-27的随机数
        if(data_str[i][j]==0)   
        {   //在值为0的位置产生球--值为6
            data_str[i][j]=6;
            lcd_draw_bmp(20+20*j,20+20*i,"6.bmp");
            break;
        }
    }
}


//生成贪吃蛇的头
Head_snake* creat_HeadSnake()
{
    //创建头结点
    Head_snake* head=(Head_snake*)malloc(sizeof(Head_snake));
    Node* new=(Node*)malloc(sizeof(Node));
    //取数组中间元素为贪吃蛇起点，并且使其向右(值为2)运行
    data_str[10][10]=2;
    new->i=10;
    new->j=10;
    new->next=NULL;
    head->first=head->last=new;
    head->direction=2;  //向右
    head->num=1;
    return head;
}

//清空链表空间
void clearn_all_snake(Head_snake* head)
{
    if (head == NULL || head->first == NULL) {
        return; // 如果链表为空，直接返回
    }

    Node* p = head->first;
    while (p) {
        Node* temp = p;  // 记录当前节点
        p = p->next;     // 移动到下一个节点
        free(temp);      // 释放当前节点
    }

    free(head);  // 释放链表头
}


typedef struct Ranking{
    char rank[8];
    int data;
}Ranking;

//跟新贪吃蛇的历史排名
void Update_ranking(Head_snake* head)
{
    // 打开文件用于读写
    FILE* fd1 = fopen("ranking.txt", "r+");
    if (fd1 == NULL) {
        perror("fopen error");
        return;
    }

    // 初始化排名数组，逐个结构体初始化
    Ranking buf[10] = {
        {"first", 0}, {"second", 0}, {"third", 0}, {"fourth", 0}, {"fifth", 0},
        {"sixth", 0}, {"seventh", 0}, {"eighth", 0}, {"ninth", 0}, {"tenth", 0}
    };

    // 从文件中读取排名数据，确保读取成功
    for (int i = 0; i < 10; i++) {
        if (fscanf(fd1, "%s %d", buf[i].rank, &buf[i].data) != 2) {
            // 文件内容不足，直接退出循环
            break;
        }
    }

    // 关闭文件，重新以写模式打开
    fclose(fd1);
    fd1 = fopen("ranking.txt", "w+");
    if (fd1 == NULL) {
        perror("fopen error");
        return;
    }

    // 贪吃蛇当前的长度
    int temp = head->num;

    // 更新排名，如果当前分数大于历史排名中的分数，进行交换
    for (int i = 0; i < 10; i++) {
        if (temp > buf[i].data) {
            int temp1 = buf[i].data;
            buf[i].data = temp;
            temp = temp1;
        }
    }

    // 刷新排名并显示在屏幕上
    int flag = 1;
    for (int i = 0; i < 10; i++) {
        // 显示排名
        Lcd_string_size(600, 20 * i, 0xff000000, buf[i].rank, 12);

        // 如果是刷新后的分数，用不同颜色显示
        if (buf[i].data == head->num && flag == 1) {
            Lcd_string_size(600, 20 * i, 0xffff0000, buf[i].rank, 12);
            flag = 0;
        }

        // 显示分数
        Lcd_Number(700, 20 * i, 0xff00ff00, buf[i].data, 5);
    }

    // 将更新后的数据重新写入文件
    fseek(fd1, 0, SEEK_SET);
    for (int i = 0; i < 10; i++) {
        fprintf(fd1, "%s %d\n", buf[i].rank, buf[i].data);
    }

    // 关闭文件
    fclose(fd1);
}
