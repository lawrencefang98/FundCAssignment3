
/******************************************************************************
 *                               HEADER FILES                                 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

/* Collect user credentials */
/* User password == PRIVATE cipher key */
/* Prompt user for which file they want to encrypt/decrypt */
/* Read the file */
/* Store contents in a buffer */
/* Perform encryption/ decryption on the buffer */
/* Write the contents to the same file, maybe a different file (?) */

int main()
{

    securityMenu();

}

void securityMenu()
{
    char input_b[BUF_SIZE + 1] = {'\0'};
    char output_b[BUF_SIZE + 1] = {'\0'};
    char key[MAX_PASS_LEN + 1] = {'\0'};
    int choice = 0;

    printSecurity();
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    printf("Enter your key: ");
    scanf("%s", key);


    while(1)
    {
        if(choice == 1)
        {
            encryptMenu(input_b, output_b, key);

            printSecurity();
            printf("Enter your choice: ");
            scanf("%d", &choice);
        }

        else if(choice == 2)
        {
            decryptMenu(input_b, output_b, key);

            printSecurity();
            printf("Enter your choice: ");
            scanf("%d", &choice);
        }
    }
}


void printSecurity()
{
    printf("\n\n            SECURITY MENU             ");
    printf("\n--------------------------------------\n");
    printf("Choose from the following options: \n");
    printf("1. Encrypt a file.\n2. Decrypt a file.\n");
}


void encryptMenu(char input_b[], char output_b[], char key[])
{
    char in_filename[MAX_FILE_NAME + 1] = {'\0'};

    printf("\n\n            ENCRYPTION MENU           \n");
    printf("--------------------------------------\n");

    printf("Enter the name of the plaintext file: ");
    scanf("%s", in_filename);
    printf("\n");

    readFile(in_filename, input_b);
    encryptDecrypt(input_b, output_b, key);
    writeFile(in_filename, input_b, output_b);

    printf("File encrypted successfully.\n");
}

void decryptMenu(char input_b[], char output_b[], char key[])
{
    char in_filename[MAX_FILE_NAME + 1] = {'\0'};

    printf("\n\n         DECRYPTION MENU          \n");
    printf("--------------------------------------\n");

    printf("Enter the name of the ciphertext file: ");
    scanf("%s", in_filename);
    printf("\n");

    readFile(in_filename, input_b);
    encryptDecrypt(input_b, output_b, key);
    writeFile(in_filename, input_b, output_b);

    printf("File decrypted successfully.\n");
}


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
        printf("File not found.\n");
        EXIT_FAILURE;
    }

    fclose(file_p);
}

void encryptDecrypt(char input_b[], char output_b[], char key[])
{
    int i = 0;

    while (input_b[i] != '\0')
     {
        for (i = 0; i < strlen(input_b); i++)
        {
            output_b[i] = input_b[i] ^ key[i % sizeof(*key)/sizeof(char)];
        }
    }
}
