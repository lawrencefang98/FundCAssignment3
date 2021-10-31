/******************************************************************************
 *                               HEADER GUARDS                                *
 ******************************************************************************/

#ifndef FUNDCASSIGNMENT3_LOGIN_H 
#define FUNDCASSIGNMENT3_LOGIN_H

/******************************************************************************
 *                               HEADER FILES                                 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

/******************************************************************************
 *                          PREPROCESSOR DIRECTIVES                           *
 ******************************************************************************/

#define MAX_FILE_NAME 30
#define LOGIN_DB "login_database.txt"

#define MAX_PASS_LEN 20
#define MIN_PASS_LEN 8

#define ID_LEN 8
#define MAX_USERS 100
#define BUF_SIZE 4096

/******************************************************************************
 *                                 STRUCTURES                                 *
 ******************************************************************************/

typedef struct user {
    char username[ID_LEN + 1];
    char password[MAX_PASS_LEN + 1];
} user_t;

/******************************************************************************
 *                            FUNCTION PROTOTYPES                             *
 ******************************************************************************/

/* User Menu */
void loginMenu();
void printMenu();

/* Menu Options */
void loginUser(int* total_p);
void addUser(user_t accounts[], int* total_p);
void saveUser(user_t accounts[], int* total_p);

/* Debug Check */
int checkChar(const char password[]);
int checkNum(const char username[]);

/* Login Check */
int validCred(const char credentials[]);

/******************************************************************************
 *                                FUNCTIONS                                   *
 ******************************************************************************/

/******************************************************************************
 *  AUTHOR: Mandana Ebrahimian
 *  FUNCTION: loginMenu()          PURPOSE: Executes the relevant functions
 *                                          based on user input.
 *
 *  INPUT: N/A
 *  OUTPUT: N/A
 *****************************************************************************/

