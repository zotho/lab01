#include <stdio.h>

int main(int argc, char** argv){
	for(int i=0; i<argc; i++){
		printf("%s\n",argv[i]);
	}
	int i;
	scanf("%d",&i);
	printf("a is %d\n",i);
	return 0;
}
