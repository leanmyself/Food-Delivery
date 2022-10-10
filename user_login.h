typedef struct {
    char username[50];
    char password[50];
    char mobilenumber[20];
    char age[20];
} user;

user list[USER_MAX];

char* filename = "accounts.txt";
FILE *file;
user u;
int i;


user login() {

    char name[50];
    char password[50];

    br(2);pre(4);printf("===========================");
    br(1);pre(4);echo(" Welcome to Log in Section");Sleep(400);
    br(1);pre(4);printf("===========================");

    br(3);pre(4);echo("Enter username: ");Sleep(400);
    scanf("%s",name);
    strcpy(u.username , name);

    br(2);pre(4);echo("Enter password: ");Sleep(400);
    int p=0;
        do{
            password[p]=getch();
                if(password[p]!='\r'){
                    printf("*");
                }
            p++;
        }while(password[p-1]!='\r');

        password[p-1]='\0';
    strcpy(u.password,password);

    return u;
}

int registration() {

    char name[50];
    char password[50];
    char mobilenumber[20];
    char age[20];

    br(1);pre(4);printf("===============================");
    br(1);pre(4);echo("Welcome to Registration Section");Sleep(400);
    br(1);pre(4);printf("===============================");

    br(3);pre(4);echo("Enter username:");Sleep(400);
    scanf("%s",name);
    strcpy(u.username , name);

    // determine whether there has been a registered user
    for(i=0; i<USER_MAX; i++)
    {
        if(0==strcmp(list[i].username ,name))
        {
            br(2);pre(4);echo("Username already exists"); Sleep(600);
            system("cls");
            registration();
        }
    }

    br(2);pre(4);echo("Enter password:");Sleep(400);
    int p=0;
        do{
            password[p]=getch();
                if(password[p]!='\r'){
                    printf("*");
                }
            p++;
        }while(password[p-1]!='\r');

        password[p-1]='\0';
    strcpy(u.password , password);

    br(3);pre(4);echo("Enter mobile number:");Sleep(400);
    scanf("%s",mobilenumber);
    strcpy(u.mobilenumber , mobilenumber);

    br(2);pre(4);echo("Enter your age:");Sleep(400);
    scanf("%s",age);
    strcpy(u.age , age);

    writefile(u);
    br(2);pre(4);echo("Press Enter if you agree");
        if(getch()==13){
            system("cls");
            br(3);pre(3);echo("You are now registered");Sleep(400);
            br(2);pre(3);echo("Now Login with your username and password");Sleep(400);
            userlogin();
        }
    return 0;
}

void writefile(user u) {
    FILE *file = fopen(filename,"a");
    fprintf(file,u.username);
    fprintf(file,"\t");
    fprintf(file,u.password);
    fprintf(file,"\t");
    fprintf(file,u.mobilenumber);
    fprintf(file,"\t");
    fprintf(file,u.age);
    fprintf(file,"\n");

    fclose(file);
}

// determine whether the user exists
int exist(user u){
    for(i=0; i<USER_MAX; i++)
    {
        if(0==strcmp(list[i].username ,u.username) && 0==strcmp(list[i].password ,u.password))
        {
            return 1;
        }
    }
    return -1;
}


int choicemenu(){
    system("cls");
    int choice;

    br(3); pre(3); echo("1. Already have an account?"); Sleep(400);
	br(3); pre(3); echo("2. Register"); Sleep(400);
	br(3); pre(3); echo("3. Cancel"); Sleep(400);

    br(3);pre(3);printf("Enter your choice: ");
    scanf("%d",&choice);

    return choice;
}


int userlogin(){
    user test[USER_MAX];
    FILE *file = fopen(filename,"r");
    int i=0;

    if(NULL == file){
        br(2);pre(3);echo("File Not Found, Please Create the text file for accounts");
        return -1;
    }
    for(i=0; i<USER_MAX; i++){
        char uname[50];
        char upassword[50];

        fscanf(file,"%s%s",uname,upassword);

        strcpy(list[i].username , uname);
        strcpy(list[i].password , upassword);
    }

    int choice = choicemenu();

    if(choice == 1){
        system("cls");
        u=login();

        if(1 == exist(u)){
            system("cls");
            br(3);pre(3);echo("You have been log in successfully"); Sleep(800);
            br(2);pre(3);system("pause");
            userprocess();

        }
        else
        {
            br(2);pre(4);echo("You inputted wrong password"); Sleep(400);
            br(1);pre(4);echo("Please Try again"); Sleep(400);
            userlogin();
        }

    }
    else if(choice == 2){
        system("cls");
        registration();

    }
    else if(choice == 3){
        system("cls");
        second();

    }
    else{
        br(3);pre(3);echo("Incorrect Key"); Sleep(400);
		br(3);pre(3);echo("Press Enter to re-Enter the choice"); Sleep(400);

		if(getch()==13)
		system("cls");
		choicemenu();
    }
    return 0;
}
