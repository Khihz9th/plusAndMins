#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 20
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define T 1                    //true                         
#define F 0                    //false

int MazeInit(int height, int width, int initValue);                                           //迷宫初始化,二维数组指针还需要去学习。
int MazeDebugDisp(int maze[HEIGHT][WIDTH], int height, int width, int bool);                  //在终端上显示二维数组的状态
int RandOutDir(int boolOfHead);                                                               //随机生成一个方向
int DontHitWall(int direction, int x, int y);                                                 //防止撞墙的判定
int StepCont1(int x, int y, int lastDir, int NowDir, int type, int *dirFix);                  //第一种模式运行
int JudgeOfSpinbool(int bool_init, int change_value);                                         //返回值：T 能够移动  F 不能移动

int tempdir() //临时使用
{
    return rand() % 4;
}
/*
### 工作备忘：
* ~后续需要将函数内的数组改为改为指针传参，两个函数其实变量过于复炸(需要传入的形参和实参过多）后续待优化。~
* 完成代码的修改
*/
int maze[HEIGHT][WIDTH];                        //迷宫主体
int headTrack = UP;                             //0 up, 1, down, 2, left, 3, right. 
int tailTrack = DOWN;
int tempTrack = 0;                              //临时方向变量
int hx = 1, hy = 1;                             //坐标
int tx = WIDTH - 2, ty = HEIGHT - 2;
int dirIn;                                      // direction indicator
int judgeOfSpin[4] = {F, F, F, F};

