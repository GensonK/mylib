#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
struct book{
	char nameOfBook[20];
	char author[20];
	int quantity;
	struct book *next;
};
struct stu{
	char stuNum[20];
	char password[16];
	char borrowedBook[4][20];
	int bookcount;
	struct stu *next;
};
struct pw{
	char administratorPassword[20];
	struct pw *next;
};
int stucount, admincount, bookcount;
struct stu *stuhead = NULL, *stuend = NULL;
struct pw *adminhead=NULL,*adminend=NULL;
struct book *bookhead = NULL, *bookend = NULL;
int incorrectInput(int input);
void firstInterface();
void stuEntrance();
void stuRegister();
void stuLogin();
void staffEntrance();
void borrow();
void stuOperation(struct stu *p);
void writefile(int flag);
void returnbook(struct stu*sp);
void adminLogin();
void adminRegister();
void staffFunction();
void addbook();
void deletebook();
void viewstudents();
void writeStudents();
void writeBooks();
void addpassword();
int stuExist(char *stuNum);
void details();
void change();

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
		system("cls");
		stuEntrance();
	}
	if(choice==2){
		system("cls");
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
		system("cls");
		stuLogin();
	}
	if(choice==2){
		system("cls");
		stuRegister();
	}
	if(choice==3){
		system("cls");
		firstInterface();
	}	
}
void stuLogin(){
	if(stucount==0){
		printf("\nNo student in this library system...");
		printf("\nback to the home page....");
		Sleep(1500);
		firstInterface();
		return;
	}
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
				system("cls");
				printf("Suspect operation, you are forced to return home page... ");
				Sleep(1500);
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
	Sleep(1500);
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
		stuend=stuhead;
		stuend->next=NULL;
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
		strcpy(p->stuNum,stuNum);
		printf("\nValid student ID, please enter your password: ");
		scanf("%s",password);
		while (strlen(password)>16){
			printf("\nSorry,password too long, please reenter:");
			scanf("%s",password);
		}
		strcpy(p->password, password);
		p->bookcount=0;
		stuend->next = p;
		stuend = p;
		stuend->next=NULL;
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
	Sleep(1500);
	firstInterface();
}


void stuOperation(struct stu *p){
	printf("\n==================");
	printf("\n|1:borrow book...|");
	printf("\n|2:return book...|");
	printf("\n|3:log out...    |");
	printf("\n==================");
	printf("\nplease make your choice:");
	int choice;
	scanf("%d",&choice);
	while(incorrectInput(choice)){
		printf("\nwrong input! please enter 1 to 3 to make your choice again:");
		scanf("%d",&choice);
	}
	if(choice==1){
		system("cls");
		borrow(p);
		
	}
	if(choice==2){
		system("cls");
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
	bp=bookhead;
	int exist = 0;
	char bookname[99];
	int i=1;
	printf("\n|Num|name    |author  |count|");
	while(bp!=NULL){
		printf("\n|%3d|%-8s|%-8s|%-5d|",i,bp->nameOfBook,bp->author,bp->quantity);
		i++;
		bp=bp->next; 
	}
	bp=bookhead;
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
				strcpy(sp->borrowedBook[sp->bookcount-1], bp->nameOfBook);
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
		printf("\n.......return to the home page.......");
	}
	Sleep(1500);
	firstInterface();
}
	
