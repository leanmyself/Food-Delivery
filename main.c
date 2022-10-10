#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#define USER_MAX 30

#include "admin_login.h"
#include "employee.h"
#include "user_login.h"
#include "exit.h"
#include "about.h"

typedef struct product {
	char	name[30];
	float 	price;
	int		rank;
	struct 	product *next;

}product;

typedef struct menu {
	product *start;

}menu;

typedef struct stack {
	int s[100];
	int tos;

}stack;

typedef struct orderproduct {
	char 	name[30];
	float 	price;
	int 	quantity;
	struct	orderproduct *next,*prev;

}orderproduct;

typedef struct orderlist {
	double total;
	orderproduct *start,*last;

}orderlist;

struct{
    int acct;
    char pass[20];
    int balance;
}bankbdo;

struct{
    int piacc;
    char pipass[20];
    int pibalance;
}bpii;

void push(stack *t,int ele);
char pop(stack *t);
stack tobaseN(int n,int d);
void displaymenu(menu *t);
void insertfood(menu *t,product ele);
void getmenu(menu *t);
void changeprice(menu *m,int pos,float newPrice);
void deletefood(menu *m,int pos);
void savemenu(menu *m);

void get_time(char Curr_time[]);
void display_order(orderlist *t);
void rank(menu *m,char a[],int n);
void add_order(menu *m,orderlist *ol,int i,int n);
void order_quantity(menu *m,orderlist *ol,int i,int n);
void remove_order(menu *m,orderlist *ol,int i);
void print(orderlist *ol);
void saveorder(menu *m,int reset);

int i, j, k, c, n=0, ch, reset,pos, method, pili, rest;
char d = 'n';
FILE *file, *fileb;
menu m;
product food;
orderlist ol;

int main(void){

system("mode con: cols=90 lines=30");

    for(i=0; i<90; i++){    /*BOX SHAPED AT THE TOP */
        printf("\xb2");
    }
    system("color 0C");     /*COLOR OF THE TEXT AND BACKGROUND OF COMMAND LINE */

    time_t t;
    time(&t);
    pre(9);printf("%s", ctime(&t));br(3); /*PRINT CURRENT DATE AND TIME */
    pre(2);printf("           ___                             ___          \n");
    pre(2);printf("            |                               |           \n");
    pre(2);printf("            |                               |           \n");
    pre(2);printf("____________O_______________________________O___________\n");
    pre(2);printf("|                                                      |\n");
    pre(2);printf("|                Welcome to  Dig It Diner              |\n");
    pre(2);printf("|                                                      |\n");
    pre(2);printf("|                                                      |\n");
    pre(2);printf("|                                                      |\n");
    pre(2);printf("|______________________________________________________|\n");

    br(10);pre(2); printf("Please Enter Any Key to Continue");
    for(i=0; i<5; i++){
        printf(".");
        Sleep(500);     /* AFTER PRINTING ONE, ANOTHER COMES AT 0.5 SECONDS */
    }
printf("\n\n\n\n");

    for(i=0; i<90; i++){ /*BOX SHAPED AT THE BOTTOM */
        printf("\xb2");
    }
    getch();
    system("cls"); br(1);  /*CLEARS THE SCREEN */

    loadingbar();   /*CALL THE FUNCTION LOADING BAR */
    system("cls");  /*CLEARS THE SCREEN */
    second();       /*CALL THE FUNCTION SECOND */
}

void second() {

int key;

system("color 0C");    /*COLOR OF THE TEXT AND BACKGROUND OF COMMAND LINE */
    for(i=0; i<90; i++){
        printf("\xb2");
    }
    br(3); pre(3);printf("      *Welcome to Dig it Diner*      ");br(3);
    pre(3);printf("Please Enter Designated Key To Continue");br(2);

    mainmenu();

br(4);pre(4);printf("\xA9 All Rights Reserved\n\n");

    printf("\n\nEnter your choice: ");
    scanf("%d", &key);

    switch(key) {
        case 1: {
            userlogin();
            break;
        }
        case 2: {
            system("cls");
            loginadmin();
            break;
        }
        case 3: {
            system("cls");
            aboutus();
            break;
        }
        case 4: {
            ext();
            break;
        }
        default: {
            printf("\n\nInvalid Entry, Please try again\n\n"); Sleep(400);
            system("cls");
            second();
            break;
        }
    }
}

void mainmenu(){
	br(3); pre(3); echo("[1]. Customer"); Sleep(400);
	br(2); pre(3); echo("[2]. Staff"); Sleep(400);
	br(2); pre(3); echo("[3]. About Us");  Sleep(400);
	br(2); pre(3); echo("[4]. Exit");  Sleep(400);
	br(1);

}

void loadingbar(){
	for (int i=10;i<=100;i+=8){
        system("color 0C");
		system("cls");

		br(7);pre(4);printf("%d %% Loading...",i);br(2);pre(2);
		printf(" ");

		for (int j=0; j<i;j+=2){
			loadingcolor();
			printf(" ");
		}
		Sleep(100);
    }
}

void loadingcolor(){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
}