void loginMenu()
{
    user_t accounts[MAX_USERS + 1] = {0};

    int choice = 0;

    int total = 0;
    int* total_p = &total;

    printMenu();
    scanf("%d", &choice);

    while(1)
    {
        if (choice == 1)
        {
            loginUser(total_p);
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
            return;
        }

        else
        {
            printf("\nERROR | Invalid menu choice. Please try again.\n");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
        }
    }
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: printMenu()          PURPOSE:  Prints the login menu
 *
 * INPUT: N/A
 * OUTPUT: N/A
 *****************************************************************************/

void printMenu()
{
    printf("\n                    LOGIN MENU                    ");
    printf("\n--------------------------------------------------");
    printf("\nPlease choose from the following options: ");
    printf("\n  1. Login to an account");
    printf("\n  2. Create an account");
    printf("\n  3. Exit the program");
    printf("\nLOGIN MENU | Enter your choice: ");
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: addUser()         PURPOSE: Collect username and password
 *
 * INPUT: accounts[], total_p
 * OUTPUT: saves new user to file with saveUser()
 *****************************************************************************/

void addUser(user_t accounts[], int* total_p)
{
    /* Ignores spaces */
    char space;

    /* 'i' acts as a placeholder for *total_p */
    int i = *total_p;

    printf("\n\n");

    printf("\n                CREATE AN ACCOUNT                ");
    printf("\n--------------------------------------------------");

    /* Total users must not exceed the maximum clinic size */
    if(i <= MAX_USERS)
    {
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                           USER DATA: ID                           *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        /* Debug: User already exists */
        printf("\nADD USER | Enter your employee ID: ");
        scanf("%c", &space); /* Reads all text (including spaces) */
        scanf("%[^\n]", accounts[i].username);

        while(validCred(accounts[i].username) > 0)
        {
            printf("\nERROR | Account already exists.\n");
            return;
        }

        /* Debug: Username may only include numeric characters */
        while(checkNum(accounts[i].username) == 0)
        {
            printf("ERROR | Your ID can only include numeric characters.\n");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].username);
        }

        while(strlen(accounts[i].username) > ID_LEN)
        {
            printf("ERROR | Your ID must not exceed 8 chars.\n");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].username);
        }

        while(strlen(accounts[i].username) < ID_LEN)
        {
            printf("ERROR | Your ID must not be less than 8 chars.\n");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].username);
        }

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                        USER DATA: PASSWORD                        *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        printf("ADD USER | Enter your password: ");
        scanf("%c", &space); /* Reads all text (including spaces) */
        scanf("%[^\n]", accounts[i].password);

        /* Debug: User will be prompted to enter pass > or == min characters */
        while(strlen(accounts[i].password) < MIN_PASS_LEN)
        {
            printf("\nERROR | Your password must be at least 8 characters.\n");
            printf("ADD USER | Enter your password: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].password);
        }

        /* Debug: User will be prompted to enter pass > max characters */
        while(strlen(accounts[i].password) > MAX_PASS_LEN)
        {
            printf("\nERROR | Your password must not exceed 20 characters.\n");
            printf("ADD USER | Enter your password: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].password);
        }
    }

    else
    {
        printf("\nMaximum number of users reached.\n");
        --i;
    }

    ++i;

    /* '*total_p' updated with value of 'i' */
    *total_p = i;

    if(strcmp(accounts->username, "\0") != 0 &&
       strcmp(accounts->password, "\0") != 0)
    {
        /* User is saved to account file */
        saveUser(accounts, total_p);
    }
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: saveUser()         PURPOSE: Save user input to account database
 *
 * INPUT: accounts[], total_p
 * OUTPUT: saves new user to file with saveUser()
 *****************************************************************************/

void saveUser(user_t accounts[], int* total_p)
{
    FILE * file_p = fopen(LOGIN_DB,"a");

    if(file_p != NULL)
    {
        int i = *total_p - 1;

        fprintf(file_p, "%s %s\n",
                accounts[i].username,
                accounts[i].password);
    }

    fclose(file_p);
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: checkNum()         PURPOSE: Verify if ID only contains numbers
 *
 * INPUT: username[]
 * OUTPUT: containsNum
 *****************************************************************************/
/*int isNum(char ch);

int isNum(char ch)
{
    if(ch >= '0' && ch <= '9')
        return 1;

    return 0;
}*/

int checkNum(const char username[])
{
    int i;
    int containsNum;

    for(i = 0; username[i] != '\0'; i++)
    {
        if(username[i] >= '0' && username[i] <= '9')
            containsNum = 1;

        else
        {
            containsNum = 0;
            break;
        }
    }

    return containsNum;
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: checkChar()      PURPOSE: Verify if pass only contains alphanum
 *
 * INPUT: password[]
 * OUTPUT: containsChar
 *****************************************************************************/

int checkChar(const char password[])
{
    int i;
    int containsChar;

    /* String only contains alphanumeric characters */
    for(i = 0; i <= MAX_PASS_LEN; i++)
    {
        if ((password[i] >= 'A' && password[i] <= 'Z') ||
            (password[i] >= 'a' && password[i] <= 'z') ||
            (password[i] >= '0' && password[i] <= '9'))
        {
            containsChar = 1;
        }

        else
        {
            containsChar = 0;
            break;
        }
    }

    return containsChar;
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: validCred()         PURPOSE: Validate user login input with
 *                                         existing credentials
 * INPUT: credentials[]
 * OUTPUT: exists
 *****************************************************************************/

int validCred(const char credentials[])
{
    FILE *file_p = fopen(LOGIN_DB, "r");

    int exists = 0; /* Counter variable for substring occurrences */

    char text_b[BUF_SIZE + 1] = {'\0'}; /* Buffer for text file contents */

    if (file_p == NULL)
    {
        printf("ERROR | Read error.\n");
        exit(EXIT_FAILURE);
    }

    else
    {
        while(fgets(text_b, BUF_SIZE, file_p) != NULL)
        {
            /* text buffer passed to pointer */
            char *ptr = text_b;

            /* strstr determines if user/pass exists in file */
            /* exists updated with total occurrences of credentials in file */
            while ((ptr = (strstr(ptr, credentials))) != NULL)
            {
                exists++;
                ++ptr;
            }
        }
    }

    fclose(file_p);

    return exists;
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: loginUser()         PURPOSE: Authorise the user to access
 *                                        cipher menu
 * INPUT: total_p
 * OUTPUT: N/A
 *****************************************************************************/

void loginUser(int* total_p)
{
    char space; /* extra char for space */
    user_t login; /* Struct 'login' used for login input */

    printf("\nLOGIN | User ID: ");
    scanf("%c", &space); /* Reads all text (including spaces) in a line */
    scanf("%[^\n]", login.username);

    printf("LOGIN | Password: ");
    scanf("%c", &space); /* Reads all text (including spaces) in a line */
    scanf("%[^\n]", login.password);

    /* Login input matches existing credentials */
    while(validCred(login.username) == 1 && validCred(login.password) == 1)
    {
        printf("\n\n                 LOGIN SUCCESSFUL                 \n\n");

        cipherMenu();
    }

    /* No accounts exist in the database */
    if(total_p == 0)
    {
        printf("\nERROR | No accounts exist.\n");
        return;
    }

    else
    {
        /* Username does not exist in the file */
        while(validCred(login.username) == 0 ||
              validCred(login.password) == 0)
        {
            printf("\n          Invalid username or password.          \n");
            break;
        }

        /* Debug: User will be prompted to enter username with numbers only */
        if(checkNum(login.username) == 0)
        {
            printf("\nERROR | Your ID must only contain numeric characters.\n");
        }

        /* Debug: User will be prompted to enter username */
        if(strcmp(login.username, "\0") == 0)
        {
            printf("\nERROR | Empty user ID.\n");
        }

        /* Debug: User will be prompted to enter password */
        if(strcmp(login.password, "\0") == 0)
        {
            printf("\nERROR | Empty password.\n");
        }

        /* Debug: User will be prompted to enter ID not < than 8 characters */
        if(strlen(login.username) < ID_LEN)
        {
            printf("\nERROR | User ID must not be less than 8 characters.\n");
        }

        /* Debug: User will be prompted to enter ID not > than 8 characters */
        if(strlen(login.username) > ID_LEN)
        {
            printf("\nERROR | User ID must not exceed 8 characters.\n");
        }

        /* Debug: User will be prompted to enter pass not < than 8 characters */
        if(strlen(login.password) < MIN_PASS_LEN)
        {
            printf("\nERROR | Password must be at least 8 characters\n");
        }

        /* Debug: User will be prompted to enter pass not > than 20 chars */
        if(strlen(login.password) > MAX_PASS_LEN)
        {
            printf("\nERROR | Password must not exceed 20 chars.\n");
        }
    }
}

#endif /* FUNDCASSIGNMENT3_LOGIN_H */
