/******************************************************************************
 *                               HEADER GUARDS                                *
 ******************************************************************************/

#ifndef FUNDCASSIGNMENT3_ENCRYPTION_H
#define FUNDCASSIGNMENT3_ENCRYPTION_H

/******************************************************************************
 *                               HEADER FILES                                 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                          PREPROCESSOR DIRECTIVES                           *
 ******************************************************************************/

#define MAX_FILE_NAME 30
#define MAX_PASS_LEN 20
#define BUF_SIZE 4096

/******************************************************************************
 *                     FUNCTION PROTOTYPES  |  ENCRYPTION                     *
 ******************************************************************************/

/* Menus */
void cipherMenu();
void cipherChoice();
void encryptMenu(char input_b[], char output_b[], char key[]);
void decryptMenu(char input_b[], char output_b[], char key[]);

/* Menu Options */
char readFile(char filename[], char input_b[]);
void xorEncDec(char input_b[], char output_b[], char key[]);
void writeFile(char filename[], char input_b[], char output_b[]);

/******************************************************************************
 *                     FUNCTION PROTOTYPES  |  ENCRYPTION                     *
 ******************************************************************************/

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: cipherMenu()         PURPOSE: Display choices to user and accept
 *                                         input to execute relevant function
 * INPUT: N/A
 * OUTPUT: N/A
 *****************************************************************************/

void cipherMenu()
{
    char input_b[BUF_SIZE + 1] = {'\0'};
    char output_b[BUF_SIZE + 1] = {'\0'};
    char key[MAX_PASS_LEN + 1] = {'\0'};
    int choice = 0;

    cipherChoice();

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    while(1)
    {
        if(choice == 1)
        {
            printf("\nWARNING | Using an invalid key will corrupt the file.\n");
            printf("\nEnter your key: ");
            scanf("%s", key);

            encryptMenu(input_b, output_b, key);

            cipherChoice();
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
        }

        else if(choice == 2)
        {
            printf("\nWARNING | Using an invalid key will corrupt the file.\n");
            printf("\nEnter your key: ");
            scanf("%s", key);

            decryptMenu(input_b, output_b, key);

            cipherChoice();
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
        }

        else if(choice == 3)
        {
            return;
        }

        else
        {
            printf("\nPlease choose a valid option.\n");
            scanf("%d", &choice);
        }
    }
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: cipherChoice()         PURPOSE: Print choices to user
 *
 * INPUT: N/A
 * OUTPUT: N/A
 *****************************************************************************/

void cipherChoice()
{
    printf("\n                    CIPHER MENU                   ");
    printf("\n--------------------------------------------------");
    printf("\nChoose from the following options:");
    printf("\n  1. Encrypt a file");
    printf("\n  2. Decrypt a file");
    printf("\n  3. Exit the menu");
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: encryptMenu()         PURPOSE: Carries out text encryption
 *
 * INPUT: input_b, output_b, key
 * OUTPUT: N/A
 *****************************************************************************/

void encryptMenu(char input_b[], char output_b[], char key[])
{
    char in_file[MAX_FILE_NAME + 1] = {'\0'};
    char out_file[MAX_FILE_NAME + 1] = {'\0'};

    printf("\n\n                 ENCRYPTION MENU                  ");
    printf("\n--------------------------------------------------\n");

    printf("\nNOTE | Dont forget to include the .txt file type.\n");

    printf("\nEnter the name of the existing plaintext file: ");

    scanf("%s", in_file);

    printf("Enter the name of the encrypted file: ");
    scanf("%s", out_file);
    printf("\n");

    readFile(in_file, input_b);
    xorEncDec(input_b, output_b, key);
    writeFile(out_file, input_b, output_b);

    printf("\n\n\n            FILE ENCRYPTED SUCCESSFULLY           \n\n\n");
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: decryptMenu()         PURPOSE: Carries out text decryption
 *
 * INPUT: input_b, output_b, key
 * OUTPUT: N/A
 *****************************************************************************/

void decryptMenu(char input_b[], char output_b[], char key[])
{
    char in_file[MAX_FILE_NAME + 1] = {'\0'};
    char out_file[MAX_FILE_NAME + 1] = {'\0'};

    printf("\n\n                 DECRYPTION MENU                  ");
    printf("\n--------------------------------------------------\n");

    printf("\nNOTE | Dont forget to include the .txt file type.\n");

    printf("\nEnter the name of the existing ciphertext file: ");
    scanf("%s", in_file);

    printf("Enter the name of the decrypted file: ");
    scanf("%s", out_file);
    printf("\n");

    readFile(in_file, input_b);
    xorEncDec(input_b, output_b, key);
    writeFile(out_file, input_b, output_b);

    printf("\n\n\n            FILE DECRYPTED SUCCESSFULLY           \n\n\n");
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: readFile()         PURPOSE: Read file and store into text buffer
 *
 * INPUT: input_b, filename[]
 * OUTPUT: input_b[]
 *****************************************************************************/

char readFile(char filename[], char input_b[])
{
    FILE * file_p = fopen(filename, "r");

    if(file_p == NULL)
    {
        printf("File not found.\n");
        EXIT_FAILURE;
    }

    if(!feof(file_p))
    {
        int i = 0;
        char ch;

        for (ch = fgetc(file_p); ch != EOF; ch = fgetc(file_p))
        {
            while((i < BUF_SIZE))
            {
                input_b[i++] = ch;
                break;
            }
        }

        input_b[i] = '\0';

        fclose(file_p);
        printf("\n\n");
    }

    return input_b[BUF_SIZE];
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: writeFile()         PURPOSE: Write file from text buffer
 *
 * INPUT: input_b, filename[], output_b
 * OUTPUT: N/A
 *****************************************************************************/

void writeFile(char filename[], char input_b[], char output_b[])
{
    FILE * file_p = fopen(filename, "w");

    if(file_p != NULL)
    {
        int i;

        for(i = 0; i < BUF_SIZE; i++)
        {
            if(input_b[i] != '\0')
            {
                fwrite(&output_b[i], sizeof(char),
                       sizeof(output_b[BUF_SIZE]), file_p);
            }
        }
    }

    else
    {
        printf("ERROR | Read error.\n");
        EXIT_FAILURE;
    }

    fclose(file_p);
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: xorEncDec()         PURPOSE: encrypt/decrypt chars from buffer
 *
 * INPUT: input_b, output_b, key
 * OUTPUT: N/A
 *****************************************************************************/

void xorEncDec(char input_b[], char output_b[], char key[])
{
    int i = 0;

    while (input_b[i] != '\0')
    {
        for (i = 0; i < strlen(input_b); i++)
        {
            /* restrict the index of the key to its string length */
            output_b[i] = input_b[i] ^ key[i % sizeof(*key)/sizeof(char)];
        }
    }
}

#endif /* FUNDCASSIGNMENT3_ENCRYPTION_H */

