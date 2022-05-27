#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
	int value;
	struct _node* next;
	struct _node* last;
}Node;
typedef struct _list {
	Node* head;
	Node* tail;
}List;
void add(List* pList, int number) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->value = number;
	p->next = NULL;
	if (pList->head == NULL) {
		pList->head = p;
		pList->tail = p;
		p->last = NULL;
	}
	else {
		p->last = pList->tail;
		(pList->tail)->next = p;
		pList->tail = p;

	}
}

void print(const List * list){
		Node* p;
		for (p = list->head; p; p = p->next) {
			printf("%d ", p->value);
		}
		printf("\n");
}
int delNode(List* list, int number) {
		Node* p, * q;
		int i = 0;
		int res = -1;
		for (p = list->head, q = NULL; p; q = p, p = p->next,i++) {
			
			if (i == number) {
				if (q == NULL) {
					list->head = p->next;
					free(p);
					res = 1;
					break;
				}
				else {
					q->next = p->next;

					if (p->next == NULL) {
						list->tail = q;
					}
					else {
						p->next->last = q;
					}
					free(p);
					res = 1;
					break;
				}
			}

		}
		return res;
	
}
void addIndex(List* list, int index, int number) {
	Node* p = list->head;
	Node * q = (Node*)malloc(sizeof(Node));
	q->value = number;
	for (int i = 0; p; i++, p = p->next) {
		if (i == index) {
			q->next = p;
			q->last = p->last;
			p->last->next = q;
			p->last = q;
			

		}
		if (i+1 == index && !(p->next)) {
			add(list, number);
		}
	}
}
int getValue(const List* list, int index) {
	Node* p = list->head;
	for (int i = 0; p; i++, p = p->next) {
		if (i == index) {
			return p->value;
		}
		
	}
	return -1;
}
int main() {
		List list;
		int number;
		list.head = list.tail = NULL;
		do {
			scanf_s("%d", &number);
			if (number != -1) {
				add(&list, number);
			}
		} while (number != -1);
		printf("链表的值现在为：");
		print(&list);
		printf("删除第六个节点\n");
		delNode(&list, 5);
		printf("链表的值现在为：");
		print(&list);
		printf("在最后添加一个节点，值为1\n");
		add(&list, 1);
		printf("链表的值现在为：");
		print(&list);
		printf("在第三位插入一个节点，值为2\n");
		addIndex(&list, 2, 2);
		printf("链表的值现在为：");
		print(&list);
		printf("找到在第四位上节点的值为\n");
		int a = getValue(&list, 3);
		printf("值为：%d",a);
		//	for(p=list.head;p;p=p->next){
		//		
		//		printf("%d\n",p->value)
		system("pause");
		return 0;
	}
