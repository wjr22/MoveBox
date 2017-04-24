/********************************
推箱子大军
time 2017.3.25
writer wang
虽然是抄的
*********************************/
#include<glut.h>
#include<stdio.h>
#include<stdlib.h>//
#include<conio.h>//键值
#include<windows.h>//清屏，刷新
#define KEY_UP 72//上键
#define KEY_DOWN 80//下键
#define KEY_LEFT 75//左键
#define KEY_RIGHT 77//右键
#define KEY_RETURN 2//返回主界面
#define KEY_NEXT 4//下一关
#define SPACE_OUT 0
#define WALL 1//墙
#define SPACE 2//空地
#define TARGET 3//移动
#define BOX 4//箱子
#define TARGET_IN 5//移动到位置
#define PERSON 6//人物
#define BACKSPACE 27//撤销
int step[100][14][16];
int istep;
/*                            函数声明部分↓↓↓↓↓↓↓                */
         void DesignUI();//主界面函数
         int WelcomePage();//欢迎界面，选择
        /*                              绘制地图 start                          */
          int PrintMap(int aiMap[][16], int iImp);/*iImp代表游戏关卡*/
          void SelectColor(int iColor);/*颜色函数*/
       /*                              绘制地图 end                            */
		  void MoveBox(int aiMap[][16], int iPlayerX, int iPlayerY, int iSelect, int aiMap2[][16]);
		  int PlayGame(int aiMap[][16], int aiMap2[][16], int iSum, int iImp);
         void GetLevel1();
         void GetLevel2();
         void GetLevel3();
         void GetLevel4();
		 void GetLevel5();
		 void GetLevel6();
/*                            函数声明部分↑↑↑↑↑↑↑                 */
int main(){
	while (1){
		DesignUI();/*显示主界面*/
	}
}
void DesignUI(){
	int iCh;
	char cNum;
	iCh = WelcomePage();//显示欢迎界面
	if (iCh == 49)
		GetLevel1();
	if (iCh == 50){
		printf("\n\t\t 请输入关卡（1到6）:");
		getchar();
		cNum = getchar();
		switch (cNum){
		case '1':
			GetLevel1();
			break;
		case '2':
			GetLevel2();
			break;
		case '3':
			GetLevel3();
			break;
		case '4':
			GetLevel4();
			break;
		case '5':
			GetLevel5();
			break;
		case '6':
			GetLevel6();
			break;
		default :
			printf("\aEnter error!\n");
			Sleep(1000);
			exit(0);
			break;
		}
	}
	else if (iCh == 51){
		system("cls");
		exit(0);
	}
}
int WelcomePage(){
	int i = 0;
	system("cls");/*清屏*/
	system("color 0E");/*设置颜色*/
	printf("\n\n\t\tWelcome to play ...!拽两句english\n\n");
	printf("\t\t 你:♀ 墙:▓ 箱子:● 目的地:◎ 已完成:◇\n");
	printf("\t\t 上:↑ 下:↓ 左:← 右:→\n\n");
	printf("\t\t 按1开始游戏\n\t\t\n");
	printf("\t\t 按2选择关卡\n\t\t\n");
	printf("\t\t 按3结束游戏\n\t\t\n");
	printf("\t\t 注意！你只有一次机会！没有撤退！！！\t\t\n");
	printf("\t\t 专属老王的小游戏\t\t\t\n");
	while (1){
		i = getchar();
		if (i >= 49 && i <= 51)
			return i;
	}
}
/*                       绘制地图模块 start                               */
int PrintMap(int aiMap[][16], int iImp){
	int i, j;
	int iCount = 0;
	for (i = 0; i < 14; i++){
		for (j = 0; j < 16; j++){
			switch (aiMap[i][j])
			{
			case 0:
				printf("  ");//墙外空地
				break;
			case 1:
				SelectColor(14);
				printf("▓");//墙
				break;
			case 2:
				printf("  ");//墙内空地
				break;
			case 3:
				SelectColor(11);//目的地
				printf("○");
				break;
			case 4:
				SelectColor(11);
				printf("●");//箱子
				break;
			case 5:
				iCount++;
				SelectColor(9);
				printf("☆");//已完成
				break;
			case 6:
				SelectColor(10);
				printf("♀");//人
				break;
			}
		}
		printf("\n");
	}
	SelectColor(14);
	printf("\n");
	printf("\t 第%d关\t\t\n", iImp);
	printf("\t 按方向键玩\t\n");
	printf("\t 按N下一关\t\n");
	printf("\t 按Q回开始界面\t\n");
	printf("\t 按Esc重新开始\t\n");
	return iCount;//返回值表示已正确放入箱子数
}
void SelectColor(int iColor){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//得到控制台输出设备句柄
	SetConsoleTextAttribute(hConsole, iColor);//设置控制台属性
}
/*                       绘制地图模块 end                                 */