void br(int line){
	for(int i=0; i<line;i++){
		printf("\n");
	}
}

void pre(int tab){
	for(int i=0; i<tab;i++){
		printf("\t");
	}

}

void echo(char print[]){
	printf("%s",print);
}


void crudmenu(){
    displaymenu(&m);
    br(4); pre(3); printf("1. Add Product"); Sleep(400);
    br(2); pre(3); printf("2. Delete Product"); Sleep(400);
    br(2); pre(3); printf("3. Change Price"); Sleep(400);
    br(2); pre(3); printf("4. Back to Menu");  Sleep(400);
    br(2); pre(3); printf("Enter your choice: ");
}

void availaberesto() {
    br(2);pre(3);printf("List of Available Restaurants");
    br(2);pre(3);printf("1. Burger King");
    br(2);pre(3);printf("2. Greenwich Pizza");
    br(2);pre(3);printf("3. StarBucks Coffee");
    br(2);pre(3);printf("4. Chow King");
    br(2);pre(3);printf("5. Conti's Bakery and Cafe");
    br(2);pre(3);printf("6. Back to Menu");
    br(4);pre(3);printf("Please enter key: ");
}

/* ADMIN SECTION
   Menus and Functionality
*/
void adminmenu() {
    int menu, shopmenu;
    char z[1000];

    br(2);pre(4); echo("MENU"); Sleep(400);
    br(3);pre(3); echo("[1]. Restaurants"); Sleep(400);
    br(2);pre(3); echo("[2]. Food Menu"); Sleep(400);
	br(2);pre(3); echo("[3]. Delivery Employees");  Sleep(400);
    br(2);pre(3); echo("[4]. Current Order"); Sleep(400);
	br(2);pre(3); echo("[5]. Back to Menu"); br(3); Sleep(400);

    pre(3);echo("Please enter key: ");
	scanf("%d", &menu);

	switch(menu) {
        case 1: {
            listmenu:
            system("cls");
            int shopmenu;
                availaberesto();
                scanf("%d", &shopmenu);
                    switch(shopmenu) {
                        case 1:{
                            system("cls");
                            burgerking();
                            break;
                        }
                        case 2: {
                            system("cls");
                            greenwich();
                            break;
                        }
                        case 3: {
                            system("cls");
                            starbucks();
                            break;
                        }
                        case 4: {
                            system("cls");
                            chowking();
                            break;
                        }
                        case 5: {
                            system("cls");
                            contis();
                            break;
                        }
                        case 6: {
                            system("cls");
                            adminmenu();
                            break;
                        }
                        default: {
                            br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                            system("cls");
                            goto listmenu;
                        }
                    }
        break;
        }
        case 2: {
            system("cls");
            foodmenu();
            break;
        }
        case 3: {
            system("cls");
            employeesmenu();
            break;
        }
        case 4: {
            system("cls");
            pre(4);printf("============================");br(1);
            pre(5);printf("Current Order");br(1);
            pre(4);printf("============================");br(4);
            displayorder();
            br(2);system("pause");
            system("cls");
            adminmenu();
            break;
        }
        case 5: {
            system("cls");
            second();
            break;
        }
        default: {
            br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
            system("cls");
            adminmenu();
            break;
        }
	}
}

void displayorder() {
   int c;
   file = fopen("order.txt", "r");
   if (file) {
    while ((c = getc(file)) != EOF){
        putchar(c);
    }
    fclose(file);
}
    return 0;
}

int burgerking() {
    m.start = NULL;
    food.rank = 0;
	getburgerkingmenu(&m);

	while(1){
        crudmenu();
		scanf("%d",&c);

		switch(c){
			case 1 : {
			    br(2); pre(3);printf("Enter Name of food: ");
                fflush(stdin);
                gets(food.name);

                br(2);pre(3);printf("Enter Price of food: ");
                scanf("%f",&food.price);

                insertfood(&m,food);
                system("cls");
                break;
			}
			case 2 : {
                br(2); pre(3);printf("Enter index of item to be deleted: ");
                scanf("%d",&n);

                deletefood(&m,n);
                system("cls");
                break;
			}
			case 3 :{
			    br(2); pre(3);printf("Enter index of item to change price: ");
                scanf("%d",&n);

                br(2); pre(3);printf("Enter New Price of food: ");
                scanf("%f",&food.price);

                changeprice(&m,n,food.price);
                system("cls");
                break;
			}
            case 4: {
                br(2);pre(3);printf("You want to save the changes? press y or Y: ");
                fflush(stdin);
                scanf("%c",&d);
                    if(d == 'y'||d == 'Y') {
                        saveburgerkingmenu(&m);
                    }
                system("cls");
                adminmenu();
                break;
            }
			default: {
			    br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                system("cls");
                burgerking();
                break;
			}
		}
	}
}

