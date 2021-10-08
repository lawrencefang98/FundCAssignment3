
#define MAX_FILE_NAME 30

int i;
int j;
int n;

char in_filename[];
char out_filename[];
char plaintext[];
int ciphertext[];
char decrypt[];

int randomKey[];

char firstName[];
char lastName[];
char username[];
char password[];


/**
 * FUNCTION: encryptMenu()          PURPOSE:  Prompts user for encryption
 *
 * INPUT: File to be encrypted - plaintext
 * OUTPUT: Encrypted file - ciphertext
 **/

void encryptMenu();


/**
 * FUNCTION: decryptMenu()          PURPOSE: User prompts for decryption
 *
 * INPUT: File to be decrypted - ciphertext
 * OUTPUT: Decrypted file - plaintext
 **/

void decryptMenu();


/**
 * FUNCTION: encrypt()              PURPOSE: Encrypt the plaintext file
 *
 * INPUT: plaintext file
 * OUTPUT: ciphertext file
 **/

void encrypt();


/**
 * FUNCTION: decrypt()              PURPOSE: Decrypts the ciphertext file
 *
 * INPUT: ciphertext file
 * OUTPUT: plaintext file
 **/

void decrypt();


/**
 * FUNCTION: manageUser()          PURPOSE: Username and password management
 *
 * INPUT:   firstName[], lastname[], username[], password[]
 *              - Registering users --> void registerUser();
 *              - Deleting user and pass --> void deleteUser():
 *              - Changing user and pass --> void changeUser();
 **/

void manageUser();
void registerUser();
void deleteUser();
void changeUser();


/**
 * FUNCTION: validPass()            PURPOSE: Validates username + pass
 *
 * INPUT: username and password
 * OUTPUT:  - valid = continue to encryption/decryption
 *          -  invalid = exit/ prompt for valid credentials
 **/

void validPass();
void checkAlpha(); /* passwords must include both char and int values */
void checkNum();


/**
 * FUNCTION: readData()         PURPOSE: Calculate file char length --> 'n'
 *
 * INPUT: text file
 * OUTPUT: char total
 **/

void readData();


/**
 * FUNCTION: keygen();          PURPOSE: Generate random key of 'n' length
 *
 * INPUT: text file char length
 * OUTPUT: cipher key
 **/

void keygen();
