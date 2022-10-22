#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<time.h>

// 以下数据可以自己调节
#define PointNum 288		// 圆圈分的数量（一圈钉子的数量）
#define LineNum 8100		// 循环绘制线的数量
#define RandNum 120			// 设置每次随机生成连接的数量
#define AddColor 52		// 增加的值 0 到 255 值越小越线越集中，越大越分散
#define SIZE 800			// 图像大小

// 以下参数不用调节
#define PI acos(-1.0)		// 圆周率
#define R (SIZE / 2 - 10)		// 半径

struct PointS
{
	int p;
	int x;
	int y;
};

struct LineS
{
	int StarP;				// 起点
	int EndP;				// 终点
};

PointS points[PointNum];
LineS lines[RandNum];

// 为了判断两点是否连线定义的一维数组
bool LineXY[(1 + PointNum) * PointNum / 2] = { false };
bool Line_Rand[(1 + PointNum) * PointNum / 2] = { false };

// 两条线是否连接
bool IsLineKed_Rand(int p1, int p2)
{
	if (p1 >= p2)
		return Line_Rand[(1 + p1) * p1 / 2 + p2];
	else
		return Line_Rand[(1 + p2) * p2 / 2 + p1];
}

// 储存已经绘制过的线
void Link_Rand(int p1, int p2)
{
	if (p1 >= p2)
		Line_Rand[(1 + p1) * p1 / 2 + p2] = true;
	else
		Line_Rand[(1 + p2) * p2 / 2 + p1] = true;
}

// 将随机生成的进行初始化
void Line2False()
{
	for (int i = 0; i < (1 + PointNum) * PointNum / 2; i++)
	{
		Line_Rand[i] = false;
	}
}

// 判断这两个点是否连线
bool IsLinked(int p1, int p2)
{
	if (p1 >= p2)
		return LineXY[(1 + p1) * p1 / 2 + p2];
	else
		return LineXY[(1 + p2) * p2 / 2 + p1];
}

// 储存已经绘制过的线
void Link(int p1, int p2)
{
	if (p1 >= p2)
		LineXY[(1 + p1) * p1 / 2 + p2] = true;
	else
		LineXY[(1 + p2) * p2 / 2 + p1] = true;
}

int Round(float x);								// 取整
void InitPoints();								// 初始化点
void ColorToGray(IMAGE* pimg);					// 彩色图像转换为灰度图像
void Random();									// 产生随机数
LineS Getline(IMAGE* pimg);						// 获取照片颜色
void ToColor(IMAGE* oriPic, IMAGE* linePic);	// 给绕线图赋予颜色

int main()
{
	initgraph(SIZE, SIZE);
	setbkcolor(WHITE);
	cleardevice();
	IMAGE imgpolt;									// 加载原图
	IMAGE oriPic;									// 储存原图
	IMAGE linePic;									// 线图
	loadimage(&imgpolt, _T("TG.jpeg"), SIZE, SIZE);	// 加载原图
	oriPic = imgpolt;								// 原图
	ColorToGray(&imgpolt);							// 将图片转换为灰度
	InitPoints();									// 初始化点
	srand((unsigned)time(NULL));					// 生成随机种子

	for (int i = 0; i < LineNum; i++)
	{
		Random();									// 随机生成 80
		LineS myline = Getline(&imgpolt);			// 计算 80 组点中平均值最小的
		Link(myline.StarP, myline.EndP);			// 记录绘制过的线防止重复绘制
		line(points[myline.StarP].x, points[myline.StarP].y, points[myline.EndP].x, points[myline.EndP].y);
		//Sleep(10);
	}
	_getch();

	// /*该部分是给线条加上颜色*/
	// saveimage(_T("test.png"));						// 保存一下绕线图
	// loadimage(&linePic, _T("test.png"), SIZE, SIZE); // 重新加载绕线图
	// ToColor(&oriPic, &linePic);						// 用原图将绕线图的颜色替换
	// putimage(0, 0, &oriPic);
	// _getch();
	return 0;
}

