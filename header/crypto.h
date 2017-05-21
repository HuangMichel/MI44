#ifndef CRYPTOGRAPHIE_H_INCLUDED
#define CRYPTOGRAPHIE_H_INCLUDED

#define BOOL int
#define FALSE 0
#define TRUE 1

int* encrypt_binaire(char c);
char decrypt_binaire(int* tableau);
int puissance(int x, int p);
int* function(char* Msg, char* Key);
int* collage(int* tableau1, int* tableau2);
char* encrypt_Feistel(char* Msg, char* Key);
int* encrypt(char* Msg);
char* decrypt(int* tableau);
void print(char* Msg);
void print_binaire(char* Msg);
char* decrypt_Feistel(char* Msg, char* Key);

#endif // CRYPTOGRAPHIE_H_INCLUDED
