#include "game.h"

int main(void)
{
	game snakegame;

	snakegame.Setup();

	clock_t st = clock();
	clock_t dt = 0;

	// 2. ��ü ���� ����...
	while (true)
	{
		// 3. �Է�ó��
		if (!snakegame.Input())
			break;

		// 4. ������Ʈ. ������ ����
		snakegame.Update(dt);

		// 5. �׸���.
		snakegame.Draw();

		dt = clock() - st;
		st = clock();

	}


	_getch();
	return 0;
}

