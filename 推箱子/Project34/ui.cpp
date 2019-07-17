//���õ�ͷ�ļ�
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "Sokoban.h"
#include <string.h>

// ��ͼʱʹ�õı�ʾ�ߺ�ʳ���Բ�ε�ֱ�����ص������
#define CELL_PIXEL			20

// ������ͼ����ɫ
#define COLOR_ROAD			RGB(0,255,127)
#define COLOR_WALL			RGB(216,191,216)
#define COLOR_PERSON		RGB(0,255,255)
#define COLOR_FLAG			RGB(220,20,60)
#define COLOR_BOXES         RGB(173,255,47)
#define COLOR_TEXT          RGB(173,216,230)
#define COLOR_BOUNDARY      RGB(139,134,130)

//��������

#define INIT_DIR PERSON_LEFT
#define TIMER_ID 12340

#define MAXBOUNDARY_X		30	// ��Ϸ�����С
#define MAXBOUNDARY_Y		30	// ��Ϸ�����С

// ȫ�ֱ���
HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;
int map[SIZE_X][SIZE_Y];
//�˵�����
GAME_COORD Person;
POINT ptLeftTop;		// ���Ͻ�
POINT ptRightBottom;	// ���½�

//���ӵ�����
GAME_COORD Boxes[4];

int flag = 0;
int mmm = 0;


//��������
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

/*******************************************************
* #############   ��ں���WinMain   ####################
****************************************/


