#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>

#include "hmylib.h"
#include "struct.h"


int incorrectInput(int input){
	if (input==1||input==2||input==3) return 0;
	else return 1;
}
void firstInterface(){
	
	printf("\n====================");
	printf("\n|1:student entrance|");
	printf("\n|2:staff entrance  |");
	printf("\n|3:log out         |");
	printf("\n====================");
	printf("\nplease enter the number to make your choice:");
	int choice;
	scanf("%d",&choice);
	while(incorrectInput(choice)){
		printf("wrong input! please enter 1 to 3 to make your choice again:\n");
		scanf("%d",&choice);
	}
	
	if(choice==1){
		stuEntrance();
	}
	if(choice==2){
		staffEntrance();
	}
	if(choice==3){
		system("cls");
		printf("Have a good day! Bye!\n");
		return;
	}	
}
void stuEntrance(){
	system("cls");
	printf("\n===================================");
	printf("\n|1:Log in with an existing account|");
	printf("\n|2:Sign up for a new account      |");
	printf("\n|3:Return to the home page        |");
	printf("\n===================================");
	int choice;
	printf("\nPlease make your choice:");
	scanf("%d",&choice);
	
	while(incorrectInput(choice)){
		printf("\nwrong input! please enter 1 to 3 to make your choice again:");
		scanf("%d",&choice);
	}
	
	if(choice==1){
		stuLogin();
	}
	if(choice==2){
		stuRegister();
	}
	if(choice==3){
		system("cls");
		firstInterface();
	}	
}
void stuLogin(){
	system("cls");
	FILE *fp;
	printf("\nPlease enter your student ID:");
	char stuNum[100];
	scanf("%s",stuNum);
	struct stu *p;
	p=stuhead;
	while( p!=NULL){
		if(strcmp(p->stuNum,stuNum)==0){
			printf("\nRegistered student ID,please enter your password:");
			char password[999];
			scanf("%s",password);
			int chance=0;
			while(strcmp(p->password,password)!=0&&chance<3){
				printf("Wrong password,please enter again:\n(you have at most three chances to reenter your password)");
				scanf("%s",password);
				chance++;
			}
			if(strcmp(p->password,password)!=0&&chance>=3){
				printf("Suspect operation, you are forced to return home page... ");
				system("cls");
				Sleep(3000);
				firstInterface();
				return;
			}
			else if(strcmp(p->password,password)==0){
				printf("Welcome!\n");
				stuOperation(p);
				return;
			}
		}
		p=p->next;
		
	}
	printf("\nStudent id not registered or entered incorrectly!");
	printf("\n.......return to the home page.......");
	Sleep(3000);
	system("cls");
	firstInterface();
	
	
}

void stuRegister(){
	system("cls");
	FILE *fp;
	struct stu *p;
	char stuNum[100];
	char password[9999];
	if (stucount == 0){
		printf("\nplease enter your student ID: ");
		scanf("%s",stuNum);
		while (strlen(stuNum)>20){
			printf("Sorry,student ID too long, please reenter:\n");
			scanf("%s",stuNum);
		}
		strcpy(stuhead->stuNum,stuNum);
		printf("Valid student ID, please enter your password: \n");
		scanf("%s",password);
		while (strlen(password)>16){
			printf("\nSorry,password too long, please reenter:");
			scanf("%s",password);
		}
		strcpy(stuhead->password, password);
		stuhead->bookcount=0;
		stuend = stuhead;
		stuend->next = NULL;
	}
	else{
		p = (struct stu *)malloc(sizeof(struct stu));
		printf("\nplease enter your student ID: ");
		scanf("%s",stuNum);
		while(stuExist(stuNum)||strlen(stuNum)>20){
			if(stuExist(stuNum)){
				printf("\nSorry, the student ID was registered already");
				printf("\nPlease reenter:");
			}
			else{
				printf("\nSorry,student ID too long, please reenter:");
			}
			scanf("%s",stuNum);
		}
		strcpy(stuhead->stuNum,stuNum);
		printf("\nValid student ID, please enter your password: ");
		scanf("%s",password);
		while (strlen(password)>16){
			printf("\nSorry,password too long, please reenter:");
			scanf("%s",password);
		}
		strcpy(stuhead->password, password);
		stuhead->bookcount=0;
		stuend = stuhead;
		stuend->next = NULL;
	}
	stucount++;
	fp = fopen("students", "w");
	p = stuhead;
	while (p!= NULL){
		fwrite(p, sizeof(struct stu), 1, fp);
		p = p->next;
	}
	fclose(fp);
	system("cls");
	printf("\n===================================================");
	printf("\n|Congratulations! you are registered successfully!|");
	printf("\n===================================================");
	printf("\n.......return to the home page.......\n");
	Sleep(3000);
	firstInterface();
}


