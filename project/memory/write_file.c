#include <stdio.h>

#define FILE_SIZE 4096*16
int main(int argc, char* argv[]){
	FILE *fp = NULL;
	fp = fopen("disk_file.txt","w+");
	for(int i=0; i<FILE_SIZE; ++i){
		fputc('1', fp);
	}
	fclose(fp);
}
