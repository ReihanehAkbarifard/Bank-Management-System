#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
FILE *fp2;
FILE *fp3;
FILE *fp4;

struct Person
{

    char first_name[20];
    char last_name[50];
    int national_code;
    int primary_key;
};

struct Employee
{

    int primary_key;
    int person_key;
    int employee_key;
    char position[50];
    struct Person pr;
};

struct Customer
{

    int primary_key;
    int person_key;
    struct Person pr;
};

struct Account
{

    struct Customer cus;
    int account_number;
    char type[30];
    int value;
    int acc_key ;
    int flag_loan ;
    int value_loan;
};

struct Accounts_customer
{

    struct Account acc;
    int account_number;
    int customer_key;
    int primary_key;
};

struct Transaction
{

    int account_number;
    int year;
    int month;
    int day;
    int value;
    int person_key;
};

int findeAccount(struct Account *p_acc)
{

    int account_number;
    puts("Enter the account_number :");
    scanf("%d", &account_number);
    struct Account acc;
    fseek(fp2, 0, SEEK_SET);
    while (fread(&acc, sizeof(struct Account), 1, fp2))
    {
        if (acc.account_number != account_number)
            continue;
        *p_acc = acc;
        return 1;
    }
    return 0;
}

void findeCustomerInFile(struct Customer *p_cus,int acc_key)
{

   
    struct Customer cus;
    fseek(fp3, 0, SEEK_SET);
    while (fread(&cus, sizeof(struct Customer), 1, fp))
    {
        if (cus.person_key != acc_key)
            continue;
        *p_cus = cus;
    }
}

void findeTraInFile(struct Transaction *p_tra,int acc_key)
{

   
    struct Transaction tra;
    fseek(fp4, 0, SEEK_SET);
    while (fread(&tra, sizeof(struct Transaction), 1, fp4))
    {
        if (tra.person_key != acc_key)
            continue;
        *p_tra = tra;
    }
}

void show_transaction(){
    struct Transaction tra;
    struct Account acc;
    struct Customer cus;
    int res = findeAccount(&acc);
    if (!res)
        puts("Account cannot be found!");
    else{
        fseek(fp3, 0, SEEK_SET);
        fread(&cus, sizeof(struct Customer), 1, fp3);
        findeCustomerInFile(&cus,acc.acc_key);
        fseek(fp4, 0, SEEK_SET);
        fread(&tra, sizeof(struct Transaction), 1, fp4);
        findeTraInFile(&tra,tra.person_key);
        printf("This is an account with %d account_number\n", acc.account_number);
        printf("Day : %d , Month : %d , Year : %d", tra.day,tra.month,tra.year);
        printf("Balance : %d\n" ,acc.value);
        printf("Type : %s\n",acc.type);
        printf("belong to : %s %s\n",cus.pr.first_name, cus.pr.last_name);
        printf("national code : %d\n", cus.pr.national_code);
    }
} 





void Search_Account()
{

    struct Account acc;
    struct Customer cus;
    int res = findeAccount(&acc);
    if (!res)
        puts("Account cannot be found!");
    else{
        fseek(fp3, 0, SEEK_SET);
        fread(&cus, sizeof(struct Customer), 1, fp3);
        findeCustomerInFile(&cus,acc.acc_key);
        printf("This is an account with %d account_number\n", acc.account_number);
        printf("Balance : %d\n" ,acc.value);
        printf("Type : %s\n",acc.type);
        printf("belong to : %s %s\n",cus.pr.first_name, cus.pr.last_name);
        printf("national code : %d\n", cus.pr.national_code);
    }
    system("pause");
}

void loan(){
    struct Account acc;
    int account_number;
    int value;
    int loan;

    int res = findeAccount(&acc);
    if (!res)
        puts("Account cannot be found!");
    
    else{
        puts("How much loan do You want?");
        puts("**The interest rate on the loan is 18%**");
        scanf("%d",loan);

        if (0.18 * loan > acc.value){
            puts("Your account balance is not enough!");
        }
        else{
            acc.value_loan = loan;
            acc.value += loan;
            acc.flag_loan = 1;
            puts("The loan was successfully completed");
            printf("Your new balance is %d\n",acc.value);
        }
        fseek(fp2, -sizeof(struct Account), SEEK_CUR);
        fwrite(&acc, sizeof(struct Account), 1, fp2);
    }   
    


}