void stuOperation(struct stu *p){
	printf("\n==================");
	printf("\n|1:borrow book...|");
	printf("\n|2:return book...|");
	printf("\n|3:log out...    |");
	printf("\n==================");
	int choice;
	scanf("%d",&choice);
	while(incorrectInput(choice)){
		printf("\nwrong input! please enter 1 to 3 to make your choice again:");
		scanf("%d",&choice);
	}
	if(choice==1){
		borrow(p);
		
	}
	if(choice==2){
		returnbook(p);
	}
	if(choice==3){
		system("cls");
		firstInterface();
	}
	
}

void borrow(struct stu *sp){
	system("cls");
	struct book *bp;
	char bookname[99];
	int exist = 0;
	bp = bookhead;
	int i=0;
	printf("\nplease enter the book name which you want to borrow:");
	scanf("%s",bookname);
	while (bp != NULL){
		if (strcmp(bookname, bp->nameOfBook) == 0){
			if (bp->quantity == 0){
				printf("sorry, no this book left...");
				break;
			}
			else{
				bp->quantity -= 1;
				sp->bookcount++;
				strcpy(sp->borrowedBook[sp->bookcount], bp->nameOfBook);
				writeStudents();
				writeBooks();
				exist = 1;
				break;
			}
		}
		bp = bp->next;

	}
	if (exist == 0){
		printf("\n---------no such books----------");
	}
	else{
		system("cls");
		printf("\n borrow %s successfully!!", bp->nameOfBook);
		printf(".......return to the home page.......");
	}
	Sleep(3000);
	firstInterface();
}
	
