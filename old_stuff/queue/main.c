#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct Entry {
	int product_code;
	int quantity;
} Entry;

int main(int argc, char** argv) 
{
	FILE* fp;
	FILE* whole_sale;
	FILE* retail_sale;
	FILE* chosen_fp;
	Entry curr_entry;
	Entry tmp_entry;
	Entry pred_entry;
	int sum_quant;
	int lim;
	Queue q;
	
	if(argc != 2) {
		printf("Expected limit\n");
		return ERR;
	}	
	
	lim = atoi(argv[1]);
	fp = fopen("mov.dat", "rb");

	if(!fp) {
		printf("Failed to open \"mov.dat\"\n");
		return ERR;
	}	

	whole_sale = fopen("mayorista.dat", "wb");

	if(!whole_sale) {
		printf("Failed to create \"mayorista.dat\"\n");
		fclose(fp);
		return ERR;
	}
	
	retail_sale = fopen("minorista.dat", "wb");

	if(!retail_sale) {
		printf("Failed to create \"minorista.dat\"\n");
		fclose(whole_sale);
		fclose(fp);
		return ERR;
	}

	queue_new(&q);
	fread(&curr_entry, sizeof(Entry), 1, fp);
	while(!feof(fp)) {
		memcpy(&pred_entry, &curr_entry, sizeof(Entry));
		sum_quant = 0;

		while((curr_entry.product_code == pred_entry.product_code) && !feof(fp)) {
			sum_quant += curr_entry.quantity;
			queue_add(&q, &curr_entry, sizeof(Entry));	
			fread(&curr_entry, sizeof(Entry), 1, fp); 
		}

		chosen_fp = (sum_quant >= lim)
					? whole_sale
					: retail_sale;

		while(!queue_is_empty(&q)) {
			queue_rem(&q, &tmp_entry, sizeof(Entry));
			fwrite(&tmp_entry, sizeof(Entry), 1, chosen_fp);
		}			
	}

	fclose(retail_sale);
	fclose(whole_sale);
	fclose(fp);

	return OK;
}