void returnbook(struct stu *sp){
	system("cls");
	if (sp->bookcount==0){
		printf("you have not borrowed any book...");
		Sleep(1500);
		firstInterface();
	}
		
	else{
	struct book *bp;
	char bookname[100];
	int count = sp->bookcount;
	int exist=0;
	int flag;
	bp = bookhead;
	int i;
	printf("\nThe books you have borrowed:\n");
	for(i=0;i<sp->bookcount;i++){
		printf("\n%d:%s", i+1,sp->borrowedBook[i]);
	}
	printf("\n=======================================================");
	printf("\nPlease enter the book name to choose which you want to return:");
	scanf("%s",bookname);
	while (bp != NULL){
		if (strcmp(bp->nameOfBook, bookname) == 0){
			bp->quantity++;
			exist=1;
			break;
		}
		bp = bp->next;
	}
	if(!exist){
		printf("\n=========================================================================");
		printf("\n|        The book can not be found from library                         |");
		printf("\n|(deleted or you did not borrow this book from here, you can keep that!)|");
		printf("\n=========================================================================");
		printf("\n.......return to the home page.......\n");
		Sleep(1500);
		system("cls");
		firstInterface();
	}
	else{	
		for ( i= 0; i < sp->bookcount-1; i++){
			if(strcmp(sp->borrowedBook[i],bookname)==1)
			 flag=i;
		}
	for( i=flag;i<sp->bookcount-1;i++){
		strcpy(sp->borrowedBook[i], sp->borrowedBook[i + 1]);
	}
	sp->bookcount--;
	writeStudents();
	writeBooks();
	printf("\n--------Returned successfully!!---------");
	printf("\n.......return to the home page.......\n");
	Sleep(1500);
	firstInterface();
	}
	}
}
void staffEntrance()
{
	system("cls");
	printf("\n=========================================");
	printf("\n|1:Log in with an existing account      |");
	printf("\n|2:Register a new administrator password|");
	printf("\n|3:Return to the home page              |");
	printf("\n=========================================");
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
	if(admincount==0){
		printf("\nthere is no administrator password for this library, please set one first");
		printf("\nnow jump to register entrance...");
		Sleep(1500);
		adminRegister();
		return;
	}
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
			Sleep(1500);
			staffFunction();
			return;
		}
		p = p->next;
	}
	printf("\n-----------Wrong password----------");
	printf("\n------Return to the home page------");
	Sleep(1500);
	firstInterface();
}
void adminRegister(){
	system("cls");
	FILE *fp;
	struct pw *p;
	char password[100];
	char pw[100];
	struct pw *jud;
	int exist=0;
	if (admincount == 0){
		printf("\nplease set a new password for this library system: ");
		scanf("%s",password);
		while (strlen(password)>20){
			printf("\nSorry,password too long, please reenter:");
			scanf("%s",password);
		}
		strcpy(adminhead->administratorPassword, password);
		adminend = adminhead;
		adminend->next = NULL;
		exist=1;
	}
	else{
		printf("\nplease enter registered administrator password:");
		scanf("%s",pw);
		jud=adminhead;
		while(jud!=NULL){
			if(strcmp(jud->administratorPassword,pw)==0){
				exist=1;
				break;
			}
			jud=jud->next;
		}
		if(exist==1){
			p = (struct pw *)malloc(sizeof(struct pw));
			printf("\nplease enter the password you want to add: ");
			scanf("%s",password);
			while(strlen(password)>20){
				printf("\nSorry,password too long, please reenter:");
				scanf("%s",password);
			}
		}
		else{
			printf("\nPassword incorrect!!!");
			printf("\nback to the home page......");
			Sleep(1500);
			firstInterface();
			return;
		}
		strcpy(p->administratorPassword,password);
		adminend->next = p;
		adminend=p;
		adminend->next = NULL;
	}
	if(exist==1){
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
		printf("\n|      .......return to the home page.......      |");
		printf("\n===================================================");
		Sleep(1500);
		firstInterface();
	}
	
}
void staffFunction(){
	system("cls");
	printf("\n================================");
	printf("\n|1:add books                   |");
	printf("\n|2:delete books                |");
	printf("\n|3:view all registered students|");
	printf("\n|4:details of all the books    |");
	printf("\n|5:change book information     |");
	printf("\n|6:add administrator password  |");
	printf("\n|7:return to the home page.... |");
	printf("\n================================");
	int choice;
	printf("\nenter number to make your choice:");
	scanf("%d",&choice);
	while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7){
		printf("\nWrong input enter again:");
		scanf("%d",choice);
	}
	switch(choice){
		case 1:
			addbook();
			break;
		case 2:
			deletebook();
			break;
		case 3 :
			viewstudents();
			break;
		case 4:
			details();
			break;
		case 5:
			change();
			break;
		case 6:
			addpassword();
			break;
		case 7:
			firstInterface();
			break;		
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
		while (scanf("%s",author)){
			if (strlen(author) > 20)
				printf("too long\n");
			else break;
		}
		strcpy(bookhead->author, author);
		printf("\nQuantity of book: ");
		while(!scanf("%d", &bookhead->quantity)){
			printf("\nplease enter an int:");
		}
		bookend=bookhead;
		bookend->next=NULL;
	}

	else{
		p = (struct book *)malloc(sizeof(struct book));
		printf("\nName of book: ");
		while (scanf("%s",bookname)){
			if (strlen(bookname) > 20)
				printf("too long\n");
			else break;
		}
		strcpy(p->nameOfBook, bookname);
		printf("\nAuthor of book: ");
		while (scanf("%s",author)){
			if (strlen(author) > 20)
				printf("too long\n");
			else break;
		}
		strcpy(p->author, author);
		printf("\nQuantity of book: ");
		while(!scanf("%d", &(p->quantity))){
			printf("\nplease enter an int:");
		}
		bookend->next=p;
		bookend=p;
		bookend->next=NULL;
		
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
	Sleep(1500);
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
		Sleep(1500);
		firstInterface();
		return;
	}
	else{
		int i=0;
		struct book *bp;
		bp=bookhead;
		while(bp!=NULL){
		printf("\n%d: %s\t%d",i+1,bp->nameOfBook,bp->quantity);
		bp=bp->next;
		i++;
		}
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
	if(stucount==0){
		printf("\nno registered students in this system");
		printf("\nback to the home page.......");
		Sleep(1500);
		firstInterface();
	}
	while (sp != NULL){
		printf("student ID: %s",sp->stuNum);
		int i;
		for(i=0;i<sp->bookcount;i++){
			printf("\nBorrowed book:%s",sp->borrowedBook[i]);
		}
		printf("\nTotal count of borrowed books:%d",sp->bookcount);
		printf("\n--------------------------------------------");
		printf("\n\n");
		sp = sp->next;
	}
	printf("\n\n\n===================================================");
	printf("\nyou can enter 1 to do sth else or enter anything to exit:");
	int i;
	scanf("%d",&i);
	if(i==1){
		staffFunction();
	}
	else{
		printf("have a good day, bye!");
		return;
	}
}
void details(){
	if(bookcount==0){
		printf("no books here");
		Sleep(1500);
		firstInterface();
		return;
	}
	struct book *bp;
	bp=bookhead;
	int i=1;
	printf("\n|Num|name    |author  |count|");
	while(bp!=NULL){
		printf("\n|%3d|%-8s|%-8s|%-5d|",i,bp->nameOfBook,bp->author,bp->quantity);
		i++;
		bp=bp->next; 
	}
	printf("\nyou can enter 1 to do sth else or enter anything to exit:");
	scanf("%d",&i);
	if(i==1){
		staffFunction();
	}
	else{
		printf("have a good day, bye!");
		return;
	}
}
void change(){
	if(bookcount==0){
		printf("no books here");
		Sleep(1500);
		firstInterface();
		return;
	}
	struct book *bookp;
	char bookname[100];
	int exist = 0;
	int end = 0;
	int count;
	char author[100];
	bookp = bookhead;
	system("cls");
	printf("booklist:\n");
	int i=1;
	printf("\n|Num|name    |author  |count|");
	while(bookp!=NULL){
		printf("\n|%3d|%-8s|%-8s|%-5d|",i,bookp->nameOfBook,bookp->author,bookp->quantity);
		i++;
		bookp=bookp->next; 
	}
	bookp = bookhead;
	printf("\n(you can enter 0 to return to the first interface)\nthe name of the book: ");
	while (scanf("%s",bookname)){
		if (strcmp(bookname, "0") == 0){
			firstInterface();
			break;
		}
		bookp=bookhead;
		while (bookp != NULL){
			if (strcmp(bookp->nameOfBook, bookname) == 0){
				exist = 1;
				break;
			}
			bookp = bookp->next;
		}
		if (!exist)
			printf("\nno such book,reenter: ");
		else
			break;
	}
	printf("\nthe book is found...");
	Sleep(1500);
	system("cls");
	printf("\n=============================");
	printf("\n|1:change name              |");
	printf("\n|2:change author            |");
	printf("\n|3:change quantity          |");
	printf("\n|4:return to the home page..|");
	printf("\n=============================");
	int choice;
	printf("\nmake your choice:");
	scanf("%d",&choice);
	while(choice!=1&&choice!=2&&choice!=3&&choice!=4){
		printf("\nWrong input enter again:");
		scanf("%d",choice);
	}
	switch (choice){
		case 1:{
			printf("\nnew name: ");
			scanf("%s", bookp->nameOfBook);
			break;
		}

		case 2:{
			printf("\nnew author: ");
			scanf("%s",bookp->author);
			break;
		}
		case 3:{
			printf("\nnew quantity: ");
			scanf("%d",&bookp->quantity);
			break;
		}
		case 4:{
			firstInterface();
			break;
		}
	}
	writeBooks();
	printf("\nthe information of book was update successfully");
	printf("\nbace to the home page....");
	Sleep(1500);
	firstInterface();
	
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
	Sleep(1500);
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

int main(){
	FILE *fp;
	bookhead=(struct book *)malloc(sizeof(struct book));
	stuhead=(struct stu *)malloc(sizeof(struct stu));
	adminhead=(struct pw *)malloc(sizeof(struct pw));
	
	fp = fopen("students", "a+");
	stucount = fread(stuhead, sizeof(struct stu), 1, fp);
	fclose(fp);
	stuend = stuhead;
	readStudents();

	fp = fopen("books", "a+");
	bookcount = fread(bookhead, sizeof(struct book), 1, fp);
	fclose(fp);
	bookend = bookhead;
	readBooks();
	
    fp = fopen("admins", "a+");
	admincount = fread(adminhead, sizeof(struct pw), 1, fp);
	fclose(fp);
	adminend = adminhead;
	readPassword();
    
	firstInterface();
	return 0;
}
