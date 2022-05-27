#include <stdio.h>
#include "List.h"
#include <stdlib.h>
#include <string.h>
int main() {
	printf("这是一个实现高精度的加减法的程序\n");
	List a1, a2, b,a3,a4;
	a1 = listCreat();
	a2 = listCreat();
	a3 = listCreat();
	a4 = listCreat();
	b = listCreat();
	int value = 0;

	char c;
	printf("请输入第一个数的符号，如为正数，输入“+”和回车，如为负数，输入“-”和回车,\n");
	c =getchar();
	printf("然后请输入第一个数的绝对值，格式为从最低为到最高位，每一位以空格相隔，输入-1时结束\n"
	"例如第一个数为5421，则输入1 2 4 5 -1\n");
	do {
		scanf_s("%d", &value);
		if (value != -1) {
			add(&a1, value);
		}
		
	} while (value != -1);
	if (c == '-') {
		a1.sign = -1;
	}
	printf("你输入的第一个数是：\n");
	print(&a1);
	ListCpy(&a1, &a3);
	printf("\n");
	printf("现在，请输入第二个数的符号，如为正数，输入“+”和回车，如为负数，输入“-”和回车,\n");
	getchar();
	c = getchar();
	if (c == '-') {
		a2.sign = -1;
	}
	printf("然后请输入第二个数的绝对值，格式为从最低为到最高位，每一位以空格相隔，输入-1时结束\n"
		"例如第一个数为5421，则输入1 2 4 5 -1\n");
	do {
		scanf_s("%d", &value);
		if (value != -1) {
			add(&a2, value);
		}

	} while (value != -1);
	printf("你输入的第二个数是：\n");
	print(&a2);
	ListCpy(&a2, &a4);
	printf("\n");
	printf("你想进行加法还是减法，如为加法，输入“+”和回车，如为减法，输入“-”和回车\n");
	getchar();
	c = getchar();
	HandleList(a1, a2, c, &b);
	print(&a3);
	printf("%c", c);
	print(&a4);
	printf("的结果为：");
	print(&b);
//	printf("%d", Listcmp(&a1, &a2));
	system("pause");
	return 0;
}