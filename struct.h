#ifndef __STRUCT_H__
#define __STRUCT_H__

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

extern int stucount, admincount, bookcount;
extern struct stu *stuhead, *stuend;
extern struct pw *adminhead,*adminend;
extern struct book *bookhead, *bookend;

#endif
