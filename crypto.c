#include <stdlib.h>
#include <stdio.h>
#include "crypto.h"

char tab3[] = {'A','B','C','D','E','F',
            'G','H','I','J','K','L',
            'M','N','O','P','Q','R',
            'S','T','U','V','W','X',
            'Y','Z',' ','.',',','"',
            '!','?'};

/*********************************************************
@name: encrypt_binaire
@description: Fonction qui crypte le caractere en binaire
@parameters:
-char c: caractere
@return: un binaire
**********************************************************/
int* encrypt_binaire(char c){

    int i = 0;
    BOOL boolean = TRUE;

    while(boolean){
        if(tab3[i]==c){
            //printf("Trouve en i = %d\n", i);
            boolean = FALSE;
        }else{
            i++;
        }
    }

    int decimal = i;
    int r = 0; //reste
    int dummy[5] = {0,0,0,0,0}; //stockage de reste
    int j = 0;

    while(decimal>0){
        r = decimal % 2; //calcule du reste valeur 0 ou 1
        dummy[j] = r; //stocke la valeur du reste

        //printf("Decimal: %d = 2* ", decimal);
        decimal = decimal / 2;
        //printf("%d + %d\n", decimal, r);
        if(decimal>0){
            j++;
        }
        //printf("j = %d\n", j);
    }

    int k;
    int z = 0;
    int *binaire_ptr = malloc(5*sizeof(int));
    if(i == 0){
            //si i = 0 cad on est dans le tableau du 1er valeur et qui prend en valeur binaire 00000
        for(k=0; k<5; ++k){
            binaire_ptr[k] = dummy[k];
        }
    }else{
        for(k=4; k>=0; --k){
            binaire_ptr[z] = dummy[k];
            z++;
        }
    }


    //int a;
    //printf("Le charactere %c a pour nombre binaire :", c);
    //for(a = 0; a<5 ; ++a){
        //printf("%d",binaire_ptr[a]);
    //}
    //printf("\n");

    return binaire_ptr;
}

/*********************************************************
@name: decrypt_binaire
@description: Fonction qui decrypt le binaire en caractere
@parameters:
-int* tableau: binaire
@return: un caractere en char
**********************************************************/
char decrypt_binaire(int *tableau){

    int x = 4;
    int j;
    int decimal = 0;
    for(j = 0; j<5; ++j){
        if(tableau[j]==1){
            decimal = decimal + tableau[j]*puissance(2,x);
            //printf("Decimal %d\n", decimal);
        }
        x = x - 1;
    }
    //printf("Decimal = %d\n", decimal);
    char c = tab3[decimal];
    //int i;
    //printf("Le caractere du nombre binaire ");
    //for(i =0; i<5; ++i){
        //printf("%d", tableau[i]);
    //}
    //printf(" est %c\n", c);

    return c;
}

int puissance(int x, int p){
    int i;
    int val = 1;
    for(i = 0; i<p; i++){
        val = val * x;
    }
    return val;
}

/*********************************************************************************************************************************************
@name: function
@description: Fonction qui permet de decaler un message binaire vers la gauche et d'additionner en base 2 le ou exclusif le message et une cl¨¦
@parameters:
-char* Msg: message de caractere
-char* Key: la cle
@return: un binaire
***********************************************************************************************************************************************/
int* function(char* Msg, char* Key){
    int n = 10;

    char msg1 = Msg[0];
    char msg2 = Msg[1];
    int* binaireMsg1 = encrypt_binaire(msg1);
    int* binaireMsg2 = encrypt_binaire(msg2);
    int* binaireMsg = malloc(n*sizeof(int));
    //printf("Message binaire : ");
    binaireMsg = collage(binaireMsg1, binaireMsg2);

    int i;
    int tmp;
    /*decallage de bit vers la gauche*/
    for(i = 0; i<n-1; ++i){
        tmp = binaireMsg[i];
        binaireMsg[i] = binaireMsg[i+1];
        binaireMsg[i+1] = tmp;
    }

    //printf("Apres decallage a gauche: ");
    //int k;
    //for(k = 0; k<n; ++k){
        //printf("%d", binaireMsg[k]);
    //}
    //printf("\n");

    char Key1 = Key[0];
    char Key2 = Key[1];
    int* binaireKey1 = encrypt_binaire(Key1);
    int* binaireKey2 = encrypt_binaire(Key2);
    int* binaireKey = malloc(n*sizeof(int));
    //printf("Key binaire: ");
    binaireKey = collage(binaireKey1, binaireKey2);

    int j;
    int* tableau_binaire = malloc(n*sizeof(int));
    /*addition binaire du ou exclusif*/
    for(j = 0; j<n; ++j){
        tableau_binaire[j] = binaireMsg[j] ^ binaireKey[j];
    }

    //printf("Apres addition de base 2 en ou exclusif: ");
    //int z;
    //for(z = 0; z<n; ++z){
        //printf("%d", tableau_binaire[z]);
    //}
    //printf("\n");

    return tableau_binaire;
}