int findecustomer(struct Customer *p_cus)
{

    int national_code;
    puts("Enter the national_code :");
    scanf("%d", &national_code);
    struct Customer cus;
    fseek(fp3, 0, SEEK_SET);
    while (fread(&cus, sizeof(struct Customer), 1, fp3))
    {
        if (cus.pr.national_code != national_code)
            continue;
        *p_cus = cus;
        return 1;
    }
    return 0;
}

void Search_Customer()
{

    struct Customer cus;
    int res = findecustomer(&cus);
    if (!res)
        puts("Customer cannot be found!");
    else{
        printf("%s %s \nwith %d nationall code .\n", cus.pr.first_name, cus.pr.last_name, cus.pr.national_code);
    }
    system("pause");
}

void pay_money(){

    struct Account acc;
    struct Transaction tra;
    
    int account_number;
    int value;
    int loan = acc.value_loan;
    int res = findeAccount(&acc);
    if (!res)
        puts("Account cannot be found!");
    else{
        puts("How much money you want to pay?");
        scanf("%d", &value);
        

        if (value > acc.value)
            puts("Your account balance is not enough!");
        else if(acc.flag_loan == 1 && acc.value - value > loan/12 ){
            puts("You cant do this transaction because of your Bank installment!");
        }
        else{
            acc.value -= value;
            puts("What day is today?");

            scanf("Day : %d , Month : %d , Year : %d", tra.day,tra.month,tra.year);
            tra.value = value;
            tra.account_number = account_number;

            printf("Your new balance is %d\n",acc.value);
            fseek(fp4, 0, SEEK_END);
            fwrite(&tra, sizeof(struct Transaction), 1, fp4);
        }
        fseek(fp2, -sizeof(struct Account), SEEK_CUR);
        fwrite(&acc, sizeof(struct Account), 1, fp2);
       
    }
    
    system("cls");
       
}

void transaction(){
    struct Account acc1;
    struct Account acc2;
    int account_number1;
    int account_number2;
    int value;
    int loan = acc1.value_loan;
    int res1 = findeAccount(&acc1);
    int res2 = findeAccount(&acc2);

    if (!res1 && !res2)
        puts("Account cannot be found!");

    else if(acc1.flag_loan == 1 && acc1.value - value > loan/12 ){
            puts("You cant do this transaction because of your Bank installment!");
    }

    else{
        puts("How much money you want to pay?");
        scanf("%d", &value);

        if (value > acc1.value)
            puts("Your account balance is not enough!");

        else{
            acc1.value -= value;
            acc2.value += value;
            puts("transfer completed successfully.");
            printf("Your new balance is %d\n",acc1.value);
            fseek(fp2, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc1, sizeof(struct Account), 1, fp2);
            fseek(fp2, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc2, sizeof(struct Account), 1, fp2);
        }
        
        
    }
}

void Add_Account(){

    struct Account acc;
    int number;

    puts("How many people you want to creat an account for?");
    scanf("%d", &number);
    if (number == 1)
    {
        puts("please enter his/her person_key :");
        int person_key;
        scanf("%d", &person_key);
        puts("please enter his/her account_number :");
        scanf("%d", &acc.account_number);
        puts("please enter his/her type :");
        scanf("%s", &acc.type);
        puts("please enter his/her value :");
        scanf("%d", &acc.value);
        printf("\n");
        acc.cus.primary_key = acc.account_number;
        acc.acc_key = acc.cus.person_key;
        acc.flag_loan = 0;
        puts("***Account created successfully***");
        
        fseek(fp2, 0, SEEK_END);
        fwrite(&acc, sizeof(struct Account), 1, fp2);
        system("cls");
    }
    else
    {
        for (int i = 0; i < number; i++)
        {
            puts("please enter his/her person_key ");
            int person_key;
            scanf("%d", &person_key);
        }
    }
}


