#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_NAME 30
#define MAX_FILE_SIZE 50
#define MAX_KEY_SIZE 50

void encryptFile(char plaintext[], int ciphertext[], int key[]);
void decryptFile(char decrypt[], int ciphertext[], int key[]);


int main()
{
    char plaintext[MAX_FILE_SIZE];
    int ciphertext[MAX_FILE_SIZE];
    char decrypt[MAX_KEY_SIZE];
    int choice;

    int key[MAX_KEY_SIZE + 1] = {
            18,	49,	46,	22,	43,	27,	27,	36,	36,	45,
            41,	31,	7,	50,	38,	30,	2,	41,	6,	18,
            31,	16,	22,	22,	38,	42,	19,	27,	44,	25,
            31,	45,	50,	6,	26,	23,	32,	31,	38,	8,
            28,	6,	5,	47,	22,	31,	33,	41,	19,	16
    };

    printf("SECURITY MENU | 1 = Encrypt, 2 = Decrypt, 3 = Exit\n");
    scanf("%d", &choice);

    while(1)
    {
        if(choice == 1)
        {
            encryptFile(plaintext, ciphertext, key);
            printf("SECURITY MENU | 1 = Encrypt, 2 = Decrypt\n");
            scanf("%d", &choice);
        }
        else if(choice == 2)
        {
            decryptFile(decrypt, ciphertext, key);
            printf("SECURITY MENU | 1 = Encrypt, 2 = Decrypt\n");
            scanf("%d", &choice);
        }
        
        else
            exit(1);
    }
    
}

void encryptFile(char plaintext[], int ciphertext[], int key[])
{
    FILE * file_p;

    char filename[MAX_FILE_NAME];

    printf("ENCRYPT | Enter the name of the file: ");
    scanf("%s",filename);

    file_p = fopen(filename, "r");

    if(file_p == NULL)
    {
        printf("File not found.\n");
        exit(0);
    }

    else
    {
        int i = 0;
        int j;

        while(!feof(file_p))
        {
            fscanf(file_p, "%c", &plaintext[i]);

            ciphertext[i] = plaintext[i] ^ key[i];
            i++;
        }

        rewind(file_p);

        file_p = fopen(filename, "w");

        for(j = 0; j < i; j++)
        {
            fprintf(file_p, "%d", ciphertext[j]);
        }

    }

    fclose(file_p);
}

void decryptFile(char decrypt[], int ciphertext[], int key[])
{
    FILE * file_p;
    char filename[MAX_FILE_NAME];

    printf("DECRYPT | Enter the name of the file: ");
    scanf("%s",filename);

    file_p = fopen(filename, "r");

    if(file_p == NULL)
    {
        printf("File not found.\n");
        exit(0);
    }

    else
    {
        int i = 0;
        int j;

        while(!feof(file_p))
        {
            fscanf(file_p, "%d", &ciphertext[i]);

            decrypt[i] = ciphertext[i] ^ key[i];
            i++;
        }

        rewind(file_p);

        file_p = fopen(filename, "w");

        for(j = 0; j < i; j++)
        {
            fprintf(file_p, "%d", ciphertext[j]);
        }

        printf("DECRYPT | File decrypted successfully.\n");

    }

    fclose(file_p);
}
