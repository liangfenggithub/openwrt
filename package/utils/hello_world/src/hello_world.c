#include <stdio.h>
#include<unistd.h>
int main(char argc, char *argv[])
{
	int i = 1;
	while(1){		
		printf("Hello world!!!%d\n",i);
		
		if (i < 10){
			i++;
		}else{
			i = 1;	
		}
		
		sleep(1);
	}
	return  0;
}