void Edit_CustomerName()
{
    struct Customer cus;
    int res = findecustomer(&cus);
    if (!res)
        puts("Customer cannot be found!");
    else
    {
        puts("enter the new Customer firstname :");
        char c;
        scanf("%c%[^\n]%c", &c, cus.pr.first_name, &c);
        puts("Person enter the new lastname :");
        scanf("%c%[^\n]%c", &c, cus.pr.last_name, &c);
        fseek(fp3, -sizeof(struct Customer), SEEK_CUR);
        fwrite(&cus, sizeof(struct Customer), 1, fp3);
    }
}

void Show_Accounts()
{

    struct Account acc;
    struct Customer cus;
    fseek(fp2, 0, SEEK_SET);
    long pos = ftell(fp2);
    fseek(fp2, 0, SEEK_END);
    long posEnd = ftell(fp2);
    printf("%d Accounts\n", (posEnd - pos) / sizeof(struct Account));

    fseek(fp2, 0, SEEK_SET);
    int res;
    while (res = fread(&acc, sizeof(struct Account), 1, fp2)){
        fseek(fp3, 0, SEEK_SET);
        fread(&cus, sizeof(struct Customer), 1, fp3);
        findeCustomerInFile(&cus,acc.acc_key);
        printf("This is an account with %d account_number\n", acc.account_number);
        printf("Balance : %d\n" ,acc.value);
        printf("Type : %s\n",acc.type);
        printf("belong to : %s %s\n",cus.pr.first_name, cus.pr.last_name);
        printf("national code : %d\n", cus.pr.national_code);
    }
    
    system("pause");
}

void Add_Employee()
{

    struct Employee emp;
    puts("please Enter Person name :");
    scanf("%s", emp.pr.first_name);
    puts("please Enter Person last name :");
    scanf("%s", emp.pr.last_name);
    puts("please Enter Person national_code :");
    scanf("%d", &emp.pr.national_code);
    puts("please Enter Person primary_key :");
    scanf("%d", &emp.pr.primary_key);
    puts("please Enter Employee primary_key :");
    scanf("%d", &emp.primary_key);
    puts("please Enter Employee employee_key :");
    scanf("%d", &emp.employee_key);
    puts("please Enter Employee position :");
    scanf("%s", emp.position);

    emp.pr.primary_key = emp.person_key;

    puts("Employee added successfully");
    fseek(fp, 0, SEEK_END);
    fwrite(&emp, sizeof(struct Employee), 1, fp);
}
void prnemp(struct Employee emp)
{
    printf("%s %s \n", emp.pr.first_name, emp.pr.last_name);
    printf("nationall code : %d \n", emp.pr.national_code);
    printf("employee key : %d \n", emp.employee_key);
    printf("emp.position : %s \n", emp.position);
}
void Show_Employees()
{

    struct Employee emp;

    fseek(fp, 0, SEEK_SET);
    long pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long posEnd = ftell(fp);
    printf("%d Employee\n", (posEnd - pos) / sizeof(struct Employee));

    fseek(fp, 0, SEEK_SET);
    int res;\
    while (res = fread(&emp, sizeof(struct Employee), 1, fp))
    {
        prnemp(emp);
    }
    system("pause");
}

int findemployee(struct Employee *p_emp)
{

    int employee_key;
    puts("Enter the national_code :");
    scanf("%d", &employee_key);
    struct Employee emp;
    fseek(fp, 0, SEEK_SET);
    while (fread(&emp, sizeof(struct Employee), 1, fp))
    {
        if (emp.employee_key != employee_key)
            continue;
        *p_emp = emp;
        return 1;
    }
    return 0;
}

