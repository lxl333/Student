#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>

#define LEN sizeof(struct  student)
#define FORMAT "%-8d%-15s%-12.11f%-12.11f%-12,11f%-12.11f\n"
#define DATA stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum
#define file "data.txt"

struct student /*define struct of students' grade*/
{
	int num;/*number*/
	char name[15];/*name*/
	double elec;/*elective*/
	double expe;/*experiment*/
	double requ;/*required*/
	double sum;/*sum grade*/
};

struct student stu[50];/*define struct array*/
void in();/*input students'grade's informations*/
void show();/*show students'informations*/
void order();/*paixu*/
void del();/*delete students'grade'sinformations*/
void modify();/*modify record*/
void menu();/*menu*/
void insert();/*insert record*/
void total();/*sum total*/
void search();/*search record */

int main()/*main function*/
{
	int n;
	menu();
	scanf("%d", &n);/*input fun's num*/
	while (n) {
		switch (n) {
		case 1:
			in();
			break;
		case 2:
			search();
			break;
		case 3:
			del();
			break;
		case 4:
			modify();
			break;
		case 5:
			insert();
			break;
		case 6:
			order();
			break;
		case 7:
			total();
			break;
		case 8:
			show();
			break;
		default:
			break;
		}
		getch();
		menu();/*run out the fun,then show the menu again*/
		scanf("%d", &n);
	}
	return 0;
}

void in()/*input record*/
{
	int i, m = 0;/*m is record the num*/
	char ch[2];
	FILE *fp;/*define the file pointer*/
	if ((fp = fopen(file, "a+")) == NULL)/*open the file*/
	{
		printf("can not open.\n");
		return;
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;/* records'sum*/
	}
	fclose(fp);
	if (m == 0)
		printf("NO record!\n");
	else {
		system("cls");
		show();/*use function show,show the old record*/
	}
	if ((fp = fopen(file, "wb")) == NULL) {
		printf("can not open\n");
		return;
	}
	for (i = 0; i < m; i++)
		fwrite(&stu[i], LEN, 1, fp);/*write the record in the file*/
	printf("please input (Y/N):");
	scanf("%s", ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)/*whether input new record*/
	{
		printf("number:");
		scanf("%d", &stu[m].num);/*input student' number*/
		for (i = 0; i < m; i++)
			if (stu[i].num == stu[m].num) {
				printf("the number is existing ,press any to continue!");
				getch();
				fclose(fp);
				return;
			}
		printf("name:");
		scanf("%s", stu[m].name);/*input student's name*/
		printf("elective:");
		scanf("%lf", stu[m].elec);/*input student's elective subject*/
		printf("experiment:");
		scanf("%lf", stu[m].expe);/*input student's experiment */
		printf("required course:");
		scanf("%lf", stu[m].requ);/*input student's required course*/
		stu[m].sum = stu[m].elec + stu[m].expe + stu[m].requ;/*compute the sum*/
		if (fwrite(&stu[m], LEN, 1, fp) != 1)/*put the new record into the file*/
		{
			printf("can not save!");
			getch();
		} else {
			printf("%s  saved!\n", stu[m].name);
			m++;
		}
		printf("continue ?(Y/N)");/*if continue*/
		scanf("%s", ch);
	}
	fclose(fp);
	printf("OK!\n");
}

void show() {
	FILE * fp;
	int i, m = 0;
	fp = fopen(file, "rb");
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	fclose(fp);
	printf("number  name        elective     experiment  required   sum\t\n");
	for (i = 0; i < m; i++) {
		printf(FORMAT, DATA);/*将信息按指定格式打印*/
	}
}

void menu()/*define function  achieve the menu's function*/
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|--------------------STUDENT---------------|-------------|\n");
	printf("\t\t|\t0.exit                             |             |\n");
	printf("\t\t|\t1.input record                     |             |\n");
	printf("\t\t|\t2.search record                    |  made       |\n");
	printf("\t\t|\t3.delete record                    |    in       |\n");
	printf("\t\t|\t4.modity record                    |  jian       |\n");
	printf("\t\t|\t5.insert record                    |  dong       |\n");
	printf("\t\t|\t6.order                            |             |\n");
	printf("\t\t|\t7.number                           |             |\n");
	printf("\t\t|\t8.show                             |             |\n");
	printf(
			"\t\t|------------------------------------------|-------------|\n\n");
	printf("\t\t\tchoose(0-8):");
}

