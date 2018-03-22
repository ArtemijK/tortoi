#include <stdio.h>
//#include <iostream>
#include <string.h>
#include <stdlib.h>


struct aeroflot{
    char destination[20];
    int number;
    char brand[10];
};

typedef struct aeroflot aeroflot;

void sort (aeroflot* , int, FILE*, FILE*);
void name (FILE*, aeroflot*, FILE*);
void punkt3 (aeroflot*);
void punkt4 (aeroflot*);


int main(){
	FILE *file;
	FILE *bitfile;
	FILE *newfile;
	int i=0, num;
	file = fopen("korolev_12_input.txt", "r");
	fscanf(file, "%d", &num);
	
	aeroflot *array = (aeroflot*) malloc ((num) * sizeof(aeroflot));
	while (fscanf (file, "%s%d%s", array[i].destination, &(array[i].number), array[i].brand) != EOF) {
		i++;
	}
	
	sort(array, num, bitfile, newfile);
	fclose(file);
	free(array);
	/*name(bitfile, array, newfile);
	free(array);*/
	array = (aeroflot*) malloc ((num) * sizeof(aeroflot));
	punkt3(array);
	free(array);
	punkt4(array);
	free(array);
	
	
}
/******************************************************************************************/
void sort(aeroflot *array, int num, FILE* bitfile, FILE* newfile){
	int j, i;
    int sortnumber;
	num--;
    aeroflot sortir;
    printf("\nDestination\tnumber\t\tbrand\n");

    for(i=0; i<num; i++){
        for(j=0; j<num-i; j++){
            if(((*(array+j)).number) > ((*(array+j+1)).number)){

                sortir = *(array+j);
                *(array+j) = *(array+j+1);
                *(array+j+1) = sortir;

            }
        }
    }
	
	for(i=0; i<num+1; i++){
        printf("%s\t\t%d\t\t%s\n", ((*(array+i)).destination), ((*(array+i)).number), ((*(array+i)).brand));
    }
	
	newfile = fopen("korolev_12_output.txt", "w+");
	fprintf(newfile, "NEW FILE, CREATED FROM BINARY\n\n");
	for(i=0; i<num+1; i++){
        fprintf(newfile, "%s %d %s\n", (*(array+i)).destination, (*(array+i)).number, (*(array+i)).brand);
    }
	fclose(newfile);
	
	
	num++;
	
	bitfile = fopen("korolev_12_bit.txt", "wb");    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	i=0;
	fwrite(&num, sizeof(int), 1, bitfile);
	while (i<num) {
		fwrite(&array[i], sizeof(aeroflot), 1, bitfile);
		i++;
	}
	fclose(bitfile);
}
/******************************************************************************************************/
void name (FILE* bitfile, aeroflot *array, FILE* newfile){
	int num, i, g=0;
	bitfile = fopen("korolev_12_bit.txt", "r");
	fread(&num, sizeof(int), 1, bitfile);
	while (i<num) {
		fread(&array[i], sizeof(aeroflot), 1, bitfile);
		i++;
	}
	fclose(bitfile);
	
	newfile = fopen("korolev_12_output.txt", "a");
	printf("Enter destination\n");
    char namedestination[20];
    scanf("%s", namedestination);
    printf("Departing to the destination\nNumber\tBrand\n");
    for (i=0; i<num; i++){
        if ( strcmp(namedestination, array[i].destination) == 0){
            printf("%d\t%s\n", ((*(array+i)).number), ((*(array+i)).brand));
			fprintf(newfile, "%d %s\n", (*(array+i)).number, (*(array+i)).brand);
            g++;
        } 

    }
    if (g==0) {
		printf("There are no such flights\n");
		fprintf(newfile, "\nThere are no such flights (%s)\n", namedestination);
	}
	fclose(newfile);
}

/**********************************************************************************************************/
void punkt3(aeroflot *array){
	int num, nbr, i=0;
   
	FILE *bitfile = fopen("korolev_12_bit.txt", "rb");
	
	fread(&num, sizeof(int), 1, bitfile);
	printf("\nInput number column - ");
	scanf("%d", &nbr);
	
	if (nbr == 1){
		while(i<num){
			fread(&array[i].destination, sizeof(char[20]), 1, bitfile);
			fseek(bitfile, sizeof(int) + sizeof(char[10]) + 2L, SEEK_CUR);
			i++;
		}
		for (i=0; i<num; i++){
			printf("%s\n", array[i].destination);
		}
				
	} if (nbr == 2){
		fseek(bitfile, sizeof(char[20]) + sizeof(int), SEEK_SET);
		while(i<num){
			fread(&array[i].number, (long)sizeof(int), 1, bitfile);
			fseek(bitfile, (long)(sizeof(char[20]) + sizeof(char[10]) + 2L), SEEK_CUR);
			i++;
		}
		for (i=0; i<num; i++){
			printf("%d\n", array[i].number);
		}	
		
	} if (nbr == 3){
		fseek(bitfile, sizeof(char[20]) + sizeof(int[2]), SEEK_SET);
		while(i<num){
			fread(&array[i].brand, (long)sizeof(char[10]), 1, bitfile);
			fseek(bitfile, (long)(sizeof(char[20]) + sizeof(int) + 2L), SEEK_CUR);
			i++;
		}
		for (i=0; i<num; i++){
			printf("%s\n", array[i].brand);
		}		
		
	} if (nbr!=1 && nbr!=2 && nbr!=3) printf ("Error_punkt_3");
	
	fclose(bitfile);
}

/**********************************************************************************************************/

void punkt4(aeroflot *array){
	int num, nbr, i=0;
	FILE *bitfile = fopen("korolev_12_bit.txt", "rb");
	
	fread(&num, sizeof(int), 1, bitfile);
	printf("\nInput number line - ");
	scanf("%d", &nbr);
	if(nbr<=num){
		fseek(bitfile, (nbr-1)* sizeof(aeroflot)/*(sizeof(char[20]) + sizeof(int)+ sizeof(char[10])+2L)*/, SEEK_CUR);
		fread(array, (long)sizeof(aeroflot), 1, bitfile);
		//fread(&array[0].number, (long)sizeof(int), 1, bitfile);
		//fread(&array[0].brand, (long)sizeof(char[10]), 1, bitfile);
		printf("%s\t\t%d\t\t%s\n", ((*(array)).destination),((*(array)).number), ((*(array)).brand));
		exit(1);
		
	} else printf("Error_punkt_4");
	
	fclose(bitfile);
}



