void Search_Employee()
{

    struct Employee emp;
    int res = findemployee(&emp);
    if (!res)
        puts("Employee cannot be found!");
    else{

        printf("%s %s \n", emp.pr.first_name, emp.pr.last_name);
        printf("nationall code : %d \n", emp.pr.national_code);
        printf("employee key : %d \n", emp.employee_key);
        printf("emp.position : %s \n", emp.position);
    }
        
    system("pause");
}

void Edit_EmployeeName()
{
    struct Employee emp;
    int res = findemployee(&emp);
    if (!res)
        puts("Employee cannot be found!");
    else
    {
        puts("enter the new Employee firstname");
        char c;
        scanf("%c%[^\n]%c", &c, emp.pr.first_name, &c);
        puts("Person enter the new lastname");
        scanf("%c%[^\n]%c", &c, emp.pr.last_name, &c);
        fseek(fp, -sizeof(struct Employee), SEEK_CUR);
        fwrite(&emp, sizeof(struct Employee), 1, fp);
    }
}

int menu_admin()
{

    puts("Hi ! What do you want to do ?");

    puts("0 : Exit");
    puts("1 : Add_Employee");
    puts("2 : Show_Employees");
    puts("3 : Search_Employee");
    puts("4 : Edit_EmployeeName");

    int opt;
    scanf("%d", &opt);
    return opt;
}

void Add_Customer()
{

    struct Customer cus;
    puts("please Enter Person name :");
    scanf("%s", cus.pr.first_name);
    puts("please Enter Person last name :");
    scanf("%s", cus.pr.last_name);
    puts("please Enter Person national_code :");
    scanf("%d", &cus.pr.national_code);
    puts("please Enter Person primary_key :");
    scanf("%d", &cus.pr.primary_key);
    puts("please Enter Customer primary_key :");
    scanf("%d", &cus.primary_key);

    cus.pr.primary_key = cus.person_key;

    puts("Customer added successfully");
    
    fseek(fp3, 0, SEEK_END);
    fwrite(&cus, sizeof(struct Customer), 1, fp3);
}
void prncus(struct Customer cus)
{

    printf("%s %s \n", cus.pr.first_name, cus.pr.last_name);
    printf("nationall code : %d \n", cus.pr.national_code);
}
void Show_Customers()
{

    struct Customer cus;

    fseek(fp3, 0, SEEK_SET);
    long pos = ftell(fp3);
    fseek(fp3, 0, SEEK_END);
    long posEnd = ftell(fp3);
    printf("%d Customers\n", (posEnd - pos) / sizeof(struct Customer));

    fseek(fp3, 0, SEEK_SET);
    int res;
    while (res = fread(&cus, sizeof(struct Customer), 1, fp3))
    {
        prncus(cus);
    }

    system("pause");
}


int menu_employee()
{

    puts("Hi ! What do you want to do ?");

    puts("0 : Exit");
    puts("1 : Add_Customer");
    puts("2 : Show_Customers");
    puts("3 : Add_Account");
    puts("4 : Show_Accounts");
    puts("5 : Search_Customer");
    puts("6 : Edit_CustomerName");
    puts("7 : Withdrawal_from_customer_account");
    puts("8 : Deposit_to_customer_account");

    int opt;
    scanf("%d", &opt);
    return opt;
}

void Show_my_Account()
{

    Search_Account();
}

int menu_customer()
{

    puts("Hi ! What do you want to do ?");

    puts("0 : Exit");
    puts("1 : Show_my_Accont");
    puts("2 : pay_money");
    puts("3 : transaction");
    puts("4 : get_loan");
    puts("4 : show_transaction");


    int opt;
    scanf("%d", &opt);
    return opt;
}

