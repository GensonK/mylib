#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include "struct.h"
#include "hmylib.h"

int stucount, admincount, bookcount;
struct stu *stuhead = NULL, *stuend = NULL;
struct pw *adminhead=NULL,*adminend=NULL;
struct book *bookhead = NULL, *bookend = NULL;

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
