#define BOOL int
#define FALSE 0
#define TRUE 1

long* powmodA(long* M, long e, long n);
long Find_DecimalA(char M);
char Find_CharA(long M);
long* CharToDecimalA(char* M);
long random_numberA();
long* genere_aleatoireA(char* c, long e2, long n2, char* texte);
long* crypt_messageA(char* M, long e, long n);
char* decrypt_messageA(long* M, long d, long n);
char* DecimalToCharA(long* M);
BOOL testMessage(char* C1, char* C2);
long* binaireA(char* m);
char* genere_passwordA(char* m);
char* MotPassA(long* M);
long BinaireToDecimalA(long* m);
int puissanceA(int x, int p);
char* genereText();
