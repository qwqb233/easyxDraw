#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <windowsx.h>

using namespace std;


//设定窗口的大小
#define WIDTH 640
#define HIGH  480

//回调函数
typedef void (*fun_callback_t)(int mouseX,int mouseY);
fun_callback_t g_fun_cd = NULL;

/*
* 画十字
* 输入鼠标位置
*/
void drawCross(int mouseX,int mouseY)
{
	int tempX = mouseX / 10;
	int tempY = mouseY / 10;
	fillrectangle(tempX * 10, tempY * 10, tempX * 10 + 10, tempY * 10 + 10);
	fillrectangle(tempX * 10 + 10, tempY * 10, tempX * 10 + 20, tempY * 10 + 10);
	fillrectangle(tempX * 10, tempY * 10 + 10, tempX * 10 + 10, tempY * 10 + 20);
	fillrectangle(tempX * 10 - 10, tempY * 10, tempX * 10, tempY * 10 + 10);
	fillrectangle(tempX * 10, tempY * 10 - 10, tempX * 10 + 10, tempY * 10);
}

/*
* 画点
* 输入鼠标位置
*/
void drawPoint(int mouseX, int mouseY)
{
	//取整
	int tempX = mouseX / 10;
	int tempY = mouseY / 10;
	//填充
	fillrectangle(tempX * 10, tempY * 10, tempX * 10 + 10, tempY * 10 + 10);
}

/*
* 设置回调函数指针
* 输入函数指针
*/
void setcallback(fun_callback_t cd)
{
	g_fun_cd = cd;
}

/*
* 清屏，回复网格状态
*/
void clean()
{
	cleardevice();
	setlinecolor(RED);
	setfillcolor(WHITE);
	//画网格，大小10x10
	for (int i = 0; i <= WIDTH; i += 10)
		line(i, 0, i, HIGH);

	for (int i = 0; i <= HIGH; i += 10)
		line(0, i, WIDTH, i);
}

int main()
{
	//选择函数列表中的函数
	static int status = 1;
	fun_callback_t funList[] = {drawPoint,drawCross};
	
	//创建窗口
	initgraph(WIDTH, HIGH);
	//获取屏幕的大小
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHigh = GetSystemMetrics(SM_CYSCREEN);

	setbkcolor(BLACK);
	cleardevice();
	
	//设置窗口的名称
	HWND hnd = GetHWnd();
	SetWindowText(hnd, (LPCUWSTR)"easyx");

	//获取窗口位置
	HWND gameh = ::FindWindow(NULL,(LPCUWSTR)"easyx");
	RECT r1;
	::GetWindowRect(gameh, &r1);
	cout << "left:" << r1.left << endl;
	cout << "right" << r1.right<<endl;
	cout << "top" << r1.top<<endl;
	cout << "bottom" << r1.bottom<<endl;
	
	//清屏
	clean();

	//easyx信息处理结构体
	ExMessage* exmessage = new ExMessage;

	//鼠标状态机状态变量
	bool mouseLStatus = 0;
	bool mouseRStatus = 0;

	//设置画笔初始状态
	setcallback(drawCross);

	//记录选择方格的坐标
	int selectBlock[2];

	//主循环
	while (1)
	{
		//初始鼠标位置
		int mouseX = 0;
		int mouseY = 0;

		//监听信息
		getmessage(exmessage, -1);

		//当左键按下是获取鼠标位置并画对应图案
		if (exmessage->lbutton)
		{
			mouseX = exmessage->x;
			mouseY = exmessage->y;
			g_fun_cd(mouseX, mouseY);
		}

		//右键清屏
		if (exmessage->rbutton) clean();

		//滚轮向上扩大笔刷
		if (exmessage->wheel > 0)
		{
			if (++status < sizeof(funList) / sizeof(funList[0]))
				setcallback(funList[status]);
			else status--;
		}

		//滚轮向下减小笔刷
		if (exmessage->wheel < 0)
		{
			if (--status >= 0)
				setcallback(funList[status]);
			else status++;
		}

		//按下ESC后退出
		if (exmessage->vkcode == VK_ESCAPE) closegraph();

		//记录坐标
		selectBlock[0] = mouseX / 10 * 10 + 5;
		selectBlock[1] = mouseY / 10 * 10 + 5;
		cout << "selectBlock:(" << selectBlock[0] << "," << selectBlock[1] << ")\n";
	}
	/*
	while (1)
	{

		
		int lastX = 0;
		int lastY = 0;
		if (mouseLStatus)
		{
			lastX = exmessage->x;
			lastY = exmessage->y;
		}
		
		getmessage(exmessage, -1);
		if (exmessage->lbutton && !mouseRStatus) mouseLStatus = !mouseLStatus;
		if (exmessage->rbutton && !mouseLStatus) mouseRStatus = !mouseRStatus;

		if (mouseLStatus)
		{
			if (lastX == 0 && lastY == 0)
			{
				lastX = exmessage->x;
				lastY = exmessage->y;
			}
			setlinecolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(exmessage->x, exmessage->y, 3);
			for (int i = 0; i < 10; i++)
			{
				line(lastX+i, lastY+i, exmessage->x+i, exmessage->y+i);
				line(lastX-i, lastY-i, exmessage->x-i, exmessage->y-i);
			}
		}
		if (mouseRStatus)
		{
			if (lastX == 0 && lastY == 0)
			{
				lastX = exmessage->x;
				lastY = exmessage->y;
			}
			setlinecolor(getbkcolor());
			setfillcolor(getbkcolor());
			fillcircle(exmessage->x, exmessage->y, 10);
			line(lastX, lastY, exmessage->x, exmessage->y);
		}
		
		
		if (exmessage->vkcode == VK_ESCAPE) closegraph();
	}
	*/

	return 1;
}