// 初始化点(想创新可以生成椭圆的位置坐标)
void InitPoints()
{
	for (int i = 0; i < PointNum; i++)
	{
		double a = i * PI * 2 / PointNum;
		points[i].p = i;
		points[i].x = int(SIZE / 2.0 + R * cos(a));
		points[i].y = int(SIZE / 2.0 - R * sin(a));
		setlinecolor(BLACK);
		circle(points[i].x, points[i].y, 3);
	}
}

// 彩色图像转换为灰度图像
void ColorToGray(IMAGE* pimg)
{
	DWORD* p = GetImageBuffer(pimg);	// 获取显示缓冲区指针
	COLORREF c;
	for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
	{
		c = BGR(p[i]);
		c = (GetRValue(c) * 299 + GetGValue(c) * 587 + GetBValue(c) * 114 + 500) / 1000;
		p[i] = RGB(c, c, c);
	}
}

// 随机生成线
void Random()
{
	for (int i = 0; i < RandNum; i++)
	{
		int starP;
		int endP;
		while (true)
		{
			starP = rand() % PointNum;
			endP = rand() % PointNum;
			if (IsLinked(starP, endP) == false
				&& IsLineKed_Rand(starP, endP) == false)
			{
				break;
			}
		}
		lines[i].StarP = starP;
		lines[i].EndP = endP;
		Link_Rand(starP, endP);		// 记录随机生成的线
	}
	Line2False();					// 初始化线值
}

// 四舍五入
int Round(float x)
{
	return (int)(x < 0 ? x - 0.5 : x + 0.5);
}

// 获取颜色最深的那一条线
LineS Getline(IMAGE* pimg)
{
	LineS mylines;
	mylines.StarP = 0;
	mylines.EndP = 0;
	DWORD* p_data = GetImageBuffer(pimg);
	int width = pimg->getwidth();
	double MaxNum = 255;
	int MYsteps;
	float X, Y;
	float CX, CY;
	for (int i = 0; i < RandNum; i++)
	{
		int SUMDN = 0;
		int x1 = points[lines[i].StarP].x;
		int y1 = points[lines[i].StarP].y;
		int x2 = points[lines[i].EndP].x;
		int y2 = points[lines[i].EndP].y;
		int steps = abs(x2 - x1) > abs(y2 - y1) ? abs(x2 - x1) : abs(y2 - y1);
		float x = (float)x1;
		float y = (float)y1;
		float cx = (float)(x2 - x1) / steps;
		float cy = (float)(y2 - y1) / steps;

		for (int j = 0; j < steps; j++)
		{
			int XIA = width * Round(y) + Round(x);
			SUMDN += GetRValue(p_data[XIA]);
			x += cx;
			y += cy;
		}
		double Aver = SUMDN / (steps * 1.0);

		if (Aver < MaxNum)
		{
			MaxNum = Aver;
			mylines = lines[i];
			MYsteps = steps;
			X = (float)x1;
			Y = (float)y1;
			CX = cx;
			CY = cy;
		}
	}
	if (MaxNum == 255)
	{
		return mylines;
	}
	for (int j = 0; j < MYsteps; j++)
	{
		int XIA = width * Round(Y) + Round(X);
		int c = GetRValue(p_data[XIA]) + AddColor > 255 ? 255 : GetRValue(p_data[XIA]) + AddColor;
		p_data[XIA] = RGB(c, c, c);
		X += CX;
		Y += CY;
	}
	return mylines;
}

// 给线图上色
void ToColor(IMAGE* oriPic, IMAGE* linePic)
{
	DWORD* ori_data = GetImageBuffer(oriPic);
	DWORD* line_data = GetImageBuffer(linePic);
	for (int i = oriPic->getwidth() * oriPic->getheight() - 1; i >= 0; i--)
	{
		int oriR = GetRValue(ori_data[i]);
		int oriG = GetGValue(ori_data[i]);
		int oriB = GetBValue(ori_data[i]);
		int lineR = GetRValue(line_data[i]);
		int lineG = GetGValue(line_data[i]);
		int lineB = GetBValue(line_data[i]);
		int newPicR = (int)(255 - (255 - lineR) * (255 - oriR) / 255.0);
		int newPicG = (int)(255 - (255 - lineG) * (255 - oriG) / 255.0);
		int newPicB = (int)(255 - (255 - lineB) * (255 - oriB) / 255.0);
		ori_data[i] = RGB(newPicR, newPicG, newPicB);
	}
}