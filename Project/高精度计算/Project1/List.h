#pragma once
typedef struct node {
	int number; //λ��
	int value;//��ֵ
	struct node* next;
	struct node* last;
}Node;
typedef struct list {
	int sign = 1;//1��ʾ������-1��ʾ����
	Node* head;//��һλ
	Node* tail;//���һλ
}List;
List listCreat();
int Listcmp(List* list1, List* list2);
void add(List* plist, int number);
void print(const List* list);
void delNode(List* list, int number);
void ListAdd(List list1, List list2, List* res);
void ListSub(List list1, List list2, List* res);
void HandleList(List list1, List list2, char s, List* res);
void ListCpy(List* list1, List* list2);