#ifndef __HMYLIB_H__
#define __HMYLIB_H__

int incorrectInput(int input);
void firstInterface();
void stuEntrance();
void stuRegister();
void stuLogin();
void staffEntrance();
void borrow(struct stu *);
void stuOperation(struct stu*);
void returnbook(struct stu*);
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
void searchBook();
void readStudents();
void readBooks();
void readPassword();
void firstInterface();
int pwExist(char *);
#endif
