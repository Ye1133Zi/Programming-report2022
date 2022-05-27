#pragma once
typedef struct node {
	int number; //位数
	int value;//数值
	struct node* next;
	struct node* last;
}Node;
typedef struct list {
	int sign = 1;//1表示正数，-1表示负数
	Node* head;//第一位
	Node* tail;//最后一位
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