void order()/*排序函数*/
{
	FILE *fp;
	struct student t;
	int i = 0, j = 0, m = 0;
	if ((fp = fopen(file, "r+")) == NULL) {
		printf("can not open!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	fclose(fp);
	if (m == 0) {
		printf("no record!\n");
		return;
	}
	if ((fp = fopen(file, "wb")) == NULL) {
		printf("can not open\n");
		return;
	}
	for (i = 0; i < m - 1; i++)
		for (j = i + i; j < m; j++)/*成绩顺序交换*/
			if (stu[i].sum < stu[j].sum) {
				t = stu[i];
				stu[i] = stu[j];
				stu[j] = t;
			}
	if ((fp = fopen(file, "wb")) == NULL) {
		printf("can not open\n");
		return;
	}
	for (i = 0; i < m; i++)/*输入重排内容*/
		if (fwrite(&stu[i], LEN, 1, fp) != 1) {
			printf("%s can not save !\n");
			getch();
		}
	fclose(fp);
	printf("save successfully\n");
}

void del()/*delete function*/
{
	FILE *fp;
	int snum, i, j, m = 0;
	char ch[2];
	if ((fp = fopen(file, "r+")) == NULL) {
		printf("can not open\n");
		return;
	}

	while (!feof(fp))
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	fclose(fp);
	if (m == 0) {
		printf("no record !\n");
		return;
	}
	printf("please input the number :");
	scanf("%d", &snum);
	for (i = 0; i < m; i++)
		if (snum == stu[i].num)
			break;
	printf("find the student ,delete?(Y/N)");
	scanf("%s", ch);
	if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)/*if go to delete*/
		for (j = i; j < m; j++)
			stu[j] = stu[j + 1];/*transform  records*/
	m--;/*record 自减*/
	if ((fp = fopen(file, "wb")) == NULL) {
		printf("can not open \n");
		return;
	}
	for (j = 0; j < m; j++)/*write to the file again*/
		if (fwrite(&stu[j], LEN, 1, fp) != 1) {
			printf("can nor save!\n");
			getch();
		}
	fclose(fp);
	printf("delete successfully!\n");
}

void search()/*search function*/
{
	FILE *fp;
	int snum, i, m = 0;
	char ch[2];
	if ((fp = fopen(file, "rb")) == NULL) {
		printf("can not open\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	fclose(fp);
	if (m == 0) {
		printf("no record!\n");
		return;
	}
	printf("please input the number:");
	scanf("%d", &snum);
	for (i = 0; i < m; i++)
		if (snum == stu[i].num)/*check if the input number exist*/
		{
			printf("find the student ,show?(Y/N)");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
				printf(
						"number  name       elective   experiment  required   sum\t\n");
				printf(FORMAT, DATA);/* IN SOME WAY OUT THE RESURT*/
				break;
			}
		}
	if (i == m)
		printf("can not find the student !\n");
}

void modify() {
	FILE *fp;
	int i, j, m = 0, snum;
	if ((fp = fopen(file, "r+")) == NULL) {
		printf("can not open\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	if (m == 0) {
		printf("no record!\n");
		fclose(fp);
		return;
	}
	show();
	printf(
			"please input the number of the student which do you want to modify!\n");
	printf("modify number:");
	scanf("%d", &snum);
	for (i = 0; i < m; i++)
		if (snum == stu[i].num)/*if having change*/
			break;
	printf("find the student !you can modify!\n");
	printf("name:");
	scanf("%s", stu[i].name);
	printf("elective:");
	scanf("%lf", &stu[i].elec);
	printf("experiment:");
	scanf("%lf", &stu[i].expe);
	printf("required course:");
	scanf("%lf", &stu[i].requ);
	printf("modify successfully!");
	stu[i].sum = stu[i].elec + stu[i].expe + stu[i].requ;
	if ((fp = fopen(file, "wb")) == NULL) {
		printf("can not open\n");
		return;
	}
	for (j = 0; j < m; j++)
		if (fwrite(&stu[j], LEN, 1, fp) != 1) {
			printf("can not save!\n");
			getch();
		}
	fclose(fp);
}

void insert() {
	FILE *fp;
	int i, j, k, m = 0, snum;
	if ((fp = fopen(file, "r+")) == NULL) {
		printf("can not open\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	if (m == 0) {
		printf("no record!\n");
		fclose(fp);
		return;
	}
	printf(
			"please input position where do you want to insert!(intput the number)\n");
	scanf("%d", &snum);
	for (i = 0; i < m; i++) {
		if (snum == stu[i].num)
			break;
	}
	for (j = m - 1; j > i; j--) {
		stu[j + 1] = stu[j];
	}
	printf("now please input the new information.\n");
	printf("number:");
	scanf("%d", &stu[i + 1].num);
	for (k = 0; k < m; k++) {
		if (stu[k].num == stu[m].num) {
			printf("the number is existing ,press any to continue!");
			getch();
			fclose(fp);
			return;
		}
	}
	printf("name :");
	scanf("%s", stu[i + 1].name);
	printf("elective:");
	scanf("%lf", stu[i + 1].elec);
	printf("experiment:");
	scanf("%lf", stu[i + 1].expe);
	printf("required course:");
	scanf("%lf", stu[i + 1].requ);
	stu[i + 1].sum = stu[i + 1].elec + stu[i + 1].expe + stu[i + 1].requ;
	if ((fp = fopen(file, "wb")) == NULL) {
		printf("can not open\n");
		return;
	}
	for (k = 0; k <= m; k++) {
		if (fwrite(&stu[k], LEN, 1, fp) != 1) {
			printf("can not save!\n");
			getch();
		}
	}
	fclose(fp);
}

void total() {
	FILE *fp;
	int m = 0;
	if ((fp = fopen(file, "r+")) == NULL) {
		printf("can nnot open\n");
		return;
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	if (m == 0) {
		printf("no record!\n");
		fclose(fp);
		return;
	}
	printf("the class are %d students!\n", m);
	fclose(fp);
}
