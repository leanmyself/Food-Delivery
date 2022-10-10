struct employee {
    int employee_id;
    char employee_name[50];
    char age[10];
    char sex[30];
    char location[30];
}lists;


void addemployee() {
    FILE *file;

    file = fopen("employeesrecord.txt", "a+");

    br(2);pre(3);printf("Enter Employee ID: ");Sleep(400);
    scanf("%d", &lists.employee_id);

    br(2);pre(3);printf("Enter Name: ");Sleep(400);
    fflush(stdin);
    gets(lists.employee_name);

    br(2);pre(3);printf("Enter Age: ");Sleep(400);
    scanf("%s", &lists.age);

    br(2);pre(3);printf("Enter Sex: ");Sleep(400);
    scanf("%s", &lists.sex);

    br(2);pre(3);printf("Enter Location: ");Sleep(400);
    fflush(stdin);
    gets(lists.location);

    fwrite(&lists, sizeof(lists), 1, file);

    fclose(file);

}

void employeelist() {

    FILE *file1;

    file1 = fopen("employeesrecord.txt", "r");br(2);
    pre(1);printf("=======================================================================");Sleep(400); br(1);
    pre(1);printf("ID\tName\t\t\tAge\tSex\t\tLocation\n");Sleep(400);
    pre(1);printf("=======================================================================");Sleep(400);
    br(1);
        while (fread(&lists, sizeof(lists), 1, file1)) {
            pre(1);printf("%d\t%s\t\t%s\t%s\t\t%s\n", lists.employee_id, lists.employee_name, lists.age, lists.sex, lists.location);
        }

    fclose(file1);

}

void searchemployee() {
    FILE *file2;

    int r, s, avl;
    br(2);
    pre(2);printf("Enter the Employee ID no you want to search: ");Sleep(400);
    scanf("%d", &r);

    avl = id(r);
        if (avl == 0) {
            br(2);
            pre(2);printf("Employee ID %d is not in the file\n",r);Sleep(400);
        }
        else {
            file2 = fopen("employeesrecord.txt", "r");
                while (fread(&lists, sizeof(lists), 1, file2)) {
                    s = lists.employee_id;
                        if (s == r) {
                            br(2);
                            pre(1);printf("====================================================================");br(1);
                            pre(1);printf("ID\tName\t\t\tAge\tSex\t\tLocation\n");Sleep(400);
                            pre(1);printf("====================================================================");br(1);
                            br(2);pre(1);printf("%d\t%s\t\t%s\t%s\t\t%s\n\n\n", lists.employee_id, lists.employee_name, lists.age, lists.sex, lists.location);Sleep(400);
                    }
                }
            fclose(file2);
        }
}

void deleteemployee() {

    FILE *fpo;
    FILE *fpt;

    int r, s;
        br(2);
        pre(2);printf("Enter Employee ID you want to delete :");Sleep(400);
        scanf("%d", &r);

    if (id(r) == 0) {
        br(2);
        pre(3);printf("Employee ID %d is not available in the file\n", r);Sleep(400);
    }
    else {
        fpo = fopen("employeesrecord.txt", "r");
        fpt = fopen("Temp.txt", "w");
            while (fread(&lists, sizeof(lists), 1, fpo)){
                s = lists.employee_id;
                    if (s != r)
                        fwrite(&lists, sizeof(lists), 1, fpt);
            }

        fclose(fpo);
        fclose(fpt);

        fpo = fopen("employeesrecord.txt", "w");
        fpt = fopen("Temp.txt", "r");

            while (fread(&lists, sizeof(lists), 1, fpt))
                fwrite(&lists, sizeof(lists), 1, fpo);
                br(2);
                pre(3);printf("Employee ID Deleted\n");Sleep(400);

        fclose(fpo);
        fclose(fpt);
 }

}

int id(int rno){
    FILE *file;
    int c = 0;
    file = fopen("employeesrecord.txt", "r");
        while (!feof(file))
        {
            fread(&lists, sizeof(lists), 1, file);

                if (rno == lists.employee_id){
                    fclose(file);
                    return 1;
                }
        }

    fclose(file);
    return 0;
}
