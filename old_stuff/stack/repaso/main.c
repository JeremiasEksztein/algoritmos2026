#include "stack.h"

typedef enum {
	Add,
	Sub,
	Mult,
	Div,
	Mod
} Op;

int main(int argc, char** argv)
{
	Stack ops;

	stack_new(&ops);

	
	
	stack_destroy(&ops);

	return 0;
}