int greenwich() {
    m.start = NULL;
	food.rank = 0;
	getgreenwichmenu(&m);

	while(1){
        crudmenu();
		scanf("%d",&c);

		switch(c){
			case 1 : {
			    br(2); pre(3);printf("Enter Name of food: ");
                fflush(stdin);
                gets(food.name);

                br(2);pre(3);printf("Enter Price of food: ");
                scanf("%f",&food.price);

                insertfood(&m,food);
                system("cls");
                break;
			}
			case 2 : {
                br(2); pre(3);printf("Enter index of item to be deleted: ");
                scanf("%d",&n);

                deletefood(&m,n);
                system("cls");
                break;
			}
			case 3 :{
			    br(2); pre(3);printf("Enter index of item to change price: ");
                scanf("%d",&n);

                br(2); pre(3);printf("Enter New Price of food: ");
                scanf("%f",&food.price);

                changeprice(&m,n,food.price);
                system("cls");
                break;
			}
            case 4: {
                br(2);pre(3);printf("You want to save the changes? press y or Y: ");
                fflush(stdin);
                scanf("%c",&d);
                    if(d == 'y'||d == 'Y') {
                        savegreenwichmenu(&m);
                    }
                        system("cls");
                        adminmenu();
                break;
            }
			default: {
			     br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                system("cls");
                greenwich();
                break;
			}
		}
	}
}

int starbucks() {
    m.start = NULL;
	food.rank = 0;
	getstarbucksmenu(&m);

	while(1){
        crudmenu();
		scanf("%d",&c);

		switch(c){
			case 1 : {
			    br(2); pre(3);printf("Enter Name of food: ");
                fflush(stdin);
                gets(food.name);

                br(2);pre(3);printf("Enter Price of food: ");
                scanf("%f",&food.price);

                insertfood(&m,food);
                system("cls");
                break;
			}
			case 2 : {
                br(2); pre(3);printf("Enter index of item to be deleted: ");
                scanf("%d",&n);

                deletefood(&m,n);
                system("cls");
                break;
			}
			case 3 :{
			    br(2); pre(3);printf("Enter index of item to change price: ");
                scanf("%d",&n);

                br(2); pre(3);printf("Enter New Price of food: ");
                scanf("%f",&food.price);

                changeprice(&m,n,food.price);
                system("cls");
                break;
			}
            case 4: {
                br(2);pre(3);printf("You want to save the changes? press y or Y: ");
                fflush(stdin);
                scanf("%c",&d);
                    if(d == 'y'||d == 'Y') {
                        savestarbucksmenu(&m);
                    }
                system("cls");
                adminmenu();
                break;
            }
			default: {
                br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                system("cls");
                starbucks();
                break;
			}
		}
	}
}

int chowking() {
    m.start = NULL;
	food.rank = 0;
	getchowkingmenu(&m);

	while(1){
        crudmenu();
		scanf("%d",&c);

		switch(c){
			case 1 : {
			    br(2); pre(3);printf("Enter Name of food: ");
                fflush(stdin);
                gets(food.name);

                br(2);pre(3);printf("Enter Price of food: ");
                scanf("%f",&food.price);

                insertfood(&m,food);
                system("cls");
                break;
			}
			case 2 : {
                br(2); pre(3);printf("Enter index of item to be deleted: ");
                scanf("%d",&n);

                deletefood(&m,n);
                system("cls");
                break;
			}
			case 3 :{
			    br(2); pre(3);printf("Enter index of item to change price: ");
                scanf("%d",&n);

                br(2); pre(3);printf("Enter New Price of food: ");
                scanf("%f",&food.price);

                changeprice(&m,n,food.price);
                system("cls");
                break;
			}
            case 4: {
                br(2);pre(3);printf("You want to save the changes? press y or Y: ");
                fflush(stdin);
                scanf("%c",&d);
                    if(d == 'y'||d == 'Y') {
                        savechowkingmenu(&m);
                    }
                system("cls");
                adminmenu();
                break;
            }
			default: {
                br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                system("cls");
                chowking();
                break;
			}
		}
	}
}

int contis() {
    m.start = NULL;
	food.rank = 0;
	getcontismenu(&m);

	while(1){
        crudmenu();
		scanf("%d",&c);

		switch(c){
			case 1 : {
			    br(2); pre(3);printf("Enter Name of food: ");
                fflush(stdin);
                gets(food.name);

                br(2);pre(3);printf("Enter Price of food: ");
                scanf("%f",&food.price);

                insertfood(&m,food);
                system("cls");
                break;
			}
			case 2 : {
                br(2); pre(3);printf("Enter index of item to be deleted: ");
                scanf("%d",&n);

                deletefood(&m,n);
                system("cls");
                break;
			}
			case 3 :{
			    br(2); pre(3);printf("Enter index of item to change price: ");
                scanf("%d",&n);

                br(2); pre(3);printf("Enter New Price of food: ");
                scanf("%f",&food.price);

                changeprice(&m,n,food.price);
                system("cls");
                break;
			}
            case 4: {
                br(2);pre(3);printf("You want to save the changes? press y or Y: ");
                fflush(stdin);
                scanf("%c",&d);
                    if(d == 'y'||d == 'Y') {
                        savecontismenu(&m);
                    }
                system("cls");
                adminmenu();
                break;
            }
			default: {
			    br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                system("cls");
                contis();
                break;
			}
		}
	}
}