void returnbook(struct stu *sp){
	system("cls");
	if (sp->bookcount==0){
		printf("you have not borrowed any book...");
		Sleep(2000);
		firstInterface();
	}
		
	else{
	struct book *bp;
	char bookname[100];
	int count = sp->bookcount;
	int exist;
	int flag;
	bp = bookhead;
	int i;
	printf("\nThe books you have borrowed:\n");
	for(i=0;i<sp->bookcount;i++){
		printf("\n%d:%s", i+1,sp->borrowedBook[i]);
	}
	printf("\n=======================================================");
	printf("\nPlease enter number to choose which you want to return:");
	while(!scanf("%d",flag)||(flag<0||flag>count)){
		printf("\nWrong input, please enter again:");
	}
	while (bp != NULL){
		if (strcmp(bp->nameOfBook, sp->borrowedBook[flag-1]) == 0){
			bp->quantity++;
			break;
		}
		bp = bp->next;
	}
	if(bp==NULL&&strcmp(bp->nameOfBook, sp->borrowedBook[flag-1]) != 0){
		
		printf("\n=========================================================================");
		printf("\n|        The book can not be found from library                         |");
		printf("\n|(deleted or you did not borrow this book from here, you can keep that!)|");
		printf("\n=========================================================================");
		printf(".......return to the home page.......\n");
		Sleep(3000);
		system("cls");
		firstInterface();
	}
	for ( i= flag-1; i < sp->bookcount; i++){
		strcpy(sp->borrowedBook[i], sp->borrowedBook[i + 1]);
	}
	sp->bookcount--;
	writeStudents();
	writeBooks();
	printf("\n--------Returned successfully!!---------");
	printf("\n.......return to the home page.......\n");
	Sleep(3000);
	firstInterface();}
}
void staffEntrance()
{
	system("cls");
	printf("\n======================================");
	printf("\n|1:Log in with an existing account   |");
	printf("\n|2:Sign up for a new account         |");
	printf("\n|3:Return to the home page           |");
	printf("\n======================================");
	int choice;
	printf("\nmake your choice:");
	scanf("%d",&choice);
	while(incorrectInput(choice)){
		printf("\nwrong input! please enter 1 to 3 to make your choice again:");
		scanf("%d",&choice);
	}
	
	if(choice==1){
		adminLogin();
	}
	if(choice==2){
		adminRegister();
	}
	if(choice==3){
		system("cls");
		firstInterface();
	}

}
void adminLogin(){
	system("cls");
	struct pw *p;
	char adminname[100];
	p = adminhead;
	printf("\nPassword:");
	scanf("%s",adminname);
	while (p != NULL)
	{

		if (strcmp(p->administratorPassword, adminname) == 0)

		{
			system("cls");
			printf("\nwelcome!");
			Sleep(2000);
			staffFunction();
			return;
		}
		p = p->next;
	}
	printf("\n-----------Wrong password----------");
	printf("\n------Return to the home page------");
	Sleep(2000);
	firstInterface();
}
void adminRegister(){
	system("cls");
	FILE *fp;
	struct pw *p;
	char *password;
	if (admincount == 0){
		
		printf("\nplease enter your password: ");
		scanf("%s",password);
		while (strlen(password)>20){
			printf("\nSorry,password too long, please reenter:");
			scanf("%s",password);
		}
		strcpy(adminhead->administratorPassword, password);
		adminend = adminhead;
		adminend->next = NULL;
	}
	else{
		p = (struct pw *)malloc(sizeof(struct pw));
		printf("\nplease enter your password: ");
		scanf("%s",password);
		while(pwExist(password)||strlen(password)>20){
			if(pwExist(password)){
				printf("\nSorry, the password is already here");
				printf("\nPlease reenter: ");
			}
			else{
				printf("\nSorry,password too long, please reenter:");
			}
			scanf("%s",password);
		}
		strcpy(adminhead->administratorPassword,password);
		adminend = adminhead;
		adminend->next = NULL;
	}
	admincount++;
	fp = fopen("admins", "w");
	p = adminhead;
	while (p!= NULL){
		fwrite(p, sizeof(struct pw), 1, fp);
		p = p->next;
	}
	fclose(fp);
	system("cls");
	printf("\n===================================================");
	printf("\n|Congratulations! you are registered successfully!|");
	printf("\n|      .......return to the home page.......\n    |");
	printf("\n===================================================");
	Sleep(3000);
	firstInterface();
}
void staffFunction(){
	system("cls");
	printf("\n================================");
	printf("\n|1:add books                   |");
	printf("\n|2:delete books                |");
	printf("\n|3:view all registered students|");
	printf("\n|4:add administrator password  |");
	printf("\n|5:log out                     |");
	printf("\n================================");
	int choice;
	printf("\nenter number to make your choice:");
	scanf("%d",&choice);
	while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5){
		printf("\nWrong input!Please enter again: ");
		scanf("%d",&choice);
	}
	if(choice==1){
		addbook();
	}
	if(choice==2){
		deletebook();
	}
	if(choice==3){
		viewstudents();
	}
	if(choice==4){
		addpassword();
	}
	if(choice==5){
		printf("\n.......return to the home page.......\n");
		Sleep(3000);
		system("cls");
		firstInterface();
	}	
}
void addbook(){
	system("cls");
	struct book *p;
	char bookname[100];
	char author[100];
	FILE *fp;
	if (bookcount == 0){
		printf("\nName of book: ");
		while (scanf("%s",bookname)){
			if (strlen(bookname) > 20)
				printf("too long\n");
			else break;
		}
		strcpy(bookhead->nameOfBook, bookname);
		printf("\nAuthor of book: ");
		scanf("%s", &bookhead->author);
		printf("\nQuantity of book: ");
		scanf("%d", &bookhead->quantity);
		bookend = bookhead;
		bookend->next = NULL;
	}

	else{
		p = (struct book *)malloc(sizeof(struct book));
		printf("\nName of book: ");
		while (scanf("%s",bookname)){
			if (strlen(bookname) > 20)
				printf("too long\n");
			else break;
		}
		printf("\nAuthor of book: ");
		while (scanf("%s",author)){
			if (strlen(bookname) > 20)
				printf("too long\n");
			else break;
		}
		int isexist = 0;
		p = bookhead;
		while (p != NULL){
			if (strcmp(bookname, p->nameOfBook) == 0&&strcmp(author,p->author)==0){
				isexist = 1;
				break;
			}
			p = p->next;
		}
		if (isexist == 1){
			int count;
			printf("\nThe quantity: ");
			scanf("%d", &count);
			p->quantity += count;
		}
		else{
			p = (struct book *)malloc(sizeof(struct book));
			strcpy(p->nameOfBook, bookname);
			printf("\nAuthor of book: ");
			scanf("%s", p->author);
			printf("\nThe quantity: ");
			scanf("%d", &p->quantity);
			bookend->next = p;
			bookend = p;
			bookend->next = NULL;
		}
	}

	bookcount++;
	p = bookhead;
	fp = fopen("books", "w");
	while (p != NULL){
		fwrite(p, sizeof(struct book), 1, fp);
		p = p->next;
	}
	fclose(fp);

	system("cls");
	printf("\n===============================");
	printf("\n|Books are added successfully!|");
	printf("\n----return to the home page---|");
	printf("\n===============================");
	Sleep(3000);
	system("cls");
	firstInterface();
}
void deletebook(){
	system("cls");
	struct book *bookp;
	char bookname[100];
	int exist = 0;
	bookp = bookhead;
	if(bookcount==0){
		printf("no books here");
		Sleep(2000);
		firstInterface();
		return;
	}
	else{
	printf("\nName of the book you want to delete: ");
	printf("\n(Enter 0 to exit)\n");
	while (scanf("%s",bookname)){
		while (bookp != NULL){
			if (strcmp(bookname, bookp->nameOfBook) == 0){
				exist = 1;
				break;
			}
			bookp = bookp->next;
		}
		if(strcmp(bookname,"0")==0){
			firstInterface();
			return;}
		else if (!exist){
			printf("\n-----No such book-----");
			printf("\nReenter:");
		}
		else break;
	}
	bookp = bookhead;
	if (strcmp(bookhead->nameOfBook,bookname) == 0)
		bookhead = bookhead->next;
	while (bookp->next != NULL){
		if (strcmp(bookp->next->nameOfBook, bookname) == 0){
			bookp->next = bookp->next->next;
			break;
		}
		bookp = bookp->next;
	}
	bookp = NULL;
	writeBooks();
	printf("\nDelete successfully!!!\n");
	printf("------return to the home page-----\n");
	firstInterface();}
}
void viewstudents(){
	system("cls");
	struct stu *sp;
	sp = stuhead;
	while (sp != NULL){
		printf("student ID: %s",sp->stuNum);
		int i;
		for(i=0;i<sp->bookcount;i++){
			printf("\nBorrowed book:%s",sp->borrowedBook[i]);
		}
		printf("\n--------------------------------------------");
		printf("\nTotal count of borrowed books:%d",sp->bookcount);
		sp = sp->next;
	}
	printf("\n=====================================");
	printf("\npress enter to back to the home page....");
	if(scanf("%c")) firstInterface();
}
void addpassword(){
	system("cls");
	struct pw *p;
	char *pw;
	FILE *fp;
	printf("\nPassword you want to add: ");
	while (scanf("%s",pw)){
		if (strlen(pw) > 20)
			printf("too long\n");
		else break;
	}
	p = adminhead;
	p = (struct pw *)malloc(sizeof(struct pw));
	strcpy(p->administratorPassword, pw);
	adminend->next = p;
	adminend = p;
	adminend->next = NULL;
	
	p = adminhead;
	fp = fopen("admins", "w");
	while (p != NULL){
		fwrite(p, sizeof(struct book), 1, fp);
		p = p->next;
	}
	fclose(fp);
	system("cls");
	printf("\n==================================");
	printf("\n|Password are added successfully!|");
	printf("\n|----return to the home page-----|");
	printf("\n|=================================");
	Sleep(3000);
	system("cls");
	firstInterface();
	
}
int stuExist(char *stuNum){
	struct stu *p;
	p = stuhead;
	while (p != NULL){	
		if (strcmp(stuNum,p->stuNum)==0){
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int pwExist(char *stuNum){
	struct pw *p;
	p = adminhead;
	while (p != NULL){	
		if (strcmp(stuNum,p->administratorPassword)==0){
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int bookExist(char *bookname){
	struct book *p;
	p = bookhead;
	while (p != NULL){
		if (strcmp(bookname, p->nameOfBook) == 0){
			return 1;
		}
		p = p->next;
	}
	return 0;
	
}

void readStudents(){
	struct stu *p;
	FILE *fp;
	p = stuhead;
	fp = fopen("students", "ab+");
	while (fread(p,sizeof(struct stu),1,fp)){
		if (p->next != NULL){
			p = (struct stu *)malloc(sizeof(struct stu));
			stuend->next = p;
			stuend = p;
			stuend->next = NULL;
		}
	}
}
void readBooks(){
	struct book *p;
	FILE *fp;
	p = bookhead;
	fp = fopen("books", "ab+");
	while (fread(p, sizeof(struct book), 1, fp)){
		if (p->next != NULL){
			p = (struct book *)malloc(sizeof(struct book));
			bookend->next = p;
			bookend = p;
			bookend->next = NULL;
		}
	}
}
void readPassword(){
	struct pw *p;
	FILE *fp;
	p = adminhead;
	fp = fopen("admins", "ab+");
	while (fread(p, sizeof(struct pw), 1, fp)){
		if (p->next != NULL){
			p = (struct pw *)malloc(sizeof(struct pw));
			adminend->next = p;
			adminend = p;
			adminend->next = NULL;
		}
	}
}

void writeStudents(){
	FILE *fp;
	struct stu *userp;
	userp = stuhead;
	fp = fopen("students", "w");
	while (userp != NULL){
		fwrite(userp, sizeof(struct stu), 1, fp);
		userp = userp->next;
	}
	fclose(fp);
}

void writeBooks(){
	FILE *fp;
	struct book *bookp;
	bookp = bookhead;
	fp = fopen("books", "w");
	while (bookp != NULL){
		fwrite(bookp, sizeof(struct book), 1, fp);
		bookp = bookp->next;
	}
	fclose(fp);
}
