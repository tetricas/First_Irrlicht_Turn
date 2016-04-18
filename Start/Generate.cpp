#include "Generate.h"


Generate::Generate()
{
	n = 5, m = 5;
	map = new int*[n];
	for(size_t i = 0; i < n; i++)
		map[i] = new int[m];
}

void Generate::Create()
{
	srand(time(NULL));
	for(size_t i = 0; i < n; i++)
	for(size_t j = 0; j < m; j++)
		map[i][j] = rand() % 2;
}

Generate::~Generate()
{
	for(size_t i = 0; i < n; i++)
		delete[]map[i];
	delete[]map;
}