int main()
{
    /*
    有两种信息模式，一种是一个数值储存一个信息，但是导致矩阵的面积增大；
    另一种是一个数值储存多个信息，可以减小矩阵的面积，但是单个数值需要对其进行解译。
    last edited:2021年10月23日
    */
    MazeInit(HEIGHT, WIDTH, F);
    MazeDebugDisp(maze, HEIGHT, WIDTH, T);
    /*
    下面的代码是生成主路径，采用一个数值储存一个信息的方式。
    默认：// 实现代码时我好像替换了方向（2021年10月25日）
        入口：
           坐标 (0, 0) 特征识别值 1 向上和先左移动的概率分别为20%, 向下和向右移动的概率分别为30%
        出口：
           坐标 (HEIGHT, WIDTH) 特征识别值 2 向上和先左移动的概率分别为30%, 向下和向右移动的概率分别为20%
    
    P.S.:后续需要将下面的代码转换为函数；
    last edited:2021年10月23日
    */
   
    int bigLoop = F, littleLoop;                    //跳出循环
    int judgeOfMaze;                                //判断矩阵能否运行
    
    int n = 0;  //
    int *dirFix = &tempTrack;
    while (bigLoop == F)
    {
        printf("第%d次循环。\n", ++n);//
        littleLoop = F;
        JudgeOfSpinbool(T, headTrack);
        while (littleLoop == F)
        {
            // tempTrack = randOutDir(1);
            tempTrack = tempdir();
            printf("\nHeadTrack = %d \n", headTrack);
            printf("Head tempTrack = %d\n", tempTrack);//
            judgeOfMaze = StepCont1(hx, hy, headTrack, tempTrack, 1, dirFix);
            printf("Head judgeOfMaze = %d\n", judgeOfMaze);//
            if(judgeOfMaze != 0)
            {
                if(judgeOfMaze == 1 || judgeOfMaze == 3)
                {
                    switch (tempTrack) //防碰撞导致方向相反
                    {
                        case UP: hy ++; break;
                        case DOWN: hy --; break;
                        case RIGHT: hx --; break;
                        case LEFT: hx ++; break;
                    }
                    headTrack = tempTrack;
                    if (judgeOfMaze == 3) bigLoop = T;
                    //littleLoop = T;
                    break;
                }
                if(judgeOfMaze == 2)
                if(JudgeOfSpinbool(F, 0) == T)
                {
                    // littleLoop = T;
                    bigLoop = T;
                    break;
                }
            }
            printf("\n");//
        }
        MazeDebugDisp(maze, HEIGHT, WIDTH, T);
        if(bigLoop == T) break;
        JudgeOfSpinbool(T, tailTrack);
        while (littleLoop == F)
        {
            tempTrack = tempdir();
            printf("\nTailTrack = %d\n", tailTrack);
            printf("Tail tempTrack = %d\n", tempTrack);//
            judgeOfMaze = StepCont1(tx, ty, tailTrack, tempTrack, 2, dirFix);
            printf("Tail judgeOfMaze = %d\n", judgeOfMaze);//
            if(judgeOfMaze != 0)
            {
                if(judgeOfMaze == 1 || judgeOfMaze == 3)
                {
                    switch (tempTrack)
                    {
                        case DOWN: ty --; break;
                        case UP: ty ++; break;
                        case RIGHT: tx --; break;
                        case LEFT: tx ++; break;
                    }
                    tailTrack = tempTrack;
                    if (judgeOfMaze == 3) bigLoop = 1;
                    //littleLoop = 1;
                    break;
                }
                if(judgeOfMaze == 2)
                {
                    if(JudgeOfSpinbool(F, 0) == T)
                    {
                        bigLoop = T;
                        break;
                    }
                }
            }
            printf("\n");//
        }
        printf("\n\n\n");//
        MazeDebugDisp(maze, HEIGHT, WIDTH, F);     
    }
}
int MazeInit(int height, int width, int initValue)                              //迷宫初始化,二维数组指针还需要去学习。
{
    /*return bool of initization updated:2021年10月23日 */
    int boolOfMaze = 1;
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            maze[j][i] = initValue;             //二维数组指针；(2021年10月23日14点12分：对*((*maze)[j] + i) = initValue;为赋值形式存在疑惑)
        }
    }
    maze[0][0] = maze[1][1] = maze[0][1] = 1;
    maze[HEIGHT - 1][WIDTH - 1] = maze[HEIGHT - 1][WIDTH - 2] = maze[HEIGHT - 2][WIDTH - 2] = 2;
    int test_a, test_b;
    test_a = HEIGHT - 1;
    test_b = WIDTH - 1;
    maze[test_a][test_b] = maze[test_a -1][test_b - 1] = 2;
    return boolOfMaze;                                                  // 目前找不到报错的环境
}
int MazeDebugDisp(int maze[HEIGHT][WIDTH], int height, int width, int bool)//在终端上显示二维数组的状态
{
 for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            if(bool == F)
            {
                printf("%d ", maze[j][i]);
            }else{
                if(maze[j][i] == F)
                {
                    printf("◻");
                }else{
                    printf("◼");
                }
            }
        }
        printf("\n");
    }
    return 1;//暂时找不到报错环境，后面可以考虑取消或改变函数类型。
}
int RandOutDir(int boolOfHead) //随机生成一个方向
{
    int ra;
    int returnValue;
    ra = rand() % 10;
    //printf("生成的随机数是：%d \n", ra);//
    if(ra >= 0 && ra <= 2)      returnValue = 0;
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
int StepCont1(int x, int y, int lastDir, int NowDir, int type, int *dirFix)//第一种函数运行
{
    //0 up, 1, down, 2, left, 3, right. 
    int returnValue = 0; //1 运行成功， 0 运行失败, 2 自旋漩涡, 3 运行终止
    //方向检测
    if(NowDir == lastDir) goto errHappen;
    //边界检测
    if(x == 1 && NowDir == LEFT) goto errHappen;
    if(x == WIDTH - 2 && NowDir == RIGHT) goto errHappen;
    if(y == 1 && NowDir == UP) goto errHappen;
    if(y == HEIGHT - 2 && NowDir == DOWN) goto errHappen;
    //行进赋值
    int inputValue = 1;
    if(type == 2) inputValue = 2; //type 1, 正方向, type 2, 反方向
    switch (NowDir) //这个也需要标记检测
    {
        case UP:
            if(y >= 2)
            if (maze[y - 2][x] == inputValue) 
            {
                upSpin:
                judgeOfSpin[1] = T;
                returnValue = 2; 
                goto errHappen; 
            }
            if(maze[y - 1][x - 1] != 0 || maze[y - 1][x + 1] != 0) goto upSpin;
           break;
        case DOWN: 
            if(y < HEIGHT - 3)
            if (maze[y + 2][x] == inputValue)
            {
                downSpin:
                 judgeOfSpin[0] = T;
                 returnValue = 2; 
                 goto errHappen; 
            }
            if(maze[y + 1][x - 1] != 0 || maze[y + 1][x + 1] != 0) goto downSpin;
            break;
        case LEFT: 
            if(x >= 2)
            if (maze[y][x - 2] == inputValue)
            { 
                leftSpin:
                judgeOfSpin[3] = T;
                returnValue = 2; 
                goto errHappen;
            }
            if(maze[y + 1][x - 1] != 0 || maze[y - 1][x - 1] != 0) goto leftSpin;
            break;
        case RIGHT: 
            if(x <= WIDTH - 3)
            if (maze[y][x + 2] == inputValue)
            {
                rightSpin:
                judgeOfSpin[2] = T;
                returnValue = 2;
                goto errHappen;
            }
            if(maze[y + 1][x + 1] != F || maze[y - 1][x + 1] != F) goto rightSpin;
            break; 
        default :
            printf("\nsome bugs exists...\n");
            break;     
    }
    //赋值
    switch (NowDir)
    {
    case UP: 
        if(maze[y - 1][x] != 0) returnValue = 3;
        *dirFix = DOWN;
        maze[y - 1][x] = inputValue;
        break;
    case DOWN: 
        if(maze[y + 1][x] != 0) returnValue = 3;
        *dirFix = UP;
        maze[y + 1][x]  = inputValue;
        break;
    case LEFT: 
        if(maze[y][x - 1] != 0) returnValue = 3;
        *dirFix = RIGHT;
        maze[y][x - 1] = inputValue;
        break;
    case RIGHT: 
        if(maze[y][x + 1] != 0) returnValue = 3;
        *dirFix = LEFT;
        maze[y][x + 1] = inputValue;
        break;
    default :
        printf("\nsome bugs exists...\n");
        break;    
    }
    //正常运行校验修正
    if(returnValue != 3) returnValue = 1;
    //结果反馈
    errHappen:
    return returnValue;
}
int JudgeOfSpinbool(int bool_init, int change_value) //返回值：T 不能移动  F 能移动
{
    int returnValue = T;
    if(bool_init == T)
    {
        for(int i = 0; i < 4; i++) judgeOfSpin[i] = F;
        switch(change_value)
        {
            case 0: judgeOfSpin[1] = T; break;
            case 1: judgeOfSpin[0] = T; break;
            case 2: judgeOfSpin[3] = T; break;
            case 3: judgeOfSpin[2] = T; break;
        }
        
    }
    for(int i = 0; i < 4; i++)
    {
        if(judgeOfSpin[i] == F) returnValue = F;
    }
    return returnValue;
}