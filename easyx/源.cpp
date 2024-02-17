#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <windowsx.h>

using namespace std;


//�趨���ڵĴ�С
#define WIDTH 640
#define HIGH  480

//�ص�����
typedef void (*fun_callback_t)(int mouseX,int mouseY);
fun_callback_t g_fun_cd = NULL;

/*
* ��ʮ��
* �������λ��
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
* ����
* �������λ��
*/
void drawPoint(int mouseX, int mouseY)
{
	//ȡ��
	int tempX = mouseX / 10;
	int tempY = mouseY / 10;
	//���
	fillrectangle(tempX * 10, tempY * 10, tempX * 10 + 10, tempY * 10 + 10);
}

/*
* ���ûص�����ָ��
* ���뺯��ָ��
*/
void setcallback(fun_callback_t cd)
{
	g_fun_cd = cd;
}

/*
* �������ظ�����״̬
*/
void clean()
{
	cleardevice();
	setlinecolor(RED);
	setfillcolor(WHITE);
	//�����񣬴�С10x10
	for (int i = 0; i <= WIDTH; i += 10)
		line(i, 0, i, HIGH);

	for (int i = 0; i <= HIGH; i += 10)
		line(0, i, WIDTH, i);
}

int main()
{
	//ѡ�����б��еĺ���
	static int status = 1;
	fun_callback_t funList[] = {drawPoint,drawCross};
	
	//��������
	initgraph(WIDTH, HIGH);
	//��ȡ��Ļ�Ĵ�С
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHigh = GetSystemMetrics(SM_CYSCREEN);

	setbkcolor(BLACK);
	cleardevice();
	
	//���ô��ڵ�����
	HWND hnd = GetHWnd();
	SetWindowText(hnd, (LPCUWSTR)"easyx");

	//��ȡ����λ��
	HWND gameh = ::FindWindow(NULL,(LPCUWSTR)"easyx");
	RECT r1;
	::GetWindowRect(gameh, &r1);
	cout << "left:" << r1.left << endl;
	cout << "right" << r1.right<<endl;
	cout << "top" << r1.top<<endl;
	cout << "bottom" << r1.bottom<<endl;
	
	//����
	clean();

	//easyx��Ϣ����ṹ��
	ExMessage* exmessage = new ExMessage;

	//���״̬��״̬����
	bool mouseLStatus = 0;
	bool mouseRStatus = 0;

	//���û��ʳ�ʼ״̬
	setcallback(drawCross);

	//��¼ѡ�񷽸������
	int selectBlock[2];

	//��ѭ��
	while (1)
	{
		//��ʼ���λ��
		int mouseX = 0;
		int mouseY = 0;

		//������Ϣ
		getmessage(exmessage, -1);

		//����������ǻ�ȡ���λ�ò�����Ӧͼ��
		if (exmessage->lbutton)
		{
			mouseX = exmessage->x;
			mouseY = exmessage->y;
			g_fun_cd(mouseX, mouseY);
		}

		//�Ҽ�����
		if (exmessage->rbutton) clean();

		//�������������ˢ
		if (exmessage->wheel > 0)
		{
			if (++status < sizeof(funList) / sizeof(funList[0]))
				setcallback(funList[status]);
			else status--;
		}

		//�������¼�С��ˢ
		if (exmessage->wheel < 0)
		{
			if (--status >= 0)
				setcallback(funList[status]);
			else status++;
		}

		//����ESC���˳�
		if (exmessage->vkcode == VK_ESCAPE) closegraph();

		//��¼����
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
