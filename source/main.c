#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prg_a.h"
#include "prg_b.h"
#include "prg_c.h"
#include "crypto.h"

int main()
{
    srand(time(NULL));
    printf("----------------------BIENVENUE DANS LE PROGRAMME CRYPTOGRAPHIE RSA----------------------\n\n");
    printf("Est ce que vous avez les valeurs de la cl¨¦ publique et la cl¨¦ secr¨¨te du programme A et B ?\n");
    printf("Si oui, taper 1 sinon 0\n");
    int cmd;
    BOOL boolean = TRUE;
    while(boolean){
        fscanf(stdin,"%d", &cmd);
        if(cmd<2){
            boolean = FALSE;
            break;
        }
        printf("Je ne connais pas cette valeur, veuillez recommencez\n");

    }
    boolean = TRUE;
    //p1, p2, q1, q2 premier
    //n1, n2, e1, e2 cl¨¦ publique
    //d1, d2, phi1, phi2 cl¨¦ secrete
    long p1, p2, q1, q2, n1, n2, e1, e2, d1, d2, phi1, phi2;

    switch(cmd){
    case 1:
        printf("D'abord pour les cl¨¦s de A\n");
        printf("Veuillez saisir un grand nombre premier pour p1 = ");
        fscanf(stdin,"%ld", &p1);
        while(boolean){
            if(estPremier(p1)==TRUE){
                printf("Veuillez saisir un grand nombre premier pour q1 = ");
                fscanf(stdin,"%ld", &q1);
                if(estPremier(q1)==TRUE){
                    n1 = function_n(p1, q1);
                    printf("n1 = %ld\n", n1);
                    printf("Est ce que vous connaissez phi1 ?\n");
                    printf(">=1: Oui\n 0: Non\n");
                    fscanf(stdin,"%d", &cmd);
                        if(cmd >=1){
                            printf("Veuillez saisir phi1 = ");
                            fscanf(stdin,"%ld", &phi1);
                        }else{
                            phi1 = phi_n(p1, q1);
                        }
                    printf("Est ce que vous connaissez e1 ?\n");
                    printf(">=1: Oui\n 0: Non\n");
                    fscanf(stdin,"%d", &cmd);
                        if(cmd >=1){
                            printf("Veuillez saisir la cle de chiffrement e1 = ");
                            fscanf(stdin,"%ld", &e1);
                        }else{
                            e1 = calcul_e(p1, q1);
                        }
                    if((e1<phi1) && (pgcd(e1, phi1)==1)){
                        printf("Est ce que vous connaissez la cl¨¦ secr¨¨te d1 ?\n");
                        printf(">=1: Oui\n 0: Non\n");
                        fscanf(stdin,"%d", &cmd);
                        if(cmd >=1){
                            printf("Veuillez saisir d1 la cl¨¦ secr¨¨te, d1 = ");
                            fscanf(stdin,"%ld", &d1);
                        }else{
                            d1 = calcul_d(p1, q1, e1);
                        }
                        boolean = FALSE;
                    }else{
                        printf("Veuillez re-saisir e1 = ");
                        scanf("%ld", &e1);
                    }
                }else{
                    printf("Veuillez re-saisir q1 = ");
                    scanf("%ld", &q1);
                }
            }else{
                printf("Veuillez re-saisir p1 = ");
                scanf("%ld", &p1);
            }
        }
        boolean = TRUE;
        printf("Maintenant pour les cl¨¦s de B\n");
        printf("Veuillez saisir un grand nombre premier pour p2 = ");
        fscanf(stdin,"%ld", &p2);
        while(boolean){
            if(estPremier(p2)==TRUE){
                printf("Veuillez saisir un grand nombre premier pour q2 = ");
                fscanf(stdin,"%ld", &q2);
                if(estPremier(q2)==TRUE){
                    n2 = function_n(p2, q2);
                    printf("n2 = %ld\n", n2);
                    printf("Est ce que vous connaissez phi2 ?\n");
                    printf(">=1: Oui\n 0: Non\n");
                    fscanf(stdin,"%d", &cmd);
                        if(cmd >=1){
                            printf("Veuillez saisir phi2 = ");
                            fscanf(stdin,"%ld", &phi2);
                        }else{
                            phi2 = phi_n(p2, q2);
                        }
                    printf("Est ce que vous connaissez e2 ?\n");
                    printf(">=1: Oui\n 0: Non\n");
                    fscanf(stdin,"%d", &cmd);
                        if(cmd >=1){
                            printf("Veuillez saisir la cle de chiffrement e2 = ");
                            fscanf(stdin,"%ld", &e2);
                        }else{
                            e2 = calcul_e(p2, q2);
                        }
                    if((e2<phi2) && (pgcd(e2, phi2)==1)){
                        printf("Est ce que vous connaissez la cl¨¦ secr¨¨te d2 ?\n");
                        printf(">=1: Oui\n 0: Non\n");
                        fscanf(stdin,"%d", &cmd);
                        if(cmd >=1){
                            printf("Veuillez saisir d1 la cl¨¦ secr¨¨te, d2 = ");
                            fscanf(stdin,"%ld", &d2);
                        }else{
                            d2 = calcul_d(p2, q2, e2);
                        }
                        boolean = FALSE;
                    }else{
                        printf("Veuillez re-saisir e2 = ");
                        fscanf(stdin,"%ld", &e2);
                    }
                }else{
                    printf("Veuillez re-saisir q2 = ");
                    fscanf(stdin,"%ld", &q2);
                }
            }else{
                printf("Veuillez re-saisir p2 = ");
                fscanf(stdin,"%ld", &p2);
            }
        }
        printf("A pour cl¨¦ publique (%ld, %ld)\n", e1, n1);
        printf("B pour cl¨¦ publique (%ld, %ld)\n", e2, n2);
        break;
    case 0:
        boolean = TRUE;
        p1 = generePQ();
        p2 = generePQ();
        q1 = generePQ();
        q2 = generePQ();
        if(p1==q1){
            while(boolean){
                if(p1!=q1){
                   boolean = FALSE;
                }else{
                    q1 = generePQ();
                }
            }
        }
        boolean = TRUE;
        if(p2==q2){
            while(boolean){
                if(p2!=q2){
                   boolean = FALSE;
                }else{
                    q2 = generePQ();
                }
            }
        }
        n1 = function_n(p1, q1);
        n2 = function_n(p2, q2);
        phi1 = phi_n(p1, q1);
        phi2 = phi_n(p2, q2);
        e1 = calcul_e(p1, q1);
        e2 = calcul_e(p2, q2);
        d1 = calcul_d(p1, q1, e1);
        d2 = calcul_d(p2, q2, e2);
        if(d1<=1){
            e1 = calcul_e(p1, p1);
            d1 = calcul_d(p1, q1, e1);
        }else if(d2<=1){
            e2 = calcul_e(p2, p2);
            d2 = calcul_d(p2, q2, e2);
        }
        printf("A pour cl¨¦ (e1=%ld, n1=%ld, d1=%ld, phi1=%ld, p1=%ld, q1=%ld)\n", e1, n1, d1, phi1, p1, q1);
        printf("B pour cl¨¦ (e2=%ld, n2=%ld, d2=%ld, phi2=%ld, p2=%ld, q2=%ld)\n", e2, n2, d2, phi2, p2, q2);
        break;
    }
    /*long p1 = 5;
    long q1 = 11;
    //long e1 = 3;
    long n1 = 55;
    long phi1 = phi_n(p1,q1);
    long e1 = calcul_e(p1, q1);
    long d1 = calcul_d(p1,q1,e1);
    printf("A pour cl¨¦ publique (%ld, %ld, %ld, %ld)\n", e1, n1, d1, phi1);

    long p2 = 3;
    long q2 = 11;
    //long e2 = 3;
    long n2 = 33;
    long phi2 = phi_n(p2,q2);
    long e2 = calcul_e(p2, q2);
    long d2 = calcul_d(p2,q2,e2);
    printf("B pour cl¨¦ publique (%ld, %ld, %ld, %ld)\n", e2, n2, d2, phi2);*/

        printf("\n--------------------Programme A---------------------------\n");
        char M1[4] = {'A', 'B', '?', '!'};
        long* A1 = crypt_messageA(M1, e2, n2);

        printf("\n--------------------Programme B--------------------\n");
        char* B1 = decrypt_messageA(A1, d2, n2);

        if(M1[0]==B1[0] && M1[1]==B1[1] && M1[2]==B1[2] && M1[3]==B1[3]){
            long* B2 = genere_confirmationB(B1, e1, n1);

            printf("\n--------------------Programme A--------------------\n");
            char* A2 = decrypt_messageA(B2, d1, n1);
            char* texte = genereText();
            long* A3 = genere_aleatoireA(A2, e2, n2, texte);

            printf("\n--------------------Programme B--------------------\n");
            char* B3 = decrypt_messageA(A3, d2, n2);
            long* B4 = crypt_messageA(B3, e1, n1);

            printf("\n--------------------Programme A--------------------\n");
            char* A4 = decrypt_messageA(B4,d1,n1);

            printf("\n--------------------TESTER MESSAGE--------------------\n");
            if(testMessage(A4, B3)==TRUE){
                printf("\n--------------------Programme A--------------------\n");
                char* KEYA = genere_passwordA(A4);
                printf("\n--------------------Programme B--------------------\n");
                char* KEYB = genere_passwordA(B3);
                printf("\n--------------------Programme A--------------------\n");
                char* text = genereText();
                printf("Message generer non crypter: %c%c%c%c\n", text[0],text[1],text[2],text[3]);
                printf("--------------------Crypter par la methode Feistel--------------------\n");
                char* text_crypt = encrypt_Feistel(text, KEYA);
                printf("\n");
                printf("\n--------------------Programme B--------------------\n");
                printf("--------------------Decrypter par la methode Feistel--------------------\n");
                decrypt_Feistel(text_crypt, KEYB);
                printf("\n");
                printf("--------------------------------------Fin du programme !-----------------------------------\n");
            }else{
                printf("Message non correct\n");
            }

        }else{
            printf("Generation de nombre premier p et q faux\nOu e et d sont trop grand\n");
        }

    return 0;
}
