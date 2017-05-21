#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "prg_a.h"

char tab[] = {'A','B','C','D','E','F',
            'G','H','I','J','K','L',
            'M','N','O','P','Q','R',
            'S','T','U','V','W','X',
            'Y','Z',' ','.',',','"',
            '!','?'};

/*********************************************************
@name: crypt_messageA
@description: Fonction qui crypte le message
@parameters:
-char* M: message en char
-long e: l'exposant modulaire
-long n: valeur
@return: long* C : les caracteres chiffr¨¦es en decimal
**********************************************************/
long* crypt_messageA(char* M, long e, long n){
    printf("Message a envoyer : ");
    int i;
    for(i = 0; i<4; ++i){
        printf("%c", M[i]);
        if(i<3){
            printf(", ");
        }
    }
    printf("\n");
    printf("--------------------Crypter--------------------\n");
    long* m = CharToDecimalA(M);
    long* C = powmodA(m, e, n);
    int j;
    printf("Message crypte : ");
    for(j = 0; j<4; ++j){
        printf("%ld", C[j]);
        if(j<3){
            printf(", ");
        }
    }
    printf("\n");

    return C;
}

/*********************************************************
@name: decrypt_messageA
@description: Fonction qui decrypt le message
@parameters:
-long* M: message crypter
-long d: l'inverse modulaire
-long n: valeur
@return: char* caractere: caracteres d¨¦chiffrer
**********************************************************/
char* decrypt_messageA(long* M, long d, long n){
    printf("\n\nMessage a recu : ");
    int i;
    for(i = 0; i<4; ++i){
        printf("%ld", M[i]);
        if(i<3){
            printf(", ");
        }
    }
    printf("\n");
    printf("--------------------Derypter--------------------\n");
    long* D = powmodA(M, d, n);
    char* caractere = malloc(4*sizeof(char));
    int j;
    printf("Message decrypte : ");
    for(j = 0; j<4; ++j){
        caractere[j] = Find_CharA(D[j]);
        printf("%c", caractere[j]);
        if(j<3){
            printf(", ");
        }
    }
    printf("\n");
    return caractere;
}

/**************************************************************
@name: Find_CharA
@description: Fonction qui cherche le caractere dans le tableau
@parameters:
-long M: valeur
@return: char du caractere
***************************************************************/
char Find_CharA(long M){
    return tab[M];
}

/**************************************************************
@name: CharToDecimalA
@description: Fonction qui convertie de d¨¦cimal en char
@parameters:
-char* M: caractere
@return: long* decimal
***************************************************************/
long* CharToDecimalA(char* M){
    int i;
    long* m = malloc(4*sizeof(long));
    for(i = 0; i<4; ++i){
        m[i] = Find_DecimalA(M[i]);
        //printf("%ld == %c\n", m[i], M[i]);
    }
    return m;
}

/**************************************************************
@name: DecimalToCharA
@description: Fonction qui cherche le caractere dans le tableau
@parameters:
-long M: valeur
@return: char du caractere
***************************************************************/
char* DecimalToCharA(long* M){
    int i;
    char* m = malloc(4*sizeof(char));
    for(i = 0; i<4; ++i){
        m[i] = Find_CharA(M[i]);
        //printf("%c == %ld\n", m[i], M[i]);
    }
    return m;
}

/**************************************************************
@name: Find_DecimalA
@description: Fonction qui cherche le decimal
@parameters:
-char M: caractere
@return: long decimal ou 0 si il ne le trouve pas
***************************************************************/
long Find_DecimalA(char M){
    int i;
    for(i = 0; i<32; ++i){
        if(M==tab[i]){
            //printf("i =%d\n", i);
            return i;
        }
    }
    return 0;
}