void act_admin(int opt)
{
    switch (opt){

    case 1:
        Add_Employee();
        break;
    case 2:
        Show_Employees();
        break;
    case 3:
        Search_Employee();
        break;
    case 4:
        Edit_EmployeeName();
        break;
    }
}
void Withdrawal_from_customer_account(){

    struct Account acc;
    int account_number;
    int value;
    
    int res = findeAccount(&acc);
    if (!res)
        puts("Account cannot be found!");
    else{
        puts("How much money Customer wants to pay?");
        scanf("%d", &value);
        
        if (value > acc.value)
            puts("Customer account balance is not enough!");
        else{
            acc.value -= value;
            printf("Customer account new balance is %d\n",acc.value);
        }
        fseek(fp2, -sizeof(struct Account), SEEK_CUR);
        fwrite(&acc, sizeof(struct Account), 1, fp2);
       
    }
    
    system("cls");
}

void Deposit_to_customer_account(){

    struct Account acc;
    int account_number;
    int value;
    
    int res = findeAccount(&acc);
    if (!res)
        puts("Account cannot be found!");
    else{
        puts("How much money will be deposited in the customer's account?");
        scanf("%d", &value);
        
            acc.value += value;
            printf("Customer account new balance is %d\n",acc.value);
        
        fseek(fp2, -sizeof(struct Account), SEEK_CUR);
        fwrite(&acc, sizeof(struct Account), 1, fp2);
       
    }
    
    system("cls");
}

void act_employee(int opt)
{

    switch (opt)
    {
    case 1:
        Add_Customer();
        break;
    case 2:
        Show_Customers();
        break;
    case 3:
        Add_Account();
        break;
    case 4:
        Show_Accounts();
        break;
    case 5:
        Search_Customer();
        break;
    case 6:
        Edit_CustomerName();
        break;
    case 7:
        Withdrawal_from_customer_account();
        break;
    case 8:
        Deposit_to_customer_account();
        break;
    case 9:
        show_transaction();
    }
}

void act_customer(int opt)
{
    switch (opt)
    {
    case 1:
        Show_my_Account();
        break;
    case 2:
        pay_money();
        break;
    case 3:
        transaction();
        break;
    case 4:
        loan();
        break;
    }
}

void welcome()
{

    system("COLOR 2");
    printf("\t\t\t%s\n", "          ====================================================================  ");
    printf("\t\t\t%s\n", "                         *********************************                      ");
    printf("\t\t\t%s\n", "                         =================================                      ");
    printf("\t\t\t%s\n", "                         *********************************                      ");
    printf("\t\t\t%s\n", "                         ^         WELCOME TO            *                      ");
    printf("\t\t\t%s\n", "                         ^                               *                      ");
    printf("\t\t\t%s\n", "                         ^        REYHOON BANK           *                      ");
    printf("\t\t\t%s\n", "                         ^                               *                      ");
    printf("\t\t\t%s\n", "                         >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                      ");
    printf("\t\t\t%s\n", "           ==================================================================   ");
    printf("%s\n", "\n\n\n\n\t\t                                    Enter any key to continue.....");
    getchar();
}

int login()
{

    while (1)
    {
        int choice;

        puts("Tell me who are you?");
        puts("-------------------------");
        puts("1. I am Admin");
        puts("2. I am Employee");
        puts("3. I am Customer");

        scanf("%d", &choice);
        system("cls");
        if (choice == 1)
        {
            int password;

            while (1)
            {
                puts("Please enter your password :");
                scanf("%d", &password);
                if (password == 1234)
                {
                    system("cls");
                    int opt1 = menu_admin();
                    if (opt1 == 0)
                        return 0;
                    act_admin(opt1);
                }
                else
                {
                    puts("Your password is incorrect , try another password.");
                }
            }
        }
        else if (choice == 2)
        {
            int opt2 = menu_employee();
            if (opt2 == 0)
                return 0;
            act_employee(opt2);
        }
        else if (choice == 3)
        {
            int opt3 = menu_customer();
            if (opt3 == 0)
                return 0;
            act_customer(opt3);
        }
       
    }
}

int main()
{

    system("cls");

    fp = fopen("Employee.in", "w+");
    fp2 = fopen("Account.in", "a+");
    fp3 = fopen("Customer.in", "a+");
    fp4 = fopen("Transaction.in", "a+");
    welcome();
    system("cls");
    login();
}