void foodmenu() {
    m.start = NULL;
	food.rank = 0;
	getmenu(&m);

	while(1){
        crudmenu();
		scanf("%d",&c);

		switch(c){
			case 1 : {
			    br(2); pre(3);printf("Enter Name of food: ");
                fflush(stdin);
                gets(food.name);

                br(2);pre(3);printf("Enter Price of food: ");
                scanf("%f",&food.price);

                insertfood(&m,food);
                system("cls");
                break;
			}
			case 2 : {
                br(2); pre(3);printf("Enter index of item to be deleted: ");
                scanf("%d",&n);

                deletefood(&m,n);
                system("cls");
                break;
			}
			case 3 :{
			    br(2); pre(3);printf("Enter index of item to change price: ");
                scanf("%d",&n);

                br(2); pre(3);printf("Enter New Price of food: ");
                scanf("%f",&food.price);

                changeprice(&m,n,food.price);
                system("cls");
                break;
			}
            case 4: {
                br(2);pre(3);printf("You want to save the changes? press y or Y: ");
                fflush(stdin);
                scanf("%c",&d);
                    if(d == 'y'||d == 'Y') {
                        savemenu(&m);
                    }
                system("cls");
                adminmenu();
                break;
            }
			default: {
			    printf("\n\nInvalid Entry, Please try again\n\n"); Sleep(400);
                system("cls");
                foodmenu();
                break;
			}
		}
	}
}

void employeesmenu() {
    employeelist();
    br(4); pre(3);echo("1. Add new employee");
    br(1); pre(3);echo("2. Search employee");
    br(1); pre(3);echo("3. Delete employee");
    br(1); pre(3);echo("4. Back to Menu");

    br(3);pre(3);echo("Please enter your choice: ");
    scanf("%d", &c);
    switch(c) {
        case 1: {
            system("cls");
            addemployee();
            br(3);pre(3);printf("Please Enter Any Key to Go to Main Menu");Sleep(400);
            getch();
            system("cls"); //clears the screen
            employeesmenu();
            break;
        }
        case 2: {
            system("cls");
            searchemployee();
            br(3);pre(2);printf("Please Enter Any Key to Go to Main Menu");Sleep(400);
            getch();
            system("cls"); //clears the screen
            employeesmenu();
            break;
        }
        case 3: {
            system("cls");
            deleteemployee();
            br(3);pre(2);printf("Please Enter Any Key to Go to Main Menu");Sleep(400);
            getch();
            system("cls"); //clears the screen
            employeesmenu();
            break;
        }
        case 4: {
            system("cls");
            adminmenu();
            break;
        }
        default: {
            br(3);pre(3);printf("Invalid Entry, Please try again\n\n");Sleep(400);
            system("cls");
            employeesmenu();
            break;
        }

    }

}

/* ADMIN SECTION
   Create, Update, Delete By Food menu
*/
void push(stack *t,int ele) {
	t->s[++t->tos] = ele;
}

char pop(stack *t) {
	int z = t->s[t->tos];
	t->tos--;
	if(z>9)
	     return((char)z+55);
	else return((char)z+'0');
}

stack tobaseN(int n,int d) {
	stack x;
	x.tos=-1;
	while(d!=0){
		push(&x,d%n);
		d=d/n;
	}
	return x;
}

void displaymenu(menu *t) {
	int i=1;
    product *q;
    if(t->start == NULL){
        br(2);pre(3);printf("Menu Empty\n");
        return;
    }
    q = t->start;
    br(2);pre(2);printf("=========================================================");
    br(1);pre(2);printf("Food Name\t\t\tPrice");
    br(1);pre(2);printf("=========================================================");br(1);
    while(q!= NULL){
        pre(2);printf("%d. %-20s\t\t%.2f Pesos\n",i++,q->name,q->price);
        q = q->next;
    }br(1);
}

void insertfood(menu *t,product ele) {
	product *p,*q,*r;
	p = (product*)malloc(sizeof(product));
	strcpy(p->name,ele.name);
	p->price = ele.price;
	p->rank = ele.rank;
	if(t->start == NULL){
		t->start = p;
		p->next = NULL;
		return;
	}
	if(ele.rank > t->start->rank){
		p->next = t->start;
		t->start = p;
		return;
	}
	r = t->start;
	q = t->start->next;
	while(q != NULL){
		if(ele.rank > q->rank)
		{
			r->next = p;
			p->next = q;
			return;
		}
		r = q;
		q = q->next;
	}
	r->next = p;
	p->next = NULL;
}

void getmenu(menu *t) {
	FILE *fmenu;
	product x;
	fmenu = fopen("foodmenu.txt","r");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s%f%d",x.name,&x.price,&x.rank) != EOF)
		insertfood(t,x);
	fclose(fmenu);
}

void getburgerkingmenu(menu *t) {
	FILE *fmenu;
	product x;
	fmenu = fopen("burgerkingmenu.txt","r");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s %f %d",x.name,&x.price,&x.rank) != EOF)
		insertfood(t,x);
	fclose(fmenu);
}

void getgreenwichmenu(menu *t) {
	FILE *fmenu;
	product x;
	fmenu = fopen("greenwichmenu.txt","r");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s %f %d",x.name,&x.price,&x.rank) != EOF)
		insertfood(t,x);
	fclose(fmenu);
}

