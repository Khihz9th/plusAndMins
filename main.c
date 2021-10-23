#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 10
#define WIDTH 10

int mazeInit(int maze[HEIGHT][WIDTH], int height, int width, int initValue);//迷宫初始化,二维数组指针还需要去学习。
int mazeDebugDisp(int maze[HEIGHT][WIDTH], int height, int width);//在终端上显示二维数组的状态
int randOutDir(int boolOfHead); //随机生成一个方向
int dontHitWall(int direction, int x, int y); //防止撞墙的判定
/*
### 工作备忘：
* 后续需要将函数内的数组改为改为指针传参，两个函数其实变量过于复炸(需要传入的形参和实参过多）后续待优化。
* 
*/

int main()
{
    int maze[HEIGHT][WIDTH];//迷宫主体
    /*
    有两种信息模式，一种是一个数值储存一个信息，但是导致矩阵的面积增大；
    另一种是一个数值储存多个信息，可以减小矩阵的面积，但是单个数值需要对其进行解译。
    last edited:2021年10月23日
    */
    mazeInit(maze, HEIGHT, WIDTH, 0);
    // mazeDebugDisp(maze, HEIGHT, WIDTH);
    /*
    下面的代码是生成主路径，采用一个数值储存一个信息的方式。
    默认：
        入口：
           坐标 (0, 0) 特征识别值 1 向上和先左移动的概率分别为20%, 向下和向右移动的概率分别为30%
        出口：
           坐标 (HEIGHT, WIDTH) 特征识别值 2 向上和先左移动的概率分别为30%, 向下和向右移动的概率分别为20%
    
    P.S.:后续需要将下面的代码转换为函数；
    last edited:2021年10月23日
    */
    int headTrack = 0, temHT = 0; //0 up, 1, down, 2, left, 3, right. 
    int tailTrack = 0, temTT = 0;
    int hx = 1, hy = 1; //坐标记忆
    int tx = WIDTH - 2, ty = HEIGHT - 2;
    int dirIn; // direction indicator
    int bigLoop = 1, littleBreak = 0;

    int n = 0;//
    while(1)
    {
        while(1)
        {
            temHT = randOutDir(1);
            if(temHT == headTrack) continue;
            if(dontHitWall(temHT, hx, hy) == 0) continue;
            switch(temHT)
            {
                case 0:
                hy --;
                if(maze[hy][hx] == 0) 
                {
                    maze[hy][hx] = 1;
                    headTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[hy][hx] == 2)
                {
                    bigLoop = 0;
                    littleBreak = 1;
                }
                break;
                case 1:
                hy ++;
                 if(maze[hy][hx] == 0) 
                {
                    maze[hy][hx] = 1;
                    headTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[hy][hx] == 2)
                {
                    bigLoop = 0;
                    littleBreak = 1;
                }
                break;
                case 2:
                hx --;
                 if(maze[hy][hx] == 0) 
                {
                    maze[hy][hx] = 1;
                    headTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[hy][hx] == 2)
                {
                    bigLoop = 0;
                    littleBreak = 1;
                }
                break;
                case 3:
                hx ++;
                 if(maze[hy][hx] == 0) 
                {
                    maze[hy][hx] = 1;
                    headTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[hy][hx] == 2)
                {
                    bigLoop = 0;
                    littleBreak = 1;                
                }
                break;
            }
            if(littleBreak == 1) break;
        }
        littleBreak = 0;
        if(bigLoop == 0) break;

        while(1)
        {
            temHT = randOutDir(0);
            if(temHT == tailTrack) continue;
            if(dontHitWall(temHT, tx, ty) == 0) continue;
            switch(temHT)
            {
                case 0:
                ty --;
                if(maze[ty][tx] == 0) 
                {
                    maze[ty][tx] = 2;
                    tailTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[ty][tx] == 1)
                {
                    bigLoop = 0;
                    littleBreak = 1;
                }
                break;
                case 1:
                ty ++;
                 if(maze[ty][tx] == 0) 
                {
                    maze[ty][tx] = 2;
                    tailTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[ty][tx] == 1)
                {
                    bigLoop = 0;
                    littleBreak = 1;
                }
                break;
                case 2:
                tx --;
                 if(maze[ty][tx] == 0) 
                {
                    maze[ty][tx] = 2;
                    tailTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[ty][tx] == 1)
                {
                    bigLoop = 0;
                    littleBreak = 1;
                }
                break;
                case 3:
                tx ++;
                 if(maze[ty][tx] == 0) 
                {
                    maze[ty][tx] = 2;
                    tailTrack = temHT;
                    littleBreak = 1;
                }
                else if(maze[ty][tx] == 1)
                {
                    bigLoop = 0;
                    littleBreak = 1;                
                }
                break;
            }
            if(littleBreak == 1) break;
        }
        littleBreak = 0;
        if(bigLoop == 0) break;
        printf("循环了%d次,\n \n",++n);
    }
    mazeDebugDisp(maze, HEIGHT, WIDTH);

}

int mazeInit(int maze[HEIGHT][WIDTH], int height, int width, int initValue)//迷宫初始化,二维数组指针还需要去学习。
{
    /*return bool of initization updated:2021年10月23日 */
    int boolOfMaze = 1;
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            *((*maze +j) + i) = initValue;//二维数组指针；(2021年10月23日14点12分：对*((*maze)[j] + i) = initValue;为赋值形式存在疑惑)
        }
    }
    return boolOfMaze;//目前找不到报错的环境
}

int mazeDebugDisp(int maze[HEIGHT][WIDTH], int height, int width)//在终端上显示二维数组的状态
{
 for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            printf("%d ", *((*maze + j) + i));
        }
        printf("\n");
    }
    return 1;//暂时找不到报错环境，后面可以考虑取消或改变函数类型。
}

int randOutDir(int boolOfHead) //随机生成一个方向
{
    int ra;
    int returnValue;
    ra = rand() % 10;
    printf("生成的随机数是：%d \n", ra);
    if(ra >= 0 && ra <= 2) returnValue = 0;
    else if(ra >= 3 && ra <= 5) returnValue = 1;
    else if(ra >= 6 && ra <= 7) returnValue = 2;
    else returnValue = 3;
    if(boolOfHead != 1)
    {
        returnValue - 1;
        if(returnValue < 0) returnValue += 4;
        //!!!!!!!!
    }
    return returnValue; 
}

int dontHitWall(int direction, int x, int y)
{
    int returnValue = 1;
    switch(direction)
    {
        case 0:
        if(y == 1) returnValue = 0; 
        break;
        case 1:
        if(y == HEIGHT - 2) returnValue = 0;
        break;
        case 2:
        if(x == 1) returnValue = 0;
        break;
        case 3:
        if(x == WIDTH - 2) returnValue = 0;
        break;
    }
    return returnValue;
}