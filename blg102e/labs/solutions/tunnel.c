#include <stdio.h>

struct box{
	int sides[3];
};

int main(){
	int boxCount;
	scanf("%d", &boxCount);
		for(int i = 0; i < boxCount; i++){
		struct box b;
		
		double volume = 1;
		int appropiateEdgeCount = 0;
		for(int j = 0; j < 3; j++){
			scanf("%d", &b.sides[j]);
			if(b.sides[j] <= 40){
				appropiateEdgeCount++;
			}
			volume *= b.sides[j];
		}
		if(appropiateEdgeCount >= 2){
			printf("%.2f\n", volume);
		}
	}
	return 0;
}