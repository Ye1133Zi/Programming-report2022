#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_LENGTH  200
#define MAX_LEND 3
//书
typedef struct Book {
	int index;//编号
	char name[MAX_LENGTH];//书名
	int amount;//数量
	int lend;//可借数目
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
		fprintf(outfile, "编号\t书名\t数量\t可借数目\n");
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
		fprintf(outfile, "姓名\t借阅书籍编号\t借阅书籍编号\t借阅书籍编号\n");
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
	fscanf(fp, "%*[^\n]%*c"); // 跳过第一行
	while (fscanf(fp, "%s\t%d\t%d\t%d\n", users[usernumber].name, &users[usernumber].lendIndex[0],
		&users[usernumber].lendIndex[1], &users[usernumber].lendIndex[2]) != EOF) {
		usernumber++;
	}
	fclose(fp);
}
void LoaduserList() {
	FILE* fp;
	fp = fopen("users.txt", "w");
	fprintf(fp, "姓名\t借阅书籍编号\t借阅书籍编号\t借阅书籍编号\n");
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
//将文件读取到数组中
void creat_booklist() {
	FILE* fp;
	fp = fopen("books.txt", "r");
	booknumber = 0;
	fscanf(fp, "%*[^\n]%*c"); // 跳过第一行
	while (fscanf(fp, "%d\t%s\t%d\t%d\n", &booklist[booknumber].index, booklist[booknumber].name,
		&booklist[booknumber].amount, &booklist[booknumber].lend) != EOF) {
		booknumber++;
	}
	fclose(fp);
}
void BorrowIndex(int a,user*A) {
	int le = 0;//判断用户是否可借
	for (int i1 = 0; i1 < MAX_LEND; i1++) {
		if (A->lendIndex[i1] == -1) {
			le = 1;
			break;
		}
	}
	if (le == 0) {
		printf("借阅失败\n");
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
					printf("借阅失败\n");
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
		printf("归还失败\n");
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
					printf("图书不在库中，删除失败\n");
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
//将数组写入文件
void loadBooklist() {
	FILE* fp;
	fp = fopen("books.txt", "w");
	fprintf(fp, "编号\t书名\t数量\t可借数目\n");
	for (int i = 0; i < booknumber; i++) {
		fprintf(fp, "%d\t%s\t%d\t%d\n", booklist[i].index, booklist[i].name, booklist[i].amount, booklist[i].lend);
	}
	fclose(fp);
}
void showBorrow(int index) {
	printf("借走这本书的用户有：\n");
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
	//初始化书库
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
//	//初始化用户
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
	printf("未找到该书编号\n");
	return -1;
}
void printIf(int index) {
	for (int i = 0; i < booknumber; i++) {
		if (index == booklist[i].index) {
			printf("编号\t书名\t数量\t可借数目\n");
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
			int find = 0;//判断是否找到该用户
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
					printf("输入2查询图书编号，输入0，进行图书借阅；输入1进行图书归还，,输入-1退出\n");

					scanf("%d", &mode);
					getchar();
					if (mode == 0) {
						int index;
						printf("请输入借阅的图书编号\n");
						scanf("%d", &index);
						BorrowIndex(index, &users[userIndex]);
						LoaduserList();
					}
					else if (mode == 1) {
						int index;
						printf("请输入归还的图书编号\n");
						scanf("%d", &index);
						ReturnIndex(index, &users[userIndex]);
						LoaduserList();
					}
					else if (mode == 2) {
						char c[MAX_LENGTH];
						printf("请输入借图书的名称\n");
						scanf("%s", &c);
						if (getIndex(c) != -1) {
							printf("图书的编号为：%d\n", getIndex(c));
						}
						
					}
					loadBooklist();
				} while (mode!=-1);
			}
			else {
				printf("输入用户名出错！");
			}
	}
	else if(strcmp(argv1[1], "-u") == 0){
		int mode;
		do {
			printf("输入0，进行新图书数量添加；输入1查询图书信息，输入2进行读者信息录入，输入3进行图书信息修改,输入-1退出\n");
			scanf("%d", &mode);
			if (mode == 0) {
				printf("请输入图书的信息，格式如下：\n编号 书名 数量\n");
				int index;
				int number;
				char c[MAX_LENGTH];
				scanf("%d%s%d", &index, c, &number);
				book_creat(index, c, number);
				creat_booklist();
			}
			else if (mode == 3) {
				printf("请输入你要修改的图书编号\n");
				int index;
				scanf("%d", &index);
				int mode1;
				printf("添加请输入1，删除请输入2\n");
				scanf("%d", &mode1);
				int number;
				if (mode1 == 1) {
					printf("请输入添加的个数\n");
					scanf("%d", &number);
					add(index, number);
					loadBooklist();
				}
				else {
					printf("请输入删除的个数\n");
					scanf("%d", &number);
					del(index, number);
					loadBooklist();
				}

			}
			else if (mode == 1) {
				//BorrowIndex(12, &users[0]);
				printf("请输入图书编号\t");
				int index;
				scanf("%d", &index);
				printf("图书信息为：\n");
				printIf(index);
				showBorrow(index);
				loadBooklist();
			}
			else if (mode == 2) {
				printf("请输入你要添加的读者名：\n");
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
