/******************************************************************************
 *                               HEADER FILES                                 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

int main()
{

    securityMenu();

    return 0;
}

void securityMenu()
{
    char input_b[BUF_SIZE];
    char output_b[BUF_SIZE];
    char key[MAX_PASS_LENGTH] = "password";
    int choice = 0;

    printSecurity();
    printf("Enter your choice: ");
    scanf("%d", &choice);

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


void printSecurity()
{
    printf("\n\n            SECURITY MENU             ");
    printf("\n--------------------------------------\n");
    printf("Choose from the following options: \n");
    printf("1. Encrypt a file.\n2. Decrypt a file.\n");
}


void encryptMenu(char input_b[], char output_b[],
                 char key[])
{
    char in_filename[MAX_FILE_NAME] = {0};
    char out_filename[MAX_FILE_NAME] = {0};

    printf("\n\n            ENCRYPTION MENU           \n");
    printf("--------------------------------------\n");

    printf("Enter the name of the plaintext file: ");
    scanf("%s", in_filename);
    printf("\n");

    printf("Enter the name you want to give the encrypted file: ");
    scanf("%s", out_filename);
    printf("\n");

    readFile(in_filename, input_b);
    encryptText(input_b, output_b, key);
    writeFile(in_filename, input_b, output_b);

    printf("File encrypted successfully.\n");
}

void decryptMenu(char input_b[], char output_b[], char key[])
{
    char in_filename[MAX_FILE_NAME] = {0};
    /*char out_filename[MAX_FILE_NAME] = {0};*/

    printf("\n\n         DECRYPTION MENU          \n");
    printf("--------------------------------------\n");

    printf("Enter the name of the file you wish to decrypt: ");
    scanf("%s", in_filename);
    printf("\n");

    /*printf("Enter the name you want to give the decrypted file: ");
    scanf("%s", out_filename);
    printf("\n");*/

    readFile(in_filename, input_b);
    encryptText(input_b, output_b, key);
    writeFile(in_filename, input_b, output_b);

    printf("File decrypted successfully.\n");
}



char readFile(char filename[], char input_b[])
{
    FILE * file_p;

    int i;

    file_p = fopen(filename, "r");

    if(file_p == NULL)
    {
        printf("File not found.\n");
        EXIT_FAILURE;
    }

    if(!feof(file_p))
    {
        for(i = 0; i < BUF_SIZE; i++)
        {
            fscanf(file_p, "%c", &input_b[i]);
        }

        printf("Text is: \n");

        for(i = 0; i < 180; i++)
        {
            if (input_b[i] == '\0')
                break;

            printf("%c", input_b[i]);

        }

        fclose(file_p);
        printf("\n\n");
    }

    return input_b[BUF_SIZE];
}

void writeFile(char filename[], char input_b[], char output_b[])
{
    FILE * file_p;

    int i;

    file_p = fopen(filename, "w");

    if(file_p == NULL)
    {
        printf("File not found.\n");
        EXIT_FAILURE;
    }

    if(!feof(file_p))
    {
        for(i = 0; i < BUF_SIZE; i++)
        {
            if(i < strlen(input_b))
            {
                                    /* &input_b[i]); */
                fprintf(file_p, "%s", &output_b[i]);
            }
        }

        fclose(file_p);
    }

}

char encryptText(char plaintext_b[], char ciphertext_b[], char key[])
{
    int i = 0;

    while(plaintext_b[i] != '\0')
    {
        for(i = 0; i < strlen(plaintext_b); i++)
        {
            ciphertext_b[i] = plaintext_b[i] ^ key[i % strlen(key)];
        }
    }

    return ciphertext_b[BUF_SIZE];
}

char decryptText(char plaintext_b[], char ciphertext_b[], char key[])
{
    int i = 0;

    while(ciphertext_b[i] != '\0')
    {
        for(i = 0; i < strlen(plaintext_b); i++)
        {
            plaintext_b[i] = ciphertext_b[i] ^ key[i];
        }
    }

    return ciphertext_b[BUF_SIZE];
}
