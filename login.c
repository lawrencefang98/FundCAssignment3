/******************************************************************************
 *                               HEADER FILES                                 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

int main()
{
    loginMenu();
}

_Noreturn void loginMenu()
{
    user_t accounts[MAX_CLINIC_SZ + 1] = {0};

    int choice = 0;

    int total = 0;
    int* total_p = &total;

    printMenu();
    scanf("%d", &choice);

    while(1)
    {
        if (choice == 1)
        {
            loginUser();
            printMenu();
            scanf("%d", &choice);
        }

        else if (choice == 2)
        {
            addUser(accounts, total_p);
            printMenu();
            scanf("%d", &choice);
        }

        else if (choice == 3)
        {

        }

    }

}

void printMenu()
{
    puts("\n                LOGIN MENU                ");
    puts("------------------------------------------");
    puts("Please choose from the following options: ");
    printf("1. Login to an existing account\n");
    printf("2. Create an account\n");
    printf("3. Delete an account\n");
    printf("4. Modify an account\n\n");
    printf("LOGIN MENU | Enter your choice: ");
}

/* Exceeding password length */

void addUser(user_t accounts[], int* total_p)
{
    int i = *total_p;

    if(i <= MAX_CLINIC_SZ)
    {
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                           USER DATA: ID
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        printf("\nADD USER | Enter your employee ID: ");
        scanf("%10s", accounts[i].userID);

        while(checkCharNum(accounts[i].password) == 0)
        {
            printf("ERROR | You may only include numbers.");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%10s", accounts[i].userID);
        }

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                        USER DATA: PASSWORD
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        printf("ADD USER | Enter your password: ");
        scanf("%20s", accounts[i].password);

        while(checkChar(accounts[i].password) == 0)
        {
            printf("ERROR | You may only include alphanumeric characters");
            printf("ADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        while(checkSpace(accounts[i].password) == 1)
        {
            printf("ERROR | Your password must not contain spaces");
            printf("ADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        while(strlen(accounts[i].password) < MIN_PASS_LEN)
        {
            printf("\nERROR | Your password must be at least 10 characters.\n");
            printf("ADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        while(strlen(accounts[i].password) > MAX_PASS_LEN)
        {
            printf("\nERROR | Your password must not be greater than 20"
                   "characters.");
            printf("ADD USER | Enter your password: ");
            scanf("%s", accounts[i].password);
            break;
        }

        ++i;
    }

    else
    {
        printf("Maximum number of users reached.\n");

        --i;
    }

   /* printf("\nUser ID: %d\n", *accounts[0].userID);
      printf("Password: %s\n", accounts[0].password); */

    *total_p = i;

    saveUser(accounts, total_p);
}

void saveUser(user_t accounts[], int* total_p)
{
    FILE * file_p = fopen(LOGIN_DB,"a");

    if (file_p != NULL)
    {
        int i = 0;

        while(i <= *total_p && *accounts[i].userID != 0)
        {
            fprintf(file_p, "%8d %-20s\n",
                    *accounts[i].userID,
                    accounts[i].password);
            ++i;
        }
    }

    fclose(file_p);
}

int checkCharNum(const char password[])
{
    int i = 0;

    if(password[i] >= '0' && password[i] <= '9')
        return 1;

    else
        return 0;
}

int checkChar(const char password[])
{
    int i = 0;

    /* String only contains alphanumeric characters */
    if((password[i] >= 'A' && password[i] <= 'Z') ||
       (password[i] >= 'a' && password[i] <= 'z') ||
       (password[i] >= '0' && password[i] <= '9'))
    {
        return 1;
    }

    else
        return 0;
}

int checkSpace(const char password[])
{
    int i = 0;

    if(password[i] == ' ') /* String has a space */
        return 1;

    else
        return 0;  /* String doesn't have a space */
}

int checkUser(const char* user)
{
    FILE *file_p;

    char text_b[MAX_FILE_SZ] = {'\0'};

    const int userLen = strlen(user);

    if(userLen < 1) /* Empty user ID */
        return -1;

    if(userLen < ID_LEN) /* Input is less than min ID length */
        return -2;

    if(userLen > ID_LEN) /* Input is greater than max ID length */
        return -3;


    /* Read existing account information from file */
    file_p = fopen(LOGIN_DB, "r");

    if (file_p == NULL)
    {
        printf("ERROR | Read error.\n");
        EXIT_FAILURE;
    }

    else
    {
        while (fgets(text_b, MAX_FILE_SZ, file_p))
        {
            /* BUG - will only search first line of file */
            /*text_b[strcspn(text_b, "\n")] = 0;*/

            /* if(strcmp(text_b, user) != 0) */

            char* n = strchr(text_b, '\n');
                    if(n)
                        *n = '\0';

            char* point = strstr(text_b, user);

            if (point)
                return 1;

            else
                return 0;
        }
    }

    /* Error */
    return 2;
}

int checkPass(const char* pass)
{
    FILE *file_p;

    char text_b[MAX_FILE_SZ] = {'\0'};

    const int passLen = strlen(pass);

    if(passLen < 1) /* Empty password */
        return -1;

    if(passLen < MIN_PASS_LEN) /* Input is less than min pass length */
        return -2;

    if(passLen > MAX_PASS_LEN) /* Input is greater than max pass length */
        return -3;

    /* Read existing account information from file */
    file_p = fopen(LOGIN_DB, "r");

    if (file_p == NULL)
    {
        printf("ERROR | Read error.\n");
        EXIT_FAILURE;
    }

    else
    {
        while (fgets(text_b, MAX_FILE_SZ, file_p) && !(feof(file_p)))
        {
            text_b[strcspn(text_b, "\n")] = 0;
            char *point = strstr(text_b, pass);

            if (point)
                return 1;

            else
                return 0;
        }
    }

    /* Error */
    return 2;
}

void loginUser()
{
    char user[ID_LEN + 1];
    char pass[MAX_PASS_LEN + 1];

    printf("\nLOGIN | User ID: ");
    scanf("%10s", user);

    while (checkUser(user) == 0)
    {
        printf("ERROR | Incorrect user ID.");
        printf("\nLOGIN | User ID: ");
        scanf("%10s", user);
    }

    while (checkUser(user) == -1)
    {
        printf("ERROR | Empty user ID ");
        printf("\nLOGIN | User ID: ");
        scanf("%10s", user);
    }

    while (checkUser(user) == -2)
    {
        printf("ERROR | User ID must not be less than 8 characters.");
        printf("\nLOGIN | User ID: ");
        scanf("%10s", user);
    }

    while (checkUser(user) == -3)
    {
        printf("ERROR | User ID must not be greater than 8 characters.");
        printf("\nLOGIN | User ID: ");
        scanf("%10s", user);
    }

    printf("\nLOGIN | Password: ");
    scanf("%s", pass);

    while(checkPass(pass) == 0)
    {
        printf("ERROR | Incorrect password.");
        printf("\nLOGIN | Password: ");
        scanf("%s", pass);
    }

    while(checkPass(pass) == -1)
    {
        printf("ERROR | Empty password.");
        printf("\nLOGIN | Password: ");
        scanf("%s", pass);
    }

    while(checkPass(pass) == -2)
    {
        printf("ERROR | Password must be at least 8 characters long");
        printf("\nLOGIN | Password: ");
        scanf("%s", pass);
    }

    while(checkPass(pass) == -3)
    {
        printf("ERROR | Password must not be greater than 20 characters");
        printf("\nLOGIN | Password: ");
        scanf("%s", pass);
    }

    if(checkUser(user) == 1 && checkPass(pass) == 1)
    {
        printf("\n\nLOGIN SUCCESSFUL\n\n");

        /*securityMenu();*/
    }
}
