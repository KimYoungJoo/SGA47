#include <iostream>
#include <conio.h>
#include "test.h"

using namespace std;

// template test
// ���ø� �׽�Ʈ.
int main(void)
{
	// generic programming...

	Rect<int> a;
	Rect<int*> b;

	int* pa = new int(3);

	b.lt.x = pa;


	delete b.lt.x;


	_getch();
	return 0;
}
