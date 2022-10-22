#include <iostream>
#include <queue>
#include <regex>
#include <string.h>
#include <WinSock2.h> // Windows 套接字
#pragma comment(lib, "ws2_32.lib")
using namespace std;

string g_strHost; // 域名
string g_strObject; // 资源路径

// 开始抓取
bool StartCatch(string url);
// 解析URL
bool AnalyseURL(string url);
// 获取网页
string GetHtml(string url);
// 下载图片
bool Download(string url, string filename);

int main()
{
	cout << "请输入起始链接：";

	string startURL;
	cin >> startURL;
	// 创建文件夹
	CreateDirectory(L"images", NULL);
	CreateDirectory(L"video", NULL);
	CreateDirectory(L"book", NULL);

	// 开始抓取
	StartCatch(startURL);

	system("pause");
	return 0;
}

// 开始抓取
bool StartCatch(string url)
{
	queue<string> q;
	q.push(url);

	while (!q.empty())
	{
		// 取出URL
		string currentUrl = q.front();
		q.pop();
		cout << "网址：" << currentUrl << endl;

		// 获取网页
		string html = GetHtml(currentUrl);
		cout << html.size() << endl;

		vector <string> vImageURL;
		// 正则表达式匹配所有的URL链接
		smatch mat;
		regex reg("http://[^\\s'\"<>()]+");
		string::const_iterator start = html.begin();
		string::const_iterator end = html.end();
		while (regex_search(start, end, mat, reg))
		{
			string per(mat[0].first, mat[0].second);
			vImageURL.push_back(per);

			start = mat[0].second;
		}

		for (int i = 0; i < vImageURL.size(); i++)
		{
			// cout << "URL链接：" << vImageURL[i] << endl;
			string imageUrl = vImageURL[i];
			if (imageUrl.find(".jpg") != string::npos || imageUrl.find(".png") != string::npos || imageUrl.find(".jpeg") != string::npos)
			{
				//获取文件名
				string filename = "./images/" + imageUrl.substr(imageUrl.find_last_of('/') + 1);
				// 下
				if (Download(imageUrl, filename) == false)
				{
					cout << "下载失败" << endl;
				}
				else
				{
					cout << "下载成功" << endl;
				}
			}
			else
			{
				q.push(imageUrl);
			}
		}
	}

	return true;
}

// 解析URL
bool AnalyseURL(string url)
{
	if (url.empty())
		return false;

	if (string::npos == url.find("http://") && string::npos == url.find("https://"))
		return false;

	int index = 0;
	if (string::npos != url.find("http://"))
	{
		index = 7;
	}
	if (string::npos != url.find("https://"))
	{
		index = 8;
	}

	// 截取协议
	int pos = url.find('/', index);
	if (string::npos == pos)
	{
		g_strHost = url.substr(index);
		g_strObject = "/";
	}
	else
	{
		g_strHost = url.substr(index, pos - index);
		g_strObject = url.substr(pos);
	}

	if (g_strHost.empty() || g_strObject.empty())
		return false;

	return true;
}

// 获取网页
string GetHtml(string url)
{
	// 解析URL
	if (AnalyseURL(url) == false)
		return "";

	// 初始化网络
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
		return "";

	// 创建套接字
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0); // HTTP底层TCP实现
	if (clientSocket == INVALID_SOCKET)
		return "";

	// 把域名转化为IP地址
	hostent * host = gethostbyname(g_strHost.c_str());
	if (host == NULL)
		return "";

	// 连接网络
	sockaddr_in sa;
	memcpy(&sa.sin_addr, host->h_addr, 4);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(80);

	if (SOCKET_ERROR == connect(clientSocket, (sockaddr*)&sa, sizeof(sa)))
		return "";

	// 发送GET请求
	string info;
	info += "GET " + g_strObject + " HTTP/1.1\r\n";
	info += "Host: " + g_strHost + "\r\n";
	info += "Connection: Close\r\n";
	info += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36\r\n";
	info += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n";
	info += "\r\n";

	if (SOCKET_ERROR == send(clientSocket, info.c_str(), info.length(), 0))
		return "";

	// 接收数据
	string html;
	char ch = 0;
	while (recv(clientSocket, &ch, sizeof(ch), 0))
	{
		html += ch;
	}

	// 关闭套接字
	closesocket(clientSocket);
	WSACleanup();

	return html;
}

// 下载图片
bool Download(string url, string filename)
{
	// 解析URL
	if (AnalyseURL(url) == false)
		return false;

	// 初始化网络
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
		return false;

	// 创建套接字
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0); // HTTP底层TCP实现
	if (clientSocket == INVALID_SOCKET)
		return false;

	// 把域名转化为IP地址
	hostent* host = gethostbyname(g_strHost.c_str());
	if (host == NULL)
		return false;

	// 连接网络
	sockaddr_in sa;
	memcpy(&sa.sin_addr, host->h_addr, 4);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(80);

	if (SOCKET_ERROR == connect(clientSocket, (sockaddr*)&sa, sizeof(sa)))
		return false;

	// 发送GET请求
	string info;
	info += "GET " + g_strObject + " HTTP/1.1\r\n";
	info += "Host: " + g_strHost + "\r\n";
	info += "Connection: Close\r\n";
	info += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36\r\n";
	info += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n";
	info += "\r\n";

	if (SOCKET_ERROR == send(clientSocket, info.c_str(), info.length(), 0))
		return false;

	// 接收数据
	char ch = 0;
	int nRecvNum = 0;
	while ((nRecvNum = recv(clientSocket, &ch, sizeof(ch), 0)) > 0)
	{
		if (ch == '\r')
		{
			nRecvNum = recv(clientSocket, &ch, sizeof(ch), 0);
			if (nRecvNum > 0 && ch == '\n')
			{
				nRecvNum = recv(clientSocket, &ch, sizeof(ch), 0);
				if (nRecvNum > 0 && ch == '\r')
				{
					nRecvNum = recv(clientSocket, &ch, sizeof(ch), 0);
					if (nRecvNum > 0 && ch == '\n')
					{
						break;
					}
				}
			}
		}
	}

	// 打开文件
	FILE *fp = fopen(filename.c_str(), "wb");
	if (fp == NULL)
		return false;

	// 接收数据
	ch = 0;
	nRecvNum = 0;
	while ((nRecvNum = recv(clientSocket, &ch, sizeof(ch), 0)) > 0)
	{
		fwrite(&ch, 1, nRecvNum, fp);
	}

	// 关闭文件
	fclose(fp);

	// 关闭套接字
	closesocket(clientSocket);
	WSACleanup();

	return true;
}