void getchowkingmenu(menu *t) {
	FILE *fmenu;
	product x;
	fmenu = fopen("chowkingmenu.txt","r");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s %f %d",x.name,&x.price,&x.rank) != EOF)
		insertfood(t,x);
	fclose(fmenu);
}

void getstarbucksmenu(menu *t) {
	FILE *fmenu;
	product x;
	fmenu = fopen("starbucksmenu.txt","r");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s %f %d",x.name,&x.price,&x.rank) != EOF)
		insertfood(t,x);
	fclose(fmenu);
}

void getcontismenu(menu *t) {
	FILE *fmenu;
	product x;
	fmenu = fopen("contismenu.txt","r");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s %f %d",x.name,&x.price,&x.rank) != EOF)
		insertfood(t,x);
	fclose(fmenu);
}

void changeprice(menu *m,int pos,float newPrice) {
	product *q = m->start;
	if(q == NULL){
		br(2);pre(3);printf("Menu is Empty\n");
		return;
	}
	for(int i=0;i < pos-1 && q != NULL;i++)
        q = q->next;
	if(pos <= 0|| q == NULL){
		br(2);pre(3);printf("Invalid Choice!");Sleep(600);
		return;
	}
	br(2);pre(1);printf("Price of %s is changed from %.3f to %.3f\n",q->name, q->price, newPrice);Sleep(1000);
	q->price = newPrice;
}

void deletefood(menu *m,int pos) {
	product *q = m->start;
	if(pos == 1){
		br(2);pre(3);printf("%s is deleted\n",m->start->name);Sleep(1000);
		m->start = m->start->next;
		return;
	}
	for(i=0;i < pos-2 && q != NULL;i++)
        q = q->next;
	if(pos <= 0|| q == NULL){
		br(2);pre(3);printf("Invalid Choice!\n");
		return;
	}
	br(2);pre(3);printf("%s is deleted\n",q->next->name);Sleep(1000);
	q->next = q->next->next;
}

void savemenu(menu *m) {
	FILE *fmenu;
	product *q = m->start;
	fmenu = fopen("foodmenu.txt","w");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(4);
	}
	while(q != NULL){
        if(reset == 1)
			q->rank /= 2;
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->rank);
		q = q->next;
	}
	fclose(fmenu);
}

void saveburgerkingmenu(menu *m) {
	FILE *fmenu;
	product *q = m->start;
	fmenu = fopen("burgerkingmenu.txt","w");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(4);
	}
	while(q != NULL){
        if(reset == 1)
			q->rank /= 2;
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->rank);
		q = q->next;
	}
	fclose(fmenu);
}

void savegreenwichmenu(menu *m) {
	FILE *fmenu;
	product *q = m->start;
	fmenu = fopen("greenwichmenu.txt","w");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(4);
	}
	while(q != NULL){
        if(reset == 1)
			q->rank /= 2;
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->rank);
		q = q->next;
	}
	fclose(fmenu);
}

void savestarbucksmenu(menu *m) {
	FILE *fmenu;
	product *q = m->start;
	fmenu = fopen("starbucksmenu.txt","w");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(4);
	}
	while(q != NULL){
        if(reset == 1)
			q->rank /= 2;
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->rank);
		q = q->next;
	}
	fclose(fmenu);
}

void savechowkingmenu(menu *m) {
	FILE *fmenu;
	product *q = m->start;
	fmenu = fopen("chowkingmenu.txt","w");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(4);
	}
	while(q != NULL){
        if(reset == 1)
			q->rank /= 2;
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->rank);
		q = q->next;
	}
	fclose(fmenu);
}

void savecontismenu(menu *m) {
	FILE *fmenu;
	product *q = m->start;
	fmenu = fopen("contismenu.txt","w");
	if(fmenu == NULL){
		printf("cannot open file\n");
		exit(4);
	}
	while(q != NULL){
        if(reset == 1)
			q->rank /= 2;
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->rank);
		q = q->next;
	}
	fclose(fmenu);
}
/* CUSTOMER SECTION
  Menus and Functionality
*/
void userprocess() {

	m.start = NULL;
	ol.start = ol.last = NULL;
	ol.total = 0;

    system("cls");
    br(3);pre(3);echo("*Food Purchasing*"); Sleep(400);
    br(2);pre(3);echo("[1] By Restaurants"); Sleep(400);
    br(2);pre(3);echo("[2] By Food"); Sleep(400);
    br(2);pre(3);echo("[3] Sign out"); Sleep(400);
    br(3);pre(3);echo("Please enter key: ");
    scanf("%d", &ch);

    switch(ch) {
        case 1: {
            system("cls");
            int shopm;
                availaberesto();
                scanf("%d", &shopm);
                    switch(shopm) {
                        case 1:{
                            system("cls");
                            getburgerkingmenu(&m);
                            br(2);pre(4);printf("Welcome to Burger King");br(1);
                            byfood();
                            break;
                        }
                        case 2:{
                            system("cls");
                            getgreenwichmenu(&m);
                            br(2);pre(4);printf("Welcome to Greenwich");br(1);
                            byfood();
                            break;
                        }
                        case 3: {
                            system("cls");
                            getstarbucksmenu(&m);
                            br(2);pre(4);printf("Welcome to Starbucks Coffee");br(1);
                            byfood();
                            break;
                        }
                        case 4: {
                            system("cls");
                            getchowkingmenu(&m);
                            br(2);pre(4);printf("Welcome to Chowking");br(1);
                            byfood();
                            break;
                        }
                        case 5: {
                            system("cls");
                            getcontismenu(&m);
                            br(2);pre(4);printf("Welcome to Conti's Cafe");br(1);
                            byfood();
                            break;
                        }
                        case 6: {
                            system("cls");
                            userprocess();
                            break;
                        }
                        default: {
                            printf("\n\nInvalid Entry, Please try again\n\n"); Sleep(400);
                            system("cls");
                            userprocess();
                            break;
                        }
                }
        break;
        }
        case 2: {
            system("cls");
            getmenu(&m);
            br(2);pre(4);printf("Welcome to our Shop");br(1);
            byfood();
            break;
        }
        case 3: {
            system("cls");
            second();
            break;
        }
        default: {
            printf("\n\nInvalid Entry, Please try again\n\n"); Sleep(400);
            system("cls");
            userprocess();
            break;
        }

    }
}

