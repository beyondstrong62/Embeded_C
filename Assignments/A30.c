// Program to print all the factors of a number 
#include <stdio.h>

int main(){
	
	int n =15, fact=1;
	
	printf("Factors of %d: ",n);
	while(fact<=n/2){
		
		if(n%fact==0){
			
			printf("%d, ", fact);
		}
		
		fact++;
	}
	printf("%d", n);
	
	return 0;
}
