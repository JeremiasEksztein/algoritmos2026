#include <stdio.h>

#include "common.h"
#include "tree.h"
#include "student.h"

void showMenuHeader(void)
{
	
}

void handleInput(int input, tBinaryTree *data)
{
	tStudent key, read;

	key.id = input;

	if(binaryTreeFind(data, &key, &read, sizeof(tStudent), studentCmp))
	
}

int main(void)
{
	FILE *fpStudents;
	tBinaryTree bstStudents;
	int idQueried, shouldExit = FALSE, ret;

	fpStudents = fopen("alumnos.dat", "rb");

	if(!fpStudents) {
		return ERR;
	}

	binaryTreeNew(&bstStudents);

	ret = binaryTreeLoadFromOrderedFile(
		&bstStudents, 
		&fpStudents, 
		sizeof(tStudent)
	);

	if(ret != OK) {
		binaryTreeDelete(&bstStudents);
		fclose(fpStudents);
		return ERR;
	}

	fclose(fpStudents);

	while(!shouldExit) {
		showMenuHeader();

		scanf("%d", &idQueried);

		if(idQueried == -1) {
			shouldExit = TRUE;
			continue;
		}		

		handleInput(idQueried, &bstStudents);
	}

	binaryTreeDelete(&bstStudents);

	return OK;
}