/***********************************************************************************************************************
@name: collage
@description: Fonction sert a empiler les binaires c'est a dire de coller de rassembler les binaires dans une variables
@parameters:
-int* tableau1: binaire 1
-int* tableau2: binaire2
@return: tableau binaire
*************************************************************************************************************************/
int* collage(int* tableau1, int* tableau2){
    int* tableau = malloc(10*sizeof(int));
    int i;
    int j = 0;

    for(i = 0; i<10; ++i){
        if(i<=4){
            tableau[i] = tableau1[i];
        }else if(i>4){
            tableau[i] = tableau2[j];
            j++;
        }
    }

    //int z;
    //printf("Binaire : ");
    //for(z = 0; z<10; ++z){
        //printf("%d",tableau[z]);
    //}
    //printf("\n");
    return tableau;
}

/***********************************************************************************************************************
@name: encrypt_Feistel
@description: Fonction qui crypte en Feistel, avec une cl¨¦ et un message pendant 4 tour
@parameters:
-char* Msg: message a chiffrer
-char* Key: la cle
@return: tableau de caractere
*************************************************************************************************************************/
char* encrypt_Feistel(char* Msg, char* Key){
    char Key1[2] = {Key[0], Key[1]};
    char Key2[2] = {Key[1], Key[2]};
    char Key3[2] = {Key[2], Key[3]};
    char Key4[2] = {Key[3], Key[0]};

    char G0[2] = {Msg[0], Msg[1]};
    char D0[2] = {Msg[2], Msg[3]};

    int i;
    int* binaire = malloc(10*sizeof(int));
    int* binaire1;
    int* binaire2;
    char* tmp_G;
    char* tmp_D;
    char* tmpG;;
    char* tmpD;

    for(i = 0; i<4; ++i){

       switch(i){

        case 0:
            //printf("1er tour\n");
            tmp_G = D0;
            binaire1 = encrypt(G0);
            binaire2 = function(tmp_G, Key1);
            int j;
            for(j = 0; j<10; ++j){
                binaire[j] = binaire1[j]^binaire2[j];
            }
            tmp_D = decrypt(binaire);
            break;
        case 1:
            //printf("2eme tour\n");
            tmpG = tmp_D;
            binaire1 = encrypt(tmp_G);
            binaire2 = function(tmp_D,Key2);
            int c;
            for(c = 0; c<10; ++c){
                binaire[c] = binaire1[c]^binaire2[c];
            }
            tmpD = decrypt(binaire);
            break;
        case 2:
            //printf("3eme tour\n");
            tmp_G = tmpD;
            binaire1 = encrypt(tmpG);
            binaire2 = function(tmp_G, Key3);
            int a;
            for(a = 0; a<10; ++a){
                binaire[a] = binaire1[a]^binaire2[a];
            }
            tmp_D = decrypt(binaire);
            break;
        case 3:
            //printf("4eme tour\n");
            tmpG = tmp_D;
            binaire1 = encrypt(tmp_G);
            binaire2 = function(tmp_D,Key4);
            int d;
            for(d = 0; d<10; ++d){
                binaire[d] = binaire1[d]^binaire2[d];
            }
            tmpD = decrypt(binaire);
            break;
        }
    }


    char* caractere = malloc(4*sizeof(char));
    caractere[0] = tmpG[0];
    caractere[1] = tmpG[1];
    caractere[2] = tmpD[0];
    caractere[3] = tmpD[1];
    print(caractere);
    return caractere;
}