/**************************************************************
@name: powmodA
@description: Fonction qui calcule la puissance modulaire
@parameters:
-long* M: message en decimal
-long e : l'exposant modulaire
-long n: valeur
@return: un message crypter en long
***************************************************************/
long* powmodA(long* M, long e, long n){
    long decimal;
    /*long r = 0; //reste
    long dummy[100000]; //stockage de reste
    int j = 0;

    while(decimal>0){
        r = decimal % 2; //calcule du reste valeur 0 ou 1
        dummy[j] = r; //stocke la valeur du reste

        //printf("Decimal: %ld = 2* ", decimal);
        decimal = decimal / 2;
        //printf("%ld + %ld\n", decimal, r);
        if(decimal>=0){
            j++;
        }
        //printf("j = %d\n", j);
    }*/

    long R[2];
    int k = 0;
    //int b;
    long* result = malloc(4*sizeof(long));
    int i;
   /* for(i = 0; i<4; ++i){
        R[0] = 1;
        R[1] = M[k];
        for(b = 0; b<=j; ++b){
            if(dummy[b]==1){
                //printf("R[0] = %ld ", R[0]);
                R[0] = R[0] * R[1] % n;
                //printf(" * %ld mod %ld = %ld\n", R[1], n, R[0]);
            }
            //printf("R[1] = %ld * %ld mod %ld ", R[1], R[1], n);
            R[1] = (R[1]*R[1]) % n;
            //printf(" = %ld\n", R[1]);
        }
        result[k] = R[0];
        if(k<=3){
            k++;
        }
    }*/
    for(i = 0; i<4; ++i){
        decimal = e;
        R[0] = 1;
        R[1] = M[k];
        while(decimal>0){
            if(decimal%2==1){
                R[0] = R[0] * R[1] % n;
            }
            decimal = decimal/2;
            R[1] = (R[1]*R[1]) % n;
        }
        result[k] = R[0];
        if(k<=3){
            k++;
        }
    }
    //printf("%ld, %ld, %ld, %ld\n", result[0], result[1], result[2], result[3]);
    return result;
}

/**************************************************************
@name: random_numberA
@description: Fonction qui genere un nombre al¨¦atoire
@parameters:
@return: nombre en long entre 0 et 31
***************************************************************/
long random_numberA(){
    long number = rand()%32;
    //printf("number %ld\n", number);
    return number;
}

/****************************************************************************************************************
@name: genere_aleatoireA
@description: Fonction qui valide si il recoit bien le message ABOK et genere 4 caracteres aleatoire et le crypte
@parameters:
-char* c: caractere
-long e2: cle public
-long n2: cle public
-char* texte: texte generer aleatoirement
@return: un message crypter en long
*****************************************************************************************************************/
long* genere_aleatoireA(char* c, long e2, long n2, char* texte){
    int i;
    long* message = malloc(sizeof(long));
    long* decimal = CharToDecimalA(texte);
    if(c[0] == 'A' && c[1] == 'B' && c[2] == 'O' && c[3] == 'K'){
        printf("\n-----------------CONFIRMATION DANS A----------------\n");
        printf("Genere 4 caracteres aleatoire\n");
        for(i = 0; i<4; ++i){
            printf("%c = %ld", texte[i], decimal[i]);
            if(i<3){
                printf(", ");
            }
        }
        printf("\n");
        message = crypt_messageA(texte, e2, n2);

    }else{
        message[0] = '0';
    }
    return message;
}

/*********************************************************************
@name: testMessage
@description: Fonction qui regarde si les deux messages sont les m¨ºmes
@parameters:
-char* C1: message 1
-char* C2: message 2
@return: BOOL TRUE pour message les memes sinon FALSE
**********************************************************************/
BOOL testMessage(char* C1, char* C2){
    BOOL boolean = FALSE;
    printf("%c = %c\n", C1[0], C2[0]);
    printf("%c = %c\n", C1[1], C2[1]);
    printf("%c = %c\n", C1[2], C2[2]);
    printf("%c = %c\n", C1[3], C2[3]);
    if(C1[0]==C2[0] && C1[1]==C2[1] && C1[2]==C2[2] && C1[3]==C2[3]){
        printf("\n-------------Meme Message------------\n");
        boolean = TRUE;
    }
    return boolean;
}

