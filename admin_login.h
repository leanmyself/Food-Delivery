void loginadmin() {

    FILE * fpass;
    FILE * fp;
xy:
    fpass = fopen("F:\data.txt","r");

    char password[20],user[20],usercont[20],passcont[20], ch;
    int choice;

        if(fpass == NULL){
            br(5);pre(3);printf(" PLEASE ENTER FLASHDRIVE ");
            system("cls");
            goto xy;
        }
    fclose(fpass);
ab:
    system("cls");
    br(2);pre(4);printf("==========================");
    br(1);pre(4);echo(" Welcome to Admin Section");Sleep(400);
    br(1);pre(4);printf("==========================");

    br(4);pre(4);echo("Enter username: ");
    scanf("%s",&user);

    br(2);pre(4);echo("Enter password: ");
    int p=0;
        do{
            password[p]=getch();
                if(password[p]!='\r'){
                    printf("*");
                }
            p++;
        }while(password[p-1]!='\r');

        password[p-1]='\0';

    fpass = fopen("F:\data.txt","r");
    fscanf(fpass,"%s",usercont);
    fscanf(fpass,"%s",passcont);
    fclose(fpass);

        if(strcmp(user,usercont)==0 && strcmp(password,passcont)==0){
            system("cls");
            adminmenu();
            goto ab;
        }
        else{
            br(2);pre(4);echo("You inputted wrong password"); Sleep(400);
            br(1);pre(4);echo("Please Try again"); Sleep(400);
            goto ab;
}
return 0;
}






