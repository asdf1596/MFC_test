#include<stdio.h>
int main() {
	printf("���� x�� y�� �Է��ϼ���.\n");
	int x, y;
	printf("x : ");
	scanf("%d", &x);
	printf("y : ");
	scanf("%d", &y);
	int sum = x + y;
	printf("%d + %d = %d\n", x, y, sum);
}