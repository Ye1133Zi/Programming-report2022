#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_LENGTH  200
#define MAX_LEND 3
//��
typedef struct Book {
	int index;//���
	char name[MAX_LENGTH];//����
	int amount;//����
	int lend;//�ɽ���Ŀ
} book;
book booklist[100];
int booknumber;
typedef struct admin {
	char name[MAX_LENGTH];
	int lendIndex[MAX_LEND] = { -1,-1,-1 };;
}user;
user users[100];
int usernumber;
void book_creat(int index, char name[], int amount)
{
	FILE* outfile;
	outfile = fopen("books.txt", "a+");
	if (outfile == NULL)
	{
		printf("Can't open the file!\n");
	}
	if (fgetc(outfile) ==EOF) {
		fprintf(outfile, "���\t����\t����\t�ɽ���Ŀ\n");
	}
	fclose(outfile);
	outfile = fopen("books.txt", "a+");
	fprintf(outfile, "%d\t%s\t%d\t%d\n", index, name, amount,amount);
	fclose(outfile);
}
void user_creat(const char name[])
{
	FILE* outfile;
	outfile = fopen("users.txt", "a+");
	if (outfile == NULL)
	{
		printf("Can't open the file!\n");
	}
	if (fgetc(outfile) == EOF) {
		fprintf(outfile, "����\t�����鼮���\t�����鼮���\t�����鼮���\n");
	}
	fclose(outfile);
	outfile = fopen("users.txt", "a+");
	fprintf(outfile, "%s\t%d\t%d\t%d\n", name,-1,-1,-1);
	fclose(outfile);
}
void creat_userslist() {
	FILE* fp;
	fp = fopen("users.txt", "r");
	usernumber = 0;
	fscanf(fp, "%*[^\n]%*c"); // ������һ��
	while (fscanf(fp, "%s\t%d\t%d\t%d\n", users[usernumber].name, &users[usernumber].lendIndex[0],
		&users[usernumber].lendIndex[1], &users[usernumber].lendIndex[2]) != EOF) {
		usernumber++;
	}
	fclose(fp);
}
void LoaduserList() {
	FILE* fp;
	fp = fopen("users.txt", "w");
	fprintf(fp, "����\t�����鼮���\t�����鼮���\t�����鼮���\n");
	for (int i = 0; i < usernumber; i++) {
		fprintf(fp, "%s\t%d\t%d\t%d\n", users[i].name, users[i].lendIndex[0],
			users[i].lendIndex[1], users[i].lendIndex[2]);
	}
	fclose(fp);
}
void printAllbooks() {
	FILE* outfile;
	char buf[MAX_LENGTH];
	int len;
	outfile = fopen("books.txt", "a+");
	while (fgets(buf, 200, outfile) != NULL) {
		len = strlen(buf);
		buf[len - 1] = '\n';
		printf("%s", buf);
	}
	fclose(outfile);
}
//���ļ���ȡ��������
void creat_booklist() {
	FILE* fp;
	fp = fopen("books.txt", "r");
	booknumber = 0;
	fscanf(fp, "%*[^\n]%*c"); // ������һ��
	while (fscanf(fp, "%d\t%s\t%d\t%d\n", &booklist[booknumber].index, booklist[booknumber].name,
		&booklist[booknumber].amount, &booklist[booknumber].lend) != EOF) {
		booknumber++;
	}
	fclose(fp);
}
void BorrowIndex(int a,user*A) {
	int le = 0;//�ж��û��Ƿ�ɽ�
	for (int i1 = 0; i1 < MAX_LEND; i1++) {
		if (A->lendIndex[i1] == -1) {
			le = 1;
			break;
		}
	}
	if (le == 0) {
		printf("����ʧ��\n");
	}
	else {
		for (int i = 0; i < booknumber; i++) {
			if (a == booklist[i].index) {
				if (booklist[i].lend > 0) {
					for (int i1 = 0; i1 < MAX_LEND; i1++) {
						if (A->lendIndex[i1] == -1) {
							A->lendIndex[i1] = a;
							booklist[i].lend--;
							break;
						}
					}
				}
				else {
					printf("����ʧ��\n");
				}

			}
		}
	}	
}
void ReturnIndex(int a,user*A) {
	int re = 0;
	for (int i = 0; i < booknumber; i++) {
		if (a == booklist[i].index) {
			for (int i1 = 0; i1 < MAX_LEND; i1++) {
				if (A->lendIndex[i1] == a) {
					A->lendIndex[i1] = -1;
					booklist[i].lend++;
					re = 1;
					break;
				}
			}
		}
	}
	if (re == 0) {
		printf("�黹ʧ��\n");
	}
}
void del(int index,int number) {
	for (int i = 0; i < booknumber; i++) {
		if (index== booklist[i].index) {
			if (booklist[i].lend >= number) {
				booklist[i].amount-= number;
				booklist[i].lend -= number;
			}
			else {
				if (booklist[i].amount == number) {
					for (int j = i; j < booknumber; j++) {
						booklist[j + 1] = booklist[j];
					}
					booknumber--;
				}
				else {
					printf("ͼ�鲻�ڿ��У�ɾ��ʧ��\n");
				}
			}
		}
	}
}
void add(int index,int number) {
	int find = 0;
	for (int i = 0; i < booknumber; i++) {
		if (index == booklist[i].index) {
			booklist[i].amount += number;
			booklist[i].lend += number;
		}
	}
}
//������д���ļ�
void loadBooklist() {
	FILE* fp;
	fp = fopen("books.txt", "w");
	fprintf(fp, "���\t����\t����\t�ɽ���Ŀ\n");
	for (int i = 0; i < booknumber; i++) {
		fprintf(fp, "%d\t%s\t%d\t%d\n", booklist[i].index, booklist[i].name, booklist[i].amount, booklist[i].lend);
	}
	fclose(fp);
}
void showBorrow(int index) {
	printf("�����Ȿ����û��У�\n");
	for (int i = 0; i < usernumber; i++) {
		for (int j = 0; j < MAX_LEND; j++) {
			if (index == users[i].lendIndex[j]) {
				printf("%s\t", users[i].name);
			}
		}
	}
	printf("\n");
}
void init() {
	//��ʼ�����
	int index = 12;
	char buf[MAX_LENGTH];
	int number = 11;
	char c[100] = "aaaa";
//	book_creat(index, c, number);
//	index++;
//	number--;
//	book_creat(index, c, number);
//	index++;
//	number--;
//	book_creat(index, c, number);
//	index++;
//	number--;
//	book_creat(index, c, number);
//	index++;
//	number--;
//	book_creat(index, c, number);
//	//��ʼ���û�
	creat_booklist();
//	loadBooklist();
//	user_creat("A");
//	user_creat("B");
//	user_creat("C");
	creat_userslist();
//	LoaduserList();

}
void getName(int a) {
	for (int i = 0; i < booknumber; i++) {
		if (a == booklist[i].index) {
			printf("%s", booklist[i].name);
		}
	
	}
}
int getUserName(char c[]) {
	for (int i = 0; i < usernumber; i++) {
		if (strcmp(c,users[i].name)==0) {
			return i;
		}
	}
}
int getIndex(char c[]) {
	for (int i = 0; i < booknumber; i++) {
		if (strcmp(c, booklist[i].name) == 0) {
			return booklist[i].index;
		}

	}
	printf("δ�ҵ�������\n");
	return -1;
}
void printIf(int index) {
	for (int i = 0; i < booknumber; i++) {
		if (index == booklist[i].index) {
			printf("���\t����\t����\t�ɽ���Ŀ\n");
			printf("%d\t%s\t%d\t%d\n", booklist[i].index, booklist[i].name, booklist[i].amount, booklist[i].lend);
		}
	}
}
int main(int argc, char* argv[]) {
	init();
	char argv1[3][MAX_LENGTH];
	if (argc!=3) {
		scanf("%s%s%s", argv1[0],argv1[1], argv1[2]);
	}
	else {
		strcpy(argv1[1], argv[1]);
		strcpy(argv1[2], argv[2]);
		strcpy(argv1[0], argv[0]);
	}
	if (strcmp(argv1[1], "-a") == 0) {
			int find = 0;//�ж��Ƿ��ҵ����û�
			int userIndex;
			for (int i = 0; i <usernumber; i++) {
				if (strcmp(argv1[2], users[i].name) == 0) {
					find = 1;
					break;
				}
			}
			if (find == 1) {

				userIndex = getUserName(argv1[2]);
				int mode;
				do {
					printf("����2��ѯͼ���ţ�����0������ͼ����ģ�����1����ͼ��黹��,����-1�˳�\n");

					scanf("%d", &mode);
					getchar();
					if (mode == 0) {
						int index;
						printf("��������ĵ�ͼ����\n");
						scanf("%d", &index);
						BorrowIndex(index, &users[userIndex]);
						LoaduserList();
					}
					else if (mode == 1) {
						int index;
						printf("������黹��ͼ����\n");
						scanf("%d", &index);
						ReturnIndex(index, &users[userIndex]);
						LoaduserList();
					}
					else if (mode == 2) {
						char c[MAX_LENGTH];
						printf("�������ͼ�������\n");
						scanf("%s", &c);
						if (getIndex(c) != -1) {
							printf("ͼ��ı��Ϊ��%d\n", getIndex(c));
						}
						
					}
					loadBooklist();
				} while (mode!=-1);
			}
			else {
				printf("�����û�������");
			}
	}
	else if(strcmp(argv1[1], "-u") == 0){
		int mode;
		do {
			printf("����0��������ͼ��������ӣ�����1��ѯͼ����Ϣ������2���ж�����Ϣ¼�룬����3����ͼ����Ϣ�޸�,����-1�˳�\n");
			scanf("%d", &mode);
			if (mode == 0) {
				printf("������ͼ�����Ϣ����ʽ���£�\n��� ���� ����\n");
				int index;
				int number;
				char c[MAX_LENGTH];
				scanf("%d%s%d", &index, c, &number);
				book_creat(index, c, number);
				creat_booklist();
			}
			else if (mode == 3) {
				printf("��������Ҫ�޸ĵ�ͼ����\n");
				int index;
				scanf("%d", &index);
				int mode1;
				printf("���������1��ɾ��������2\n");
				scanf("%d", &mode1);
				int number;
				if (mode1 == 1) {
					printf("��������ӵĸ���\n");
					scanf("%d", &number);
					add(index, number);
					loadBooklist();
				}
				else {
					printf("������ɾ���ĸ���\n");
					scanf("%d", &number);
					del(index, number);
					loadBooklist();
				}

			}
			else if (mode == 1) {
				//BorrowIndex(12, &users[0]);
				printf("������ͼ����\t");
				int index;
				scanf("%d", &index);
				printf("ͼ����ϢΪ��\n");
				printIf(index);
				showBorrow(index);
				loadBooklist();
			}
			else if (mode == 2) {
				printf("��������Ҫ��ӵĶ�������\n");
				char c[MAX_LENGTH];
				creat_userslist();
				scanf("%s", &c);
				strcpy(users[usernumber].name, c);
				usernumber++;
				LoaduserList();
			}
		} while (mode != -1);
	}

//	BorrowIndex(12, &users[0]);
//	showBorrow(12);
	
//	printAllbooks();
//	do {
//		scanf_s("%d %d", &index, &number);
 //   	if (index != -1) {
//		book_creat(index, c, number);
//		}
//	} while (index != -1);
	//creat_booklist();
//	book_creat(index, c, number);
//	book_creat(index, c, number);
//	creat_booklist();
//	BorrowIndex(12,&A);
//	for (int i = 0; i < 12; i++) {
//		del(12);
//	}
//	Returnindex(12,&A);
//	del(12);
	loadBooklist();

	return 0;
}
