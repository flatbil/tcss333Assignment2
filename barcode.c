#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BARCODE_LENGTH 16 //default barcode length

#ifdef USE_MALLOC_WRAPPERS
#  include "malloc_wrap.h"
#endif

int main_barcode(int argc, char *argv[]){
	//assume lines are never longer than 512 char
	char line1[512],line2[512];
	char *inputfiles[2]={0,0},*outputfile=0;
	FILE *inputfp1=0,*inputfp2=0,*outputfp=stdout;
	if(argc !=3 && argc !=5){
		fprintf(stderr,"The command is bwa barcode <-o outputFile> R1file R2file\n");
		return 1;
	}
	//***********************************************************************
	//parse the command line
	//
	//check for case when there are 3 arguments (i.e. no -o flag)
	//
	//check the case when there are 5 arguments
	//check that there actually is a -o flag and an argument following it
	//********************************************************************
	if(argc == 3){
		inputfiles[0] = *argv+1;
		inputfiles[1] = *argv+2;
	}
	else if(argc == 5 && *argv+1 == '-o'){
		outputfile = *argv+2;
		inputfiles[0] = *argv+3;
		inputfiles[1] = *argv+4;
	}
	else {
		printf(stderr,"The command is bwa barcode <-o outputFile> R1file R2file\n");
	}
	//**********************************************************************
	//open the files
	//use fopen to open streams to the two input files and the output file if one is given
	//check that the open is successful	(i.e. that the file pointers are not 0)			
 //**********************************************************************
	inputfp1 = fopen(inputfiles[0], 'r');
	if (inputfp1 == 0){
		printf(stderr,"inputfile 1 did not open");
	}
	inputfp2 = fopen(inputfiles[1], 'r');
	if (inputfp1 == 0){
		printf(stderr,"inputfile 2 did not open");
	}
	
	if(argc == 5) {
		outputfp = fopen(outputfile, 'w');
		if (inputfp1 == 0){
			printf(stderr,"outputfile did not open");
		}
	
	}
	printf("all good");
	
	
 //**********************************************************************
 //now print out a new file which is the same as file2 with the exception that
 //the header lines have a colon and the first BARCODE_LENGTH characters of the 
 //sequence line from file 1
 //
 //HINT: this can be done with one while loop using fgets, strlen and fprintf
 //HINT:  use the modulo % operator to figure out which lines are sequence lines
 //**********************************************************************
	while(!feof(inputfp1) || !feof(inputfp2)){
		int i = 1;
		if (i%4==1){
			fgets(line1,256, inputfp2);
			i++;
		}
		else if (i%4==2){
			fgets(line2, 16, inputfp1);
			fprintf(outputfile, "%s:%s", line1, line2);
			fgets(outputfile, 256, inputfp2);
			i++;
		}
		
		else {
			fgets(outputfile, 256, inputfp2);
			fprintf(outputfile, "%s\n");
			
		}
		
		 
	}

	fclose(inputfp1);
	fclose(inputfp2);
	if(outputfp !=stdout)fclose(outputfp);
	return 0;
}