int WINAPI WinMain(
	HINSTANCE hinstance, // ����ʵ��������ڳ������У����̴������ɲ���ϵͳ��Ӧ�ó�����
	HINSTANCE hPrevInstance, // �����̵ĳ���ʵ�����
	LPSTR lpCmdLine,  // �����в�������λ����������C����main��������argc��argv,����û�а��ո�����з�
	int nCmdShow)   // ����ָ�������Ƿ���Ҫ��ʾ�Ĳ�����
{
	WNDCLASS wc;
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// ���ڵĲ˵�����Դ����
	wc.lpszMenuName = (LPCSTR) "MainMenu";
	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
	wc.lpszClassName = (LPCSTR)"MainWClass";

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�


	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",			// �����������������Ѿ�ע���˵Ĵ�����
		"SOKOBAN Game!!",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}

	// ���ڴ����ɹ����������С�

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);

	// ���½�����Ϣѭ������ȡ��Ϣ--������Ϣ--������Ϣ���ɴ��ڵ���Ϣ��������������Ϣ��
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void GamePaint(HWND hwnd)
{
	HPEN hpen;
	//HBRUSH hbrush;
	HDC hdc, hdcmem;
	HBITMAP hbmMem;

	HPEN hPenBoundary;
	HPEN hOldPen;

	HBRUSH hBrushROAD;
	HBRUSH hBrushWALL;
	HBRUSH hBrushPERSON;
	HBRUSH hBrushFLAG;
	HBRUSH hBrushBOXES;

	HBRUSH hOldBrush;

	//HFONT hFont, hOldFont;

	RECT rect;


	MAP_COORD lpwall[8];


	GetClientRect(hwnd, &rect);//�õ�hwnd���ڵĽ������꣬����rect

	hdc = GetDC(hwnd);

	// ע�� CreateCompatibleDC �е���һ�λ���
	// Before an application can use a memory DC for drawing operations, 
	// it must select a bitmap of the correct width and height into the DC. 
	// To select a bitmap into a DC, use the CreateCompatibleBitmap function
	// ע�⣺
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd183488(v=vs.85).aspx
	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
		rect.right - rect.left, rect.bottom - rect.top);

	SelectObject(hdcmem, hbmMem);

	// ������Ҫ�õ���PEN��BRUSH
	hBrushROAD = CreateSolidBrush(COLOR_ROAD); // RGB��ɫ��ʵ��BRUSH
	hpen = CreatePen(PS_INSIDEFRAME, 1, RGB(0, 0, 0));  // PEN�� PS_NULL��ʾ���ɼ�
	hBrushWALL = CreateSolidBrush(COLOR_WALL);
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);
	hBrushPERSON = CreateSolidBrush(COLOR_PERSON);
	hBrushFLAG = CreateSolidBrush(COLOR_FLAG);
	hBrushBOXES = CreateSolidBrush(COLOR_BOXES);




	/*******************************************************************************
	* #############  ������  ################
	*
	*******************************************************************************/
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	/*******************************************************************************
	* #############  ��ǽ  ################
	*
	*******************************************************************************/

	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;


	// ����ͼ��Ҫ�õ�PEN��BRUSHѡ��DC��
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushWALL);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	LONG width = (ptRightBottom.y - ptLeftTop.y) / SIZE_Y;
	LONG height = (ptRightBottom.x - ptLeftTop.x) / SIZE_X;
	GetWall(lpwall);
	for (int i = 0; i < 8; i++)
	{
		Rectangle(hdcmem,
			lpwall[i].left_top.x*width + 10,
			lpwall[i].left_top.y*height + 10,
			lpwall[i].right_bottom.x*width + 10,
			lpwall[i].right_bottom.y*height + 10
		);

	}
	//�߿�
	SelectObject(hdcmem, hPenBoundary);

	// ��PEN�ƶ�����Ҫ���Ƶķ�������Ͻ�
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
	// ����һ��������ʾLineTo����
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom - 50);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom - 50);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

	// ����ͼ��Ҫ�õ�PEN��BRUSHѡ��DC��
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushFLAG);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);
	for (INT i = 0; i < SIZE_X; i++)
	{
		for (INT j = 0; j < SIZE_Y; j++)
		{
			if (map[i][j] == FLAG)
			{
				Ellipse(hdcmem,
					j * width + 10,
					i * height + 10,
					(j + 1) * width + 10,
					(i + 1) * height + 10
				);
			}
		}
	}
	//������
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushBOXES);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);
	for (INT i = 0; i < 4; i++)
	{
		Rectangle(hdcmem,
			Boxes[i].y*width + 10,
			Boxes[i].x*height + 10,
			(Boxes[i].y+1)*width+10,
			(Boxes[i].x+1)*height+10
			);
	}
	//����
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushPERSON);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);
	Ellipse(hdcmem,
		Person.y*width + 10,
		Person.x*height + 10,
		(Person.y + 1)*width + 10,
		(Person.x + 1)*height + 10
	);

	// ���ڴ�DC�л��꣬һ������Ĵ���DC�ϡ�
	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);


	/*******************************************************************************
	* #############  ���պ��ͷ���Դ  ################
	*
	*******************************************************************************/
	// ������Դ
	// DeleteObject �ͷ�GDI����
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hBrushWALL);
	DeleteObject(hBrushROAD);
	DeleteObject(hBrushPERSON);
	DeleteObject(hBrushFLAG);
	DeleteObject(hBrushBOXES);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	//DeleteObject(hFont);
	/*******************************************************************************
	* #############  ReleaseDC ����  ################
	* �ͷ�ռ�õ�DC��ϵͳ��Դ��
	*******************************************************************************/
	ReleaseDC(hwnd, hdc);
}

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	PGAME_COORD pCoordBoundary = GetBoundary();


	// ������Ϸ�߽�
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL * (pCoordBoundary->x + 1);
	rectBoundary.bottom = 10 + CELL_PIXEL * (pCoordBoundary->y + 1);

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // ����߽���������߱߿���ȡ�
		rectBoundary.bottom, //��������Ϣ������ʾ�ռ䡣
		TRUE);
}


LONG CALLBACK MainWndProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam)
	//int map[][SIZE_Y]) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		CreateGame(hwnd,
			INIT_DIR,map,Person,Boxes, MAXBOUNDARY_X, MAXBOUNDARY_Y);
		ReSizeGameWnd(hwnd);
		break;

		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GamePaint(hwnd);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:

		OnKeyDown(wParam,Person,map,flag,Boxes);
		GamePaint(hwnd);
		if (flag == 4)
		{
			KillTimer(hwnd, TIMER_ID);
			
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
		}
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	
	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
	
	

}
