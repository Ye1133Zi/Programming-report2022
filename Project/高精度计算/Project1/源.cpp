#include <stdio.h>
#include "List.h"
#include <stdlib.h>
#include <string.h>
int main() {
	printf("����һ��ʵ�ָ߾��ȵļӼ����ĳ���\n");
	List a1, a2, b,a3,a4;
	a1 = listCreat();
	a2 = listCreat();
	a3 = listCreat();
	a4 = listCreat();
	b = listCreat();
	int value = 0;

	char c;
	printf("�������һ�����ķ��ţ���Ϊ���������롰+���ͻس�����Ϊ���������롰-���ͻس�,\n");
	c =getchar();
	printf("Ȼ���������һ�����ľ���ֵ����ʽΪ�����Ϊ�����λ��ÿһλ�Կո����������-1ʱ����\n"
	"�����һ����Ϊ5421��������1 2 4 5 -1\n");
	do {
		scanf_s("%d", &value);
		if (value != -1) {
			add(&a1, value);
		}
		
	} while (value != -1);
	if (c == '-') {
		a1.sign = -1;
	}
	printf("������ĵ�һ�����ǣ�\n");
	print(&a1);
	ListCpy(&a1, &a3);
	printf("\n");
	printf("���ڣ�������ڶ������ķ��ţ���Ϊ���������롰+���ͻس�����Ϊ���������롰-���ͻس�,\n");
	getchar();
	c = getchar();
	if (c == '-') {
		a2.sign = -1;
	}
	printf("Ȼ��������ڶ������ľ���ֵ����ʽΪ�����Ϊ�����λ��ÿһλ�Կո����������-1ʱ����\n"
		"�����һ����Ϊ5421��������1 2 4 5 -1\n");
	do {
		scanf_s("%d", &value);
		if (value != -1) {
			add(&a2, value);
		}

	} while (value != -1);
	printf("������ĵڶ������ǣ�\n");
	print(&a2);
	ListCpy(&a2, &a4);
	printf("\n");
	printf("������мӷ����Ǽ�������Ϊ�ӷ������롰+���ͻس�����Ϊ���������롰-���ͻس�\n");
	getchar();
	c = getchar();
	HandleList(a1, a2, c, &b);
	print(&a3);
	printf("%c", c);
	print(&a4);
	printf("�Ľ��Ϊ��");
	print(&b);
//	printf("%d", Listcmp(&a1, &a2));
	system("pause");
	return 0;
}