void byfood() {
    int n; float newQ;

    while(1){
        br(2);pre(3);printf("Opening Hours Today  10:00 AM-10:00 PM");
        displaymenu(&m);
        br(3);pre(3);echo("1. Add Order"); Sleep(400);
        br(1);pre(3);echo("2. Remove Order"); Sleep(400);
        br(1);pre(3);echo("3. Change Quantity of Order"); Sleep(400);
        br(1);pre(3);echo("4. View Order"); Sleep(400);
        br(1);pre(3);echo("5. Confirm your Order"); Sleep(400);
        br(1);pre(3);echo("6. Cancel"); Sleep(400);
        br(2);pre(3);printf("Enter your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1 :{
			    br(2);pre(3);printf("Enter index of food you want: ");
                scanf("%d",&pos);

                br(2);pre(3);printf("How many do you want?: ");
                scanf("%d",&n);
					if(n <= 0) {
                        br(2);pre(3);printf("Quantity can not be less than 1"); Sleep(1000);
                        system("cls");
						break;
					}
                add_order(&m,&ol,pos,n);
                system("cls");
                break;
			}
			case 2 :{
                system("cls");
			    display_order(&ol);
                br(2);pre(3);printf("Enter index of item to be deleted: ");
                scanf("%d",&pos);

                remove_order(&m,&ol,pos);
                br(2);pre(3);system("pause");
                system("cls");
                break;
			}
			case 3 : {
                system("cls");
			    display_order(&ol);
                br(2);pre(3);printf("Enter index of item to change quantity: ");
                scanf("%d",&pos);

                br(2);pre(3);printf("how many do you want?: ");
                scanf("%f",&newQ);
					if(newQ <= 0){
                        br(2);pre(3);printf("Quantity can not be less than 1"); Sleep(1000);
                        system("cls");
						break;
					}
                order_quantity(&m,&ol,pos,newQ);
                system("cls");
                break;
			}
			case 4 : {
			    system("cls");
                br(2);pre(4);printf("===============================");
			    br(1);pre(5);printf("List of your order");
			    br(1);pre(4);printf("==============================="); br(3);
                display_order(&ol);
                br(2);pre(4);system("pause");
                system("cls");
                break;
			}
			case 5 :{
			    payment:
                system("cls");
                br(2);pre(4);printf("===============================");
			    br(1);pre(5);printf("List of your order");
			    br(1);pre(4);printf("==============================="); br(3);
			    display_order(&ol);
                br(1);pre(4);printf("Delivery charge = 45 Pesos");
                br(3);pre(3);printf("Do you want Confirm this Order?(y/n): ");
                fflush(stdin);
                scanf("%c",&c);
					if(c == 'y' || c == 'Y') {
                        method:
                        system("cls");
                        br(2);pre(3);printf("Select your payment method: ");
                        br(3);pre(3);printf(" 1. Cash Payment");
                        br(2);pre(3);printf(" 2. Card Payment");
                        br(4);pre(3);printf("Enter your choice: ");
                        scanf("%d", &method);
                        switch(method){
                        case 1: {
                            system("cls");
                            print(&ol);
                            br(2);pre(3);printf("Your order is now in process");
                            br(2);pre(3);printf("Please, Ready your payment");
                            for(int i=0; i<=10; i++) {
                                Sleep(400);
                            }
                            time_t t = time(NULL);
                            struct tm tm = *localtime(&t);
                            br(5);pre(3);printf("Expected arrival time of delivery: %02d:%02d", tm.tm_hour, tm.tm_min+30);
                            for(int i=0; i<=10; i++) {
                                Sleep(600);
                            }
                            br(2);pre(3);system("pause");
                            system("cls");
                            second();
                            break;
                        }
                        case 2: {
                            bank:
                            system("cls");
                            br(2);pre(3);printf("List of Bank Available");
                            br(3);pre(3);printf("1. BANCO DE ORO");
                            br(2);pre(3);printf("2. BPI");
                            br(2);pre(3);printf("Choose Bank: ");
                            scanf("%d",&pili);
                                switch(pili){
                                    case 1: {
                                        int account,test;
                                        char pass[20];
                                        int nacc,nbal;
                                            FILE *file = fopen("bdo.dat","r");
                                            br(2);pre(3);printf("Enter Account number: ");
                                            scanf("%d",&account);
                                                while(fscanf(file,"%d %s %d",&bankbdo.acct,bankbdo.pass,&bankbdo.balance)!=EOF){
                                                    if(account ==bankbdo.acct)
                                                        test=1;
                                                }
                                            if(test!=1){
                                                    br(2);pre(3);printf("Account number doesn't exist"); Sleep(600);
                                                    system("cls");
                                                    goto method;
                                            }
                                                fclose(file);


                                            br(2);pre(3);printf("Enter Password: ");
                                            scanf("%s",pass);
                                            test=0;

                                            file = fopen("bdo.dat","r");
                                                while(fscanf(file,"%d %s %d",&bankbdo.acct,bankbdo.pass,&bankbdo.balance)!=EOF){
                                                    if(account == bankbdo.acct && strcmp(pass,bankbdo.pass)==0){
                                                        test=1;
                                                    if(bankbdo.balance<200){
                                                        br(2);pre(1);printf("You don't have enough balance, you must have 200 Pesos to complete transaction\n"); Sleep(1000);
                                                        br(2);pre(1);printf("Your Current balance is %d",bankbdo.balance); Sleep(1000);
                                                        system("cls");
                                                        goto method;
                                                        }
                                                    else if(bankbdo.balance>200){
                                                        system("cls");
                                                        print(&ol);
                                                        br(2);pre(3);printf("Your order is now in process");
                                                            for(int i=0; i<=10; i++) {
                                                                Sleep(400);
                                                            }
                                                        time_t t = time(NULL);
                                                        struct tm tm = *localtime(&t);
                                                        br(5);pre(3);printf("Expected arrival time of delivery: %02d:%02d", tm.tm_hour, tm.tm_min+30);
                                                            for(int i=0; i<=10; i++) {
                                                                Sleep(600);
                                                            }
                                                        br(2);pre(3);system("pause");
                                                        system("cls");
                                                        second();
                                                        }
                                                    }
                                                }
                                            if(test!=1){
                                                    br(2);pre(3);printf("Wrong Password"); Sleep(600);
                                                    system("cls");
                                                    goto bank;
                                            }
                                        fclose(file);
                                        break;
                                    }
                                    case 2: {
                                        int account,test;
                                        char pass[20];
                                        int nacc,nbal;
                                        FILE *fileb = fopen("bpi.dat","r");

                                        br(2);pre(3);printf("Enter Account number: ");
                                        scanf("%d",&account);

                                        while(fscanf(fileb,"%d %s %d",&bpii.piacc,bpii.pipass,&bpii.pibalance)!=EOF){
                                            if(account ==bpii.piacc)
                                            test=1;
                                        }
                                            if(test!=1){
                                                br(2);pre(3);printf("Account number doesn't exist"); Sleep(600);
                                                system("cls");
                                                goto method;
                                            }
                                        fclose(fileb);
                                        br(2);pre(3);printf("Enter Password: ");
                                        scanf("%s",pass);
                                        test=0;

                                        fileb = fopen("bpi.dat","r");
                                            while(fscanf(fileb,"%d %s %d",&bpii.piacc,bpii.pipass,&bpii.pibalance)!=EOF){
                                                if(account == bpii.piacc && strcmp(pass,bpii.pipass)==0){
                                                    test=1;
                                                        if(bpii.pibalance<200){
                                                            br(2);pre(1);printf("You don't have enough balance, you must have 200 Pesos to complete transaction\n"); Sleep(1000);
                                                            br(2);pre(1);printf("Your Current balance is %d",bpii.pibalance); Sleep(1000);
                                                            system("cls");
                                                            goto method;
                                                        }
                                                }
                                                else if(bpii.pibalance>200){
                                                        system("cls");
                                                        print(&ol);
                                                        br(2);pre(3);printf("Your order is now in process");
                                                            for(int i=0; i<=10; i++) {
                                                                Sleep(400);
                                                            }
                                                        time_t t = time(NULL);
                                                        struct tm tm = *localtime(&t);
                                                        br(5);pre(3);printf("Expected arrival time of delivery: %02d:%02d", tm.tm_hour, tm.tm_min+30);
                                                            for(int i=0; i<=10; i++) {
                                                                Sleep(600);
                                                            }
                                                        br(2);pre(3);system("pause");
                                                        system("cls");
                                                        second();
                                                }
                                            }
                                        if(test!=1){
                                            br(2);pre(3);printf("Wrong Password"); Sleep(600);
                                            system("cls");
                                            goto bank;
                                        }
                                  fclose(file);
                                  break;
                                }
                            default: {
                                br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                                system("cls");
                                goto bank;
                            }
                        }
                     break;
					}
					default: {
                    br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                    system("cls");
                    goto method;
					}
                }
            }
            else {
                system("cls");
            }
            break;
        }
        case 6: {
			    system("cls");
                br(2);pre(3);printf("Order cancelled\n");
                br(2);pre(3);system("pause");
                userprocess();
                break;
        }
        default: {
			    br(2);pre(3);printf("Invalid Entry, Please try again"); Sleep(400);
                system("cls");
                byfood();
        }
        }
    }
}

