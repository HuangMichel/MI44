#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "prg_b.h"
#include "prg_a.h"

/*****************************************************************************************************************
@name: genere_confirmationB
@description: Fonction qui permet de confirmer si il a bien recu le message AB?! et lui renvoyer en cryptant ABOK
@parameters:
-char* M: message en char
-long e: l'exposant modulaire
-long n: valeur
@return: long* C : les caracteres chiffrees en decimal
******************************************************************************************************************/
long* genere_confirmationB(char* c, long e, long n){
    long* message = malloc(sizeof(long));

    if(c[0] == 'A' && c[1] == 'B' && c[2] == '?' && c[3] == '!'){
        printf("-----------------CONFIRMATION DANS B----------------\n");
        char* M = malloc(4*sizeof(char));
        M[0] = 'A';
        M[1] = 'B';
        M[2] = 'O';
        M[3] = 'K';
        message = crypt_messageA(M, e, n);

    }else{
        message[0] = '0';
    }
    return message;
}
