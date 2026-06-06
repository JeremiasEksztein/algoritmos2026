#include "list.h"
#include <assert.h>

int print_int(const void *integer) 
{
	const int *i = integer;
	printf("[%d]\n", *i);
	return 0;
}

int cmp_int(const void *lhs, const void *rhs)
{
	const int *l = lhs, *r = rhs;

	return *l - *r;
}

#define COLOR_BLUE "\x1b[34"
#define COLOR_RED "\x1b[31"
#define COLOR_YELLOW "\x1b[33"
#define COLOR_RESET "\x1b[39"

#define START_BLINK "\x1b[5m"
#define END_BLINK "\x1b[25m"

void show_menu_header(void)
{
	printf(
		"Simply Linked List\n"
	   	"------------------------------------\n"
		"1)  Make new list\n"
		"2)  Push element front\n"
		"3)  Push element back\n"
		"4)  Add element in ith position\n"
		"5)  Pop element front\n"
		"6)  Pop element back\n"
		"7)  Remove element in ith position\n"
		"8)  Get lenght of the list\n"
		"9)  Get ith element from the list\n"
		"10) Set ith element from the list\n"
		"11) Show list\n"
		"12) Order list\n"
		"13) Destroy list\n" 
		"14) Exit program\n"
		"Please input a query\n"
		START_BLINK	" > " END_BLINK
	);
}

void handle_user_input(SLinkedList *list, int input)
{
	int buf, pos;
	
	printf("\x1b[2J\x1b[H");
	switch(input) {
		case 1:
			printf("Creating list\n");
			slinkedlist_destroy(list);
			slinkedlist_new(list);
			printf("List created\n");
			break;
		case 2:
			printf("Please input the number to push\n");
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &buf);
			if(slinkedlist_addlo(list, &buf, sizeof(int)) == ERR) {
				printf("Error when pushing element\n");
				printf("Terminating...\n");
				exit(1);
			} else {
				printf("Succesfully pushed %d to the list\n", buf);
			}
			break;
		case 3:
			printf("Please input the number to push\n");
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &buf);			
			if(slinkedlist_addhi(list, &buf, sizeof(int)) == ERR) {
				printf("Error when pushing element\n");
				printf("Terminating...\n");
				exit(1);
			} else {
				printf("Succesfully pushed %d to the list\n", buf);
			}
			break;
		case 4:
			printf("Please input the number to add\n");
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &buf);	

			printf("Please input the position\n");	
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &pos);	
			
			if(slinkedlist_add(list, pos, &buf, sizeof(int)) == ERR) {
				printf("Error when inserting element\n");
			} else {
				printf("Succesfully pushed %d to the list\n", buf);
			}
			break;
		case 5:
			printf("Popping element...\n");
			if(slinkedlist_remlo(list, &buf, sizeof(int)) == ERR) {
				printf("Error when popping element\n");
			} else {
				printf("Succesfully popped %d from the list\n", buf);
			}
			break;
		case 6:
			printf("Popping element...\n");
			if(slinkedlist_remhi(list, &buf, sizeof(int)) == ERR) {
				printf("Error when popping element\n");
			} else {
				printf("Succesfully popped %d from the list\n", buf);
			}
			break;
		case 7:
			printf("Please input the position\n");	
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &pos);	
			
			if(slinkedlist_rem(list, pos, &buf, sizeof(int)) == ERR) {
				printf("Error when removing element\n");
			} else {
				printf("Succesfully removed %d from the list\n", buf);
			}
			break;
		case 8:
			printf("Querying lenght...\n");
			printf("The lenght of the list is %lu\n", slinkedlist_len(list));
			break;
		case 9:
			printf("Please input position\n");
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &pos);

			if(slinkedlist_get(list, pos, &buf, sizeof(int)) == ERR) {
				printf("Error when querying %dth element from the list\n", pos);
			} else {
				printf("%dth element of the list has value of %d\n", pos, buf);
			}
			break;
		case 10:
			printf("Please input the new number to set\n");
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &buf);	

			printf("Please input the position\n");	
			printf(START_BLINK " > " END_BLINK);
			scanf("%d", &pos);	
			
			if(slinkedlist_set(list, pos, &buf, sizeof(int)) == ERR) {
				printf("Error when setting %dith element of the list\n", pos);
			} else {
				printf("Succesfully set %dth element of the list to %d\n", pos, buf);
			}
			break;
		case 11:
			printf("Showing list...\n");
			slinkedlist_print(list, print_int);
			break;
		case 12:
			printf("Ordering list...\n");
			slinkedlist_sort(list, cmp_int);
			printf("List ordered\n");
			break;
		case 13:
			printf("Destroying list...\n");
			slinkedlist_destroy(list);
			break;
		default:
			printf("Incorrect input. Try again\n");
	}	

	getc(stdin);
	getc(stdin);

	printf("\x1b[2J\x1b[H");
}

int main(void)
{
	SLinkedList l;
	int program_ended = 0;
	int input;
	
	while(!program_ended) {
		show_menu_header();

		scanf("%d", &input);

		if(input == 14) {
			printf("\x1b[2J\x1b[H");
			printf("Exiting...\n");
			program_ended = 1;
			continue;
		}
		
		handle_user_input(&l, input);
	}

	slinkedlist_destroy(&l);

	return 0;
}
/*
	
	Computer tmp;
	int i;

	printf("First pass\n");
	
	for(i = 0; i < 50; i++) {
		slinkedlist_addlo(&l, arr + i, sizeof(Computer));
		computer_show(arr + i);
	}

	printf("Second pass\n");

	slinkedlist_sort(&l, computer_cmp);
	slinkedlist_print(&l, computer_print);

	for(i = 0; i < 50; i++) {
		slinkedlist_remlo(&l, &tmp, sizeof(Computer));
		computer_show(&tmp);
	}

	slinkedlist_destroy(&l);
	
	return 0;
*/

/*
int main(void)
{
	SLinkedList l;
	int arr[] = {5,4,3,2,1}, i;

	slinkedlist_new(&l);

	for(i = 0; i < 5; ++i) {
		slinkedlist_addlo(&l, arr + i, sizeof(int));
	}

	puts("\n");
	slinkedlist_print(&l, print_int);
	printf("\n");
	slinkedlist_rev_print(&l, print_int);

	slinkedlist_sort(&l, cmp_int);

	puts("\n");
	slinkedlist_print(&l, print_int);

	slinkedlist_destroy(&l);

	return 0;
}
*/
