#include <stdio.h>
#include <math.h>

int main(){

	int numArr[4];
	int num=0;
	scanf("%d", &num);


			for(int i=0 ; i<4;i++){
			numArr[i]=num/pow(10,3-i);
			num = num%(int)(pow(10,3-i));
		}

	for(int i =0; i<4; i++){
		printf("%d-",numArr[i]);
	}
}
