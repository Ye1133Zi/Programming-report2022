#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <string.h>
/// <summary>
/// 这是一个链表，每一个节点用于储存高精度的一位上的数字
/// </summary>
/// <param name="plist"></param>
/// <param name="number"></param>
/// 
//创建链表
List listCreat() {
	List list;
	list.head = NULL;
	list.tail = NULL;
	return list;
}
//添加节点
void add(List* plist, int number) {
	Node* p = (Node*)malloc(sizeof
	(Node));
	p->value = number;
	p->next = NULL;
	if (plist->head == NULL) {
		p->number = 1;
		p->last = NULL;
		plist->head = p;
		plist->tail = p;
	}
	else {
		p->number = (plist->tail)->number + 1;
		(plist->tail)->next = p;
		p->last = plist->tail;
		plist->tail = p;
		

	}
}
//输出
void print(const List* list) {
	Node* p;
		
	if (list->sign == -1) {
		printf("(-");
	}
	for (p = list->tail; p; p = p->last) {
		printf("%d", p->value);
	}
	if (list->sign == -1) {
		printf("）");
	}
}
//删除
void delNode(List* list, int number) {
	Node* p, * q;

	for (p = list->head, q = NULL; p; q = p, p = p->next) {
		if (p->number == number) {
			if (q == NULL) {
				list->head = p->next;
				free(p);
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
				break;
			}
			if (q) {
				for (q = q->next; q; q = q->next) {
					q->number--;
				}
			}
		}
		

	}
}
//得到某个位数的值
int getValue(List* list, int index) {
	Node* p;
	for (p = list->head; p; p = p->next) {
		if (p->number == index) {
			return p->value;
		}
	}
}
//比较第一个数与第二个数
int Listcmp(List *list1,List*list2){
	if (list1->tail->number != list2->tail->number) {
		if (list1->tail->number > list2->tail->number) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else {

		for(int i=list1->tail->number;i>0;i--){
			if (getValue(list1, i) > getValue(list2, i)) {
				return 1;
			}
			else if(getValue(list1, i) < getValue(list2, i)) {
				return 2;
			}
			else {
				if (i == 1) {
					return 3;
				}
			}
		
		}
	}

}

//改变某个位数的值
void ChangeNodeValue(List * list,int index,int value) {
	Node* p;
	for (p = list->head; p; p = p->next) {
		if (p->number == index) {
			p->value = value;
		}
	}
}
//进位
void ListPlus1(List* list, int index){
	Node* p;
	for (p = list->head; p; p = p->next) {
		if (p->number == index) {
			p->value++;
		}
	}
}
//退位
void ListSub1(List* list, int index) {
	Node* p;
	for (p = list->head; p; p = p->next) {
		if (p->number == index) {
			p->value--;
		}
	}
}
//加法实现
void ListAdd(List list1, List list2,List*res) {
	int min = list1.tail->number;
	int max = list2.tail->number;
	int mx = 2;
	if (list1.tail->number > list2.tail->number) {
		min = list2.tail->number;
		max = list1.tail->number;
		mx = 1;
	}
	int i = 1;
	node* p1;
	node* p2;
	node p3;
	p1 = list1.head;
	p2 = list2.head;
	int ca = 0;//判断进位
	for (i; i <= min; i++) {
		if (ca == 1) {
			ListPlus1(&list2, i);
			ca = 0;
		}
		if (p1->value + p2->value < 10) {
			add(res, p1->value + p2->value );
		}
		else {
			ca = 1;
			add(res, p1->value + p2->value - 10);
			if (i == min&&min!=max) {
				if (mx == 1) {
					ListPlus1(&list1, min + 1);
				}
				else {
					ListPlus1(&list2, min + 1);
				}
			}
			
		}
		p1 = p1->next;
		p2 = p2->next;
	}
	for (int i = min+1; i <= max; i++) {
		if (mx == 1) {
			add(res, getValue(&list1, i));
			if (getValue(res, i) >= 10) {
				ChangeNodeValue(res, i, getValue(res, i) - 10);
				if (i != max) {
					ListPlus1(&list1, i + 1);
				}
				else {
					add(res, 1);
				}
			}
		}
		else {
			add(res, getValue(&list2, i));
			if (getValue(res, i) >= 10) {
				ChangeNodeValue(res, i, getValue(res, i) - 10);
				if (i != max) {
					ListPlus1(&list2, i + 1);
				}
				else {
					add(res, 1);
				}
				
			}
		}
	
	}
}
//减法实现
void ListSub(List list1, List list2, List* res) {
	int min = list1.tail->number;
	int max = list2.tail->number;
	int mx = 2;
	if (list1.tail->number > list2.tail->number) {
		min = list2.tail->number;
		max = list1.tail->number;
		mx = 1;
	}
	int i = 1;
	node* p1;
	node* p2;
	p1 = list1.head;
	p2 = list2.head;
	if (Listcmp(&list1,&list2) == 1) {
		for (i; i <= min; i++) {
			if (p1->value - p2->value >= 0) {
				add(res, p1->value - p2->value);
			}
			else {
				add(res, p1->value - p2->value + 10);
				ListSub1(&list1, i + 1);
				
			}
			p1 = p1->next;
			p2 = p2->next;
		}

	}
	else if(Listcmp(&list1, &list2) == 3) {
		if (res->tail) {
			for (i = res->tail->number; i > 0; i--) {
				delNode(res, i);
			}
		}
		
		add(res, 0);

	}
	else {
		for (i; i <= min; i++) {
			if (p2->value - p1->value >= 0) {
				add(res, p2->value - p1->value);
			}
			else {
				add(res, p2->value - p1->value + 10);
				ListSub1(&list2, i + 1);

			}
			p1 = p1->next;
			p2 = p2->next;
		}
		res->sign = -1;
	}
	for (int i = min + 1; i <= max; i++) {
		if (mx == 1) {
			add(res, getValue(&list1, i));
			if (getValue(res, i) >= 10) {
				ChangeNodeValue(res, i, getValue(res, i) - 10);
				if (i != max) {
					ListPlus1(&list1, i + 1);
				}
				else {
					add(res, 1);
				}
			}
		}
		else {
			add(res, getValue(&list2, i));
			if (getValue(res, i) >= 10) {
				ChangeNodeValue(res, i, getValue(res, i) - 10);
				if (i != max) {
					ListPlus1(&list2, i + 1);
				}
				else {
					add(res, 1);
				}

			}
		}
	}

	for (Node* p = res->head; p; p = p->next) {
		if (p->value < 0) {
			ListSub1(res, p->number+1);
			p->value += 10;
		}
	}
	int con = 1;
	Node* p = res->tail;
	while (con==1) {
		if (p->value == 0) {
			p = p->last;
			delNode(res, p->next->number);
			con = 1;
		}
		else {
			con = 0;
		}
		
	}


}
void HandleList(List list1, List list2, char s, List* res) {
	if (list1.sign==1)
	{
		if (list2.sign == 1&&s == '+') {
			ListAdd(list1, list2, res);
		}
		else if(list2.sign == 1 && s == '-'){
			ListSub(list1, list2, res);
		}
		else if (list2.sign == -1 && s == '+') {
			ListSub(list1, list2, res);
		}
		else {
			ListAdd(list1, list2, res);
		}
	}
	else {
		if (list2.sign == -1 && s == '+') {
			ListAdd(list1, list2, res);
		}
		else if (list2.sign == -1 && s == '-') {
			ListSub(list1, list2, res);
			if (Listcmp(&list1,&list2) == 2) {
				res->sign = 1;
			}
			else {
				res->sign = -1;
			}
			
		}
		else if (list2.sign == -1 && s == '+') {
			ListAdd(list1, list2, res);
			res->sign = 1;
		}
		else {
			ListSub(list1, list2, res);
			if (Listcmp(&list1, &list2) == 2) {
				res->sign = -1;
			}
			else {
				res->sign = -1;
			}
		}
	}
}
//由于node的节点存在指针，直接写list1 = list2,会导致list1随list2变化，所以写一个copy函数
void ListCpy(List* list1, List* list2) {
	if (list2->tail) {
		for (int i = 1; i <= list2->tail->number; i++) {
			delNode(list2, i);
		}
	}
	for (int i = 1; i <= list1->tail->number; i++) {
		add(list2, getValue(list1, i));
	}
	list2->sign = list1->sign;
}