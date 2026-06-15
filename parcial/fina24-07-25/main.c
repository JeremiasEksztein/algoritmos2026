#include <stdio.h>

#include "common.h"
#include "xml.h"

int main(int argc, char **argv)
{
	int ret = FALSE;
	
	if(argc != 2) {
		eprintf(
			"[ERROR]: Expected path to file\n",
			"[USAGE]: %s <PATH>", 
			argv[0]
		);

		return ERR;
	}

	ret = validateXML(argv[1]);

	if(ret == FALSE) {
		printf(
			"File %s is not a valid XML file\n",
			argv[1]
		);
	} else {
		printf(
			"File %s is a valid XML file\n",
			argv[1]
		);
	}

	return OK;
}