/*************************************************************************
@name: encrypt
@description: Fonction sert a crypter directement 2 caracteres en binaire
@parameters:
-char* Msg: message
@return: tableau de binaire
***************************************************************************/
int* encrypt(char* Msg){
    int* binaireMsg1 = encrypt_binaire(Msg[0]);
    int* binaireMsg2 = encrypt_binaire(Msg[1]);
    int* binaireMsg = malloc(10*sizeof(int));
    //printf("Message binaire : ");
    binaireMsg = collage(binaireMsg1, binaireMsg2);
    return binaireMsg;
}

/********************************************************************************
@name: decrypt
@description: Fonction sert a decrypter un tableau de 10 binaires en 2 caracteres
@parameters:
-int* tableau: binaire de 10 entier
@return: tableau de caractere
*********************************************************************************/
char* decrypt(int* tableau){
    int* binaire1 = malloc(5*sizeof(int));
    int* binaire2 = malloc(5*sizeof(int));

    int i;
    int j = 0;
    for(i = 0; i<10; ++i){
         if(i<=4){
            binaire1[i] = tableau[i];
        }else if(i>4){
            binaire2[j] = tableau[i];
            j++;
        }
    }

    char* msg = malloc(2*sizeof(char));
    msg[0] = decrypt_binaire(binaire1);
    msg[1] = decrypt_binaire(binaire2);
    return msg;
}

/***************************************************************
@name: print
@description: Fonction qui sert donc a afficher les caracteres
@parameters:
-char* Msg: message
@return:
****************************************************************/
void print(char* Msg){
    int i;
    for(i = 0; i<4; ++i){
        printf("%c", Msg[i]);
    }
}

/***************************************************************
@name: print_binaire
@description: Fonction qui sert a afficher les binaires
@parameters:
-char* Msg: message
@return:
****************************************************************/
void print_binaire(char* Msg){
    int i;
    printf("Binaire : ");
    for(i = 0; i<10; ++i){
        printf("%d", Msg[i]);
    }
    printf("\n");
}

/***************************************************************
@name: decrypt_Feistel
@description: Fonction qui decrypte en utilisant la methode Feistel
@parameters:
-char* Msg: message
-char* Key: la cle
@return: tableau de caractere decrypter
****************************************************************/
char* decrypt_Feistel(char* Msg, char* Key){
    char Key1[2] = {Key[0], Key[1]};
    char Key2[2] = {Key[1], Key[2]};
    char Key3[2] = {Key[2], Key[3]};
    char Key4[2] = {Key[3], Key[0]};

    char D0[2] = {Msg[0], Msg[1]};
    char G0[2] = {Msg[2], Msg[3]};

    int i;
    int* binaire = malloc(10*sizeof(int));
    int* binaire1;
    int* binaire2;
    char* tmp_G;
    char* tmp_D;
    char* tmpG;;
    char* tmpD;

    for(i = 0; i<4; ++i){
        switch(i){

            case 0:
                tmp_G = D0;
                binaire1 = encrypt(G0);
                binaire2 = function(tmp_G, Key4);
                int j;
                for(j = 0; j<10; ++j){
                    binaire[j] = binaire1[j]^binaire2[j];
                }
                tmp_D = decrypt(binaire);
                break;
            case 1:
                tmpG = tmp_D;
                binaire1 = encrypt(tmp_G);
                binaire2 = function(tmp_D,Key3);
                int c;
                for(c = 0; c<10; ++c){
                    binaire[c] = binaire1[c]^binaire2[c];
                }
                tmpD = decrypt(binaire);
                break;
            case 2:
                tmp_G = tmpD;
                binaire1 = encrypt(tmpG);
                binaire2 = function(tmp_G, Key2);
                int a;
                for(a = 0; a<10; ++a){
                    binaire[a] = binaire1[a]^binaire2[a];
                }
                tmp_D = decrypt(binaire);
                break;
            case 3:
                tmpG = tmp_D;
                binaire1 = encrypt(tmp_G);
                binaire2 = function(tmp_D,Key1);
                int d;
                for(d = 0; d<10; ++d){
                    binaire[d] = binaire1[d]^binaire2[d];
                }
                tmpD = decrypt(binaire);
                break;
            }
    }

    char* caractere = malloc(4*sizeof(char));
    caractere[0] = tmpD[0];
    caractere[1] = tmpD[1];
    caractere[2] = tmpG[0];
    caractere[3] = tmpG[1];
    print(caractere);
    return caractere;
}
