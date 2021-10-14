#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE_LENGTH  200

int main(int argc, const char *argv[]){

	if (argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		//printf("All good Pt. 2 ");
	}

	//---------------------------------//

	FILE *fin = fopen(argv[1], "r");

	if (fin == (void*)0) 
	{
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	} 
	else
	{
		//printf("All good");
	}

	//---------------------------------//
	char out_file[MAX_LINE_LENGTH]; // empty string
	strcpy(out_file, argv[1]);
	strcat(out_file, ".echo");

	FILE *fout = fopen(out_file, "w+");

	//----------------------------------//
	char line[MAX_LINE_LENGTH] = {0}; // stores current line as we parse each line
	unsigned int line_num = 0; // stores curr line number
	while (fgets(line, sizeof(line), fin)) {
		line_num ++;
		printf("[%04d] %s",line_num, line);
		fprintf(fout, %s, line);
	}
}