/* CUSTOMER SECTION
   Order Process of By Food Menu
*/
void get_time(char Curr_time[]){
	time_t rawtime = time(0);
	struct tm * t;
	t = localtime(&rawtime);
	sprintf(Curr_time,"%02d-%02d-%d, %02d:%02d:%02d",t->tm_mday,t->tm_mon+1,t->tm_year+1900,t->tm_hour,t->tm_min,t->tm_sec);
}

void display_order(orderlist *t) {
	int i=1;
    orderproduct *q;
    if(t->start == NULL){
        br(2);pre(3);printf("No orders yet");
        return;
    }
    q = t->start;
    while(q!= NULL){
        br(1);pre(2);printf("%d. %-20s | %5.2f * %d Quantity = %5.2f Pesos\n",i++,q->name,q->price,q->quantity,q->quantity*q->price);
        q = q->next;
    }
    br(2);pre(4);printf("Current Total = %2.lf Pesos\n",t->total);
}

void rank(menu *m,char a[],int n){
	product *q;
	q = m->start;
	while(strcmp(q->name,a) != 0)
		q = q->next;
	q->rank += n;
}

void add_order(menu *m,orderlist *ol,int i,int n){
	orderproduct *x;
	product *q = m->start;
	x = (orderproduct*)malloc(sizeof(orderproduct));
	x->next = NULL;
	for(int j=0;j < i-1&& q != NULL;j++)
        q = q->next;
	if(i <= 0|| q == NULL){
		br(2);pre(3);printf("Invalid Choice!");
		return;
	}
	strcpy(x->name,q->name);
	x->price = q->price;
	x->quantity = n;
	if(ol->start == NULL){
		ol->start = ol->last = x;
		x->prev = NULL;
	}
	else{
		ol->last->next = x;
		x->prev = ol->last;
		ol->last = x;
	}
	ol->total += (x->price*x->quantity);
	rank(m,q->name,n);
}