int PlayGame(int aiMap[][16], int aiMap2[][16], int iSum, int iImp){
	int i, j;
	int iPlayerX, iPlayerY;//人的位置
	char cop='\0';//方向键
	int iNum = 0;
	while (1){
		for (i = 0; i < 14; i++){
			for (j = 0; j < 16; j++){
				if (aiMap[i][j] == PERSON)
					break;//人的位置
			}
			if (j < 16)
				break;
		}
		iPlayerX = i;
		iPlayerY = j;
		system("cls");
		iNum = PrintMap(aiMap, iImp);
		if (iNum == iSum){
			printf("\t\t\a完成!\n");
			Sleep(3000);
			return 0;
		}
		else{
			cop = _getch();
			if ((cop == 'n') || (cop == 'N'))
				return KEY_NEXT;
			else if ((cop == 'q') || (cop == 'Q'))
				return KEY_RETURN;
			switch (cop){
			case KEY_UP:
				MoveBox(aiMap, iPlayerX, iPlayerY, 1, aiMap2); break;
			case KEY_DOWN:
				MoveBox(aiMap, iPlayerX, iPlayerY, 4, aiMap2); break;
			case KEY_LEFT:
				MoveBox(aiMap, iPlayerX, iPlayerY, 2, aiMap2); break;
			case KEY_RIGHT:
				MoveBox(aiMap, iPlayerX, iPlayerY, 3, aiMap2); break;
			case BACKSPACE:
				for (i = 0; i < 14; i++){
					for (j = 0; j < 16; j++){
						aiMap[i][j] = step[istep - 1][i][j];
					}
				}
				break;
			default:
				break;
			}
		}
	}
}/*                           移动模块 start                               */
void MoveBox(int aiMap[][16], int iPlayerX, int iPlayerY, int iSelect, int aiMap2[][16]){
	int iPlayerX1, iPlayerY1;
	int iPlayerX2, iPlayerY2;
	switch (iSelect){
	case 1://向上移动
		iPlayerX1 = iPlayerX - 1;
		iPlayerY1 = iPlayerY;
		iPlayerX2 = iPlayerX - 2;
		iPlayerY2 = iPlayerY;
		break;
	case 2://向左移动
		iPlayerX1 = iPlayerX ;
		iPlayerY1 = iPlayerY - 1;
		iPlayerX2 = iPlayerX ;
		iPlayerY2 = iPlayerY - 2;
		break;
	case 3://向右移动
		iPlayerX1 = iPlayerX ;
		iPlayerY1 = iPlayerY + 1;
		iPlayerX2 = iPlayerX ;
		iPlayerY2 = iPlayerY + 2;
		break;
	case 4://向下移动
		iPlayerX1 = iPlayerX + 1;
		iPlayerY1 = iPlayerY;
		iPlayerX2 = iPlayerX +2;
		iPlayerY2 = iPlayerY;
		break;
	case 5://回撤

	default:
		break;
	}
	switch (aiMap[iPlayerX1][iPlayerY1])
	{
	case WALL:
		break;
	case SPACE:
	case TARGET:
		aiMap[iPlayerX1][iPlayerY1] = PERSON;
		istep++;
		step[istep][iPlayerX1][iPlayerY1] = PERSON;
		if (aiMap2[iPlayerX][iPlayerY] == TARGET || aiMap2[iPlayerX][iPlayerY] == TARGET_IN){
			aiMap[iPlayerX][iPlayerY] = TARGET;//小人所在位置为空目的地或满目的地，小人移动后恢复
			step[istep][iPlayerX][iPlayerY] = TARGET;
		}
		else{
			aiMap[iPlayerX][iPlayerY] = SPACE;
			step[istep][iPlayerX][iPlayerY] = SPACE;
		}
		break;
	case BOX:
	case TARGET_IN:
		if (aiMap[iPlayerX2][iPlayerY2] == TARGET){
			istep++;
			aiMap[iPlayerX2][iPlayerY2] = TARGET_IN;
			aiMap[iPlayerX1][iPlayerY1] = PERSON;
			step[istep][iPlayerX2][iPlayerY2] = TARGET_IN;
			step[istep][iPlayerX1][iPlayerY1] = PERSON;
		}
		else if (aiMap[iPlayerX2][iPlayerY2] == SPACE)
		{
			istep++;
			aiMap[iPlayerX2][iPlayerY2] = BOX;
			aiMap[iPlayerX1][iPlayerY1] = PERSON;
			step[istep][iPlayerX2][iPlayerY2] = BOX;
			step[istep][iPlayerX1][iPlayerY1] = PERSON;
		}
		else
			break;
		if (aiMap2[iPlayerX][iPlayerY] == TARGET || aiMap2[iPlayerX][iPlayerY] == TARGET_IN){
			aiMap[iPlayerX][iPlayerY] = TARGET;
			step[istep][iPlayerX][iPlayerY] = TARGET;
		}
		else{
			aiMap[iPlayerX][iPlayerY] = SPACE;
			step[istep][iPlayerX][iPlayerY] = SPACE;
		}
		break;
	}

}
/*                           移动模块 end                                 */
/*                             关卡   start                               */
void GetLevel1(){
	printf("第一关");
	int aiMap2[14][16];
	int i, j, k,iSum=0;//iSum表示箱子数量
	int aiMap[14][16] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 3, 4, 2, 1, 1, 2, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 3, 4, 6, 4, 2, 2, 3, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 3, 2, 4, 2, 4, 3, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	istep = 0;
	for (k = 0; k < 20; k++){
		for (i = 0; i < 14; i++){
			for (j = 0; j < 16; j++){
				aiMap2[i][j] = aiMap[i][j];
				step[k][i][j] = aiMap[i][j];
				if (aiMap[i][j] == TARGET || aiMap[i][j] == TARGET_IN)//记录箱子个数
					iSum++;
			}
		}
	}
	if (PlayGame(aiMap, aiMap2, iSum, 1) != KEY_RETURN)
		GetLevel2();
}
void GetLevel2(){
	printf("第二关");
	int aiMap2[14][16];
	int j, i,iSum=0;
	int aiMap[14][16] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 2, 1, 1, 2, 2, 2, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 2, 2, 4, 2, 2, 2, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 2, 1, 1, 1, 2, 4, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 1, 3, 3, 3, 1, 2, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 2, 1, 3, 3, 1, 1, 2, 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 2, 4, 2, 2, 4, 2, 2, 4, 2, 1, 0, 0, 0 },
		{ 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 6, 2, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	};
	for (i = 0; i < 14; i++){
		for (j = 0; j < 16; j++){
			aiMap2[i][j] = aiMap[i][j];
			if (aiMap[i][j] == TARGET || aiMap[i][j] == TARGET_IN)//记录箱子个数
				iSum++;
		}
	}
	if (PlayGame(aiMap, aiMap2, iSum, 2) != KEY_RETURN)
		GetLevel3();
}
void GetLevel3(){
	printf("第三关");
	int aiMap2[14][16];
	int j, i, iSum = 0;
	int aiMap[14][16] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 0, 0 },
		{ 0, 0, 1, 2, 4, 2, 1, 1, 1, 1, 4, 2, 2, 1, 0, 0 },
		{ 0, 0, 1, 2, 2, 4, 3, 3, 3, 3, 2, 4, 2, 1, 0, 0 },
		{ 0, 0, 1, 1, 2, 2, 2, 2, 1, 2, 6, 2, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	};
	for (i = 0; i < 14; i++){
		for (j = 0; j < 16; j++){
			aiMap2[i][j] = aiMap[i][j];
			if (aiMap[i][j] == TARGET || aiMap[i][j] == TARGET_IN)//记录箱子个数
				iSum++;
		}
	}
	if (PlayGame(aiMap, aiMap2, iSum, 3) != KEY_RETURN)
		GetLevel4();
}
void GetLevel4(){
	printf("第四关");
	int aiMap2[14][16];
	int j, i, iSum = 0;
	int aiMap[14][16] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 2, 2, 2, 1, 3, 2, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 2, 2, 4, 3, 3, 3, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 2, 2, 4, 2, 1, 5, 3, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 2, 1, 1, 4, 1, 2, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 2, 2, 4, 2, 2, 4, 2, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 6, 2, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	};
	for (i = 0; i < 14; i++){
		for (j = 0; j < 16; j++){
			aiMap2[i][j] = aiMap[i][j];
			if (aiMap[i][j] == TARGET || aiMap[i][j] == TARGET_IN)//记录箱子个数
				iSum++;
		}
	}
	if (PlayGame(aiMap, aiMap2, iSum, 4) != KEY_RETURN)
		GetLevel5();
}
void GetLevel5(){
	printf("第五关");
	int aiMap2[14][16];
	int j, i, iSum = 0;
	int aiMap[14][16] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 2, 2, 1, 0, 0 },
		{ 0, 1, 2, 4, 2, 2, 2, 2, 2, 4, 2, 6, 2, 1, 0, 0 },
		{ 0, 1, 1, 2, 1, 4, 1, 1, 3, 1, 1, 2, 2, 1, 0, 0 },
		{ 0, 0, 1, 2, 2, 3, 3, 3, 5, 3, 2, 4, 2, 1, 0, 0 },
		{ 0, 0, 1, 2, 4, 1, 2, 1, 3, 1, 2, 1, 2, 1, 0, 0 },
		{ 0, 0, 1, 1, 2, 2, 2, 2, 4, 2, 2, 2, 2, 1, 0, 0 },
		{ 0, 0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	};
	for (i = 0; i < 14; i++){
		for (j = 0; j < 16; j++){
			aiMap2[i][j] = aiMap[i][j];
			if (aiMap[i][j] == TARGET || aiMap[i][j] == TARGET_IN)//记录箱子个数
				iSum++;
		}
	}
	if (PlayGame(aiMap, aiMap2, iSum, 5) != KEY_RETURN)
		GetLevel6();

}
void GetLevel6(){
	printf("第六关");
	int aiMap2[14][16];
	int j, i, iSum = 0;
	int aiMap[14][16] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 2, 3, 3, 2, 4, 1, 2, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 2, 1, 3, 5, 2, 2, 2, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 2, 5, 3, 1, 4, 2, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 4, 2, 2, 4, 2, 2, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 2, 2, 2, 1, 1, 2, 6, 1, 2, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	};
	for (i = 0; i < 14; i++){
		for (j = 0; j < 16; j++){
			aiMap2[i][j] = aiMap[i][j];
			if (aiMap[i][j] == TARGET || aiMap[i][j] == TARGET_IN)//记录箱子个数
				iSum++;
		}
	}
	if (PlayGame(aiMap, aiMap2, iSum, 6) != KEY_RETURN)
		GetLevel1();
} 
