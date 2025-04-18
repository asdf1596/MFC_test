#include<stdio.h>
int main() {
	printf("정수 x와 y를 입력하세요.\n");
	int x, y;
	printf("x : ");
	scanf("%d", &x);
	printf("y : ");
	scanf("%d", &y);
	int sum = x + y;
	printf("%d + %d = %d\n", x, y, sum);
}