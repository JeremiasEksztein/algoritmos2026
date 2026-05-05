#include <stdio.h>

typedef struct {
	int prod;
	int q;
} Entry; 

int main(void)
{
	static Entry list[] = {
		{101, 30},
	};

	FILE* fp = fopen("mov.dat", "wb");

	if(!fp) {
		return 1;
	}

	fwrite(list, sizeof(list), 1, fp);

	return 0;
}