void order_quantity(menu *m,orderlist *ol,int i,int n){
	orderproduct *q = ol->start;
	for(int j=0;j < i-1&& q != NULL;j++)
        q = q->next;
	if(i <= 0|| q == NULL){
		br(2);pre(3);printf("Invalid Choice!");
		return;
	}
	ol->total += q->price*(n - q->quantity);
	rank(m,q->name,n - q->quantity);
 	q->quantity = n;
}

void remove_order(menu *m,orderlist *ol,int i){
	product *p = m->start;
	orderproduct *q = ol->start;
	for(int j=0;j < i-1&& q != NULL;j++)
        q = q->next;
	if(i <= 0|| q == NULL) {
		br(2);pre(3);printf("Invalid Choice!");
		return;
	}
	if(q == ol->start && q == ol->last)
		ol->start = ol->last = NULL;
	else if(q == ol->start){
		ol->start = ol->start->next;
		ol->start->prev = NULL;
	}
		else if(q == ol->last){
			ol->last = ol->last->prev;
			ol->last->next = NULL;
		}
			else{
				q->prev->next = q->next;
				q->next->prev = q->prev;
			}
	ol->total -= (q->price*q->quantity);
	rank(m,q->name,-1*q->quantity);
	free(q);
}

void print(orderlist *ol){
	int i=1,k=1, charge=45;
	FILE *forder;
	char now[25],orderID[15];
	orderproduct *q = ol->start;
	forder = fopen("order.txt","w");
	if(forder == NULL){
		printf("cannot open file\n");
		exit(3);
	}
	get_time(now);
	br(2);pre(4);printf("==========================");
	br(1);pre(5);printf("YOUR ORDER");
	br(1);pre(4);printf("==========================");
	while(q != NULL){
		fprintf(forder,"%d. %-20s  | %5.2f * %d Quantity = %5.2f Pesos\n\n",i++,q->name,q->price,q->quantity,(q->price*q->quantity));
		q = q->next;
	}
	orderID[0] = 'O';
	for(i=0;i<strlen(now);i++)
		if(now[i] >= '0' && now[i] <= '9')
			orderID[k++] = now[i];
	orderID[k] = '\0';
	fprintf(forder,"Order NO: %s\n",orderID);
	br(2);pre(2);printf("Order NO : %s\n",orderID);
	display_order(ol);
	br(1);pre(1);printf("======================================================================\n\n");
	fprintf(forder,"Total Bill= %2.lf Pesos\n",ol->total+charge);
	br(1);pre(3);printf("Total = %2.lf Pesos\t\t\t%s\n",ol->total+charge,now);
	fclose(forder);
}