/**********************************************************************************************************
@name: genere_passwordA
@description: Fonction qui genere un mot de passe d'addition binaire en ou exclusif de ABOK + 4 caracteres
@parameters:
-char* m: message
@return: char du caractere
**********************************************************************************************************/
char* genere_passwordA(char* m){
    char m2[4] = {'A', 'B', 'O', 'K'};
    long* decimal1 = binaireA(m);
    long* decimal2 =  binaireA(m2);
    long* addition = malloc(20*sizeof(long));
    int i;
    //printf("Mot de passe :");
    for(i = 0; i<=19; ++i){
        addition[i] = decimal1[i]^decimal2[i];
        //printf("%ld", addition[i]);
    }
    //printf("\n");
    char* message = MotPassA(addition);
    printf("Mot de passe A: %c, %c, %c, %c\n", message[0], message[1], message[2], message[3]);
    return message;
}

/*********************************************************************
@name: binaireA
@description: Fonction qui calcule le binaire de la chaine de caractere
@parameters:
-char* m: message
@return: tableau binaire
**********************************************************************/
long* binaireA(char* m){
    long* decimal = CharToDecimalA(m);
    int i;
    long dummy[20] = {0,0,0,0,0
                        ,0,0,0,0,0
                        ,0,0,0,0,0
                        ,0,0,0,0,0};

    int j = 0;
    int l = 0;
    for(i=0; i<4; ++i){
        if(decimal[i]==0){
            for(l=0; l<4; ++l){
                dummy[j] = 0;
                j++;
            }
        }else{
            while(decimal[i]>0){
                dummy[j] = decimal[i]%2;
                decimal[i] = decimal[i] / 2;
                j++;
            }
        }
    }


    int k;
    int z = 0;
    long *binaire_ptr = malloc(20*sizeof(long));
    for(k=19; k>=0; --k){
        binaire_ptr[z] = dummy[k];
        //printf("%ld", binaire_ptr[z]);
        z++;
    }
    //printf("\n");

    return binaire_ptr;
}

/***************************************************************************
@name: MotPassA
@description: Fonction qui convertie le mot de passe de decimal et caractere
@parameters:
-long* M: mot de passe en decimal
@return: mot de passe en caractere
****************************************************************************/
char* MotPassA(long* M){
    long* m = malloc(5*sizeof(long));
    long* ptr_m = malloc(4*sizeof(long));
    int i;
    int j = 0;
    int k;
    for(i = 0; i<4; ++i){
        for(k = 0; k<5; ++k){
            m[k] = M[j];
            if(j<=19){
                j++;
            }
        }
        ptr_m[i] = BinaireToDecimalA(m);
    }
    char* c = DecimalToCharA(ptr_m);
    return c;
}

/**************************************************************
@name: BinaireToDecimalA
@description: Fonction qui converti de binaire en decimal
@parameters:
-long* m: message en binaire
@return: decimal en long
***************************************************************/
long BinaireToDecimalA(long* m){
    int x = 4;
    int j;
    long decimal = 0;
    for(j = 0; j<5; ++j){
        if(m[j]==1){
            decimal = decimal + m[j]*puissanceA(2,x);
        }
        x = x - 1;
    }
    return decimal;
}

/**************************************************************
@name: puissanceA
@description: Fonction qui calcule la puissance du nombre
@parameters:
-long x: valeur
-long p: l'exposant
@return: valeur en int
***************************************************************/
int puissanceA(int x, int p){
    int i;
    int val = 1;
    for(i = 0; i<p; i++){
        val = val * x;
    }
    return val;
}

/**************************************************************
@name: genereText
@description: Fonction qui genere 4 caracteres aleatoires
@parameters:
@return: tableau de caractere
***************************************************************/
char* genereText(){
    char* text = malloc(4*sizeof(char));
    int i;
    for(i = 0; i<4; ++i){
        text[i] = tab[random_numberA()];
    }
    return text;
}
