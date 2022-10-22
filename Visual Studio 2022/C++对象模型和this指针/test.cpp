#include <iostream>
using namespace std;

int t;

class students
{
public:
	
	static void age(int x)
	{
		t = x;
	}
};

int main()
{
	students s1;
	s1.age(1);
	cout << t << endl;
	

	system("pause");
	return 0;
}