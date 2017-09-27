#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char** argv){

	char* word = "";

	if(argc >= 3){
		word = argv[1];
	}
	else if(argc == 2){
		printf("ERROR: no files\n");
		return 0;
	}
	else {
		printf("ERROR: no word\n");
		return 0;
	} 
	//printf("word: %s\n", word);

	unsigned int fcount = argc - 2;
	char* fnames[fcount];
	unsigned int wcounts[fcount];
	for(unsigned int i = 0; i < fcount; i++){
		fnames[i] = argv[i + 2];
		//printf("file %d: %s\n", i + 1, fnames[i]);
		wcounts[i] = 0;
	}

	for(unsigned int i = 0; i < fcount; i++){
		FILE *f = fopen(fnames[i],"r");
		if(!f){
			//f==NULL	
			printf("ERROR: %s is not file!\n",fnames[i]);
			return 0;
		}
		
		char ch[1] = "";
		unsigned int n = 0;
		int x = fread(ch, 1, sizeof(char), f);
		if(x <= 0) break;
		while((isspace(ch[0]) != 0) || (ispunct(ch[0]) != 0)){
			x = fread(ch, 1, sizeof(char), f);
			if(x <= 0) break;
		}				
		while(x > 0){
			n = 0;
			while(ch[0] == word[n]){
				n++;
				x = fread(ch, 1, sizeof(char), f);
				if((((x > 0) && 
				   ((isspace(ch[0]) != 0) || (ispunct(ch[0]) != 0))) 
				   || (x <= 0)) &&
				   (word[n] == '\0')){
					wcounts[i]++;
				}
			}
			
			while((isspace(ch[0]) == 0) && (ispunct(ch[0]) == 0) && (x > 0)){
				x = fread(ch, 1, sizeof(char), f);
				//printf("1\n");
			}
			x = fread(ch, 1, sizeof(char), f);
		}
	
		fclose(f);
	}

	float a_avrg = 0.0;
	for(unsigned int i = 0; i < fcount; i++) a_avrg = a_avrg + wcounts[i];
	a_avrg = a_avrg / fcount;

	float D = 0.0;
	for(unsigned int i = 0; i < fcount; i++) D = D + 
											(wcounts[i] - a_avrg)*(wcounts[i] - a_avrg);
	if(fcount  == 1) printf("D undefined\n");
	else {
		D = sqrt(D/(fcount-1));
		printf("D = %f\n", D);
	}
	return 0;
}
