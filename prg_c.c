#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "prg_c.h"

/****************************************
@name: pgcd
@description: Fonction qui donne le pgcd
@parameters:
-long p: valeur
-long q: valeur
@return: pgcd
*****************************************/
long pgcd(long p, long q){
    if(q == 0){
        return p;
    }else{
        return pgcd(q, p%q);
    }
}

/*********************************************************
@name: function_n
@description: Fonction qui donne la multiplication de p*q
@parameters:
-long p: valeur
-long q: valeur
@return: n
**********************************************************/
long function_n(long p, long q){
    return p*q;
}

/***********************************
@name: phi_n
@description: Fonction qui phi de n
@parameters:
-long p: valeur
-long q: valeur
@return: phi
************************************/
long phi_n(long p, long q){
    return (p - 1)*(q - 1);
}

/***********************************************************************
@name: calcul_e
@description: Fonction qui permet de calcule l'exposant de chiffrement e
@parameters:
-long p: valeur
-long q: valeur
@return: e
************************************************************************/
long calcul_e(long p, long q){
    long phi = phi_n(p,q);
    long e = random_numberC(phi);
    BOOL boolean = TRUE;
    while(boolean){
        if((e>0) && (e<phi) && (pgcd(e,phi)==1)){
            boolean = FALSE;
        }else{
            e = random_numberC(phi);
        }
    }
    return e;
}

/**********************************************************
@name: random_numberC
@description: Fonction qui g¨¦n¨¦re al¨¦atoirement des valeurs
@parameters:
-long n: valeur
@return: random entre 0 et n
***********************************************************/
long random_numberC(long n){
    return (rand()% n+1);
}

/****************************************************************
@name: calcul_d
@description: Fonction qui permet de calculer l'inverse modulaire
@parameters:
-long p: valeur
-long q: valeur
-long e: valeur
@return: d
*****************************************************************/
long calcul_d(long p, long q, long e){
    long phi = phi_n(p,q);
    int i = 0;
    long r[10000];
    long quo[10000];
    long v[10000];
    v[0] = 0;
    v[1] = 1;
    BOOL boolean = TRUE;
    while(boolean){
        quo[i+1] = phi/e;
        //printf("q[%d] = %ld/%ld = %ld\n", i+1,phi,e, quo[i+1]);
        r[i+1] = e;
        //printf("r[%d] = %ld\n", i+1,e);
        r[i+2] = phi%e;
        //printf("r[%d] = %ld mod %ld = %ld\n", i+2,phi,e, r[i+2]);
        phi = r[i+1];
        //printf("phi = %ld\n",r[i+1]);
        e = r[i+2];
        //printf("e = %ld\n", r[i+2]);
        r[i] = quo[i+1] * r[i+1] + r[i+2];
        //printf("r[%d] = %ld * %ld + %ld\n", i, quo[i+1], r[i+1], r[i+2]);
        if(r[i+2]==0){
            boolean = FALSE;
        }else{
            i++;
        }
    }
    //printf("i = %d\n", i);
    int j;
    for(j = 2; j<=i+1; ++j){
        //printf("j = %d\n", j);
        v[j] = v[j-2] - quo[j-1] * v[j-1];
        //printf("v[%d] = %ld - %ld * %ld = %ld\n", i, v[j-2], quo[j-1], v[j-1], v[j]);
    }
    //printf("j = %d\n", j);
    int d;
    if(v[j-1]<0){
        d = phi_n(p,q)+v[j-1]%phi_n(p,q);
    }else{
        d = v[j-1]%phi_n(p,q);
    }
    return d;
}

/*********************************************************
@name: estPremier
@description: Fonction qui donne si la valeur est premier
@parameters:
-long n: valeur
@return: TRUE si est premier sinon FALSE
**********************************************************/
BOOL estPremier(long n){
    BOOL boolean;
    int i;
    for(i=2; i<=floor(sqrt(n));++i){
        if(n%i ==0){
            boolean = FALSE;
            return boolean;
        }
    }
    boolean = TRUE;
    /*if((n<=1) || (n % 2 == 0)||(n % 3 == 0)){
        return boolean = FALSE;
    }else if(n<=3){
        return boolean = TRUE;
    }
    i = 5;
    while(i*i<=n){
        if((n % i == 0)||(n % (i + 2) == 0)){
            return boolean = FALSE;
        }
        i = i + 6;
    }*/
    /*if (n == 2){
        boolean = TRUE;
        return boolean;
    }else if(n % 2 == 0){
        boolean = FALSE;
        return boolean;
    }
    for (i = 3; i * i <= n; i += 2){
        if (n % i == 0){
                boolean = FALSE;
                return boolean;
        }
    }*/
    return boolean;
}

/**************************************************
@name: generePQ
@description: Fonction qui genere un nombre premier
@parameters:

@return: un nombre premier;
***************************************************/
long generePQ(){
    long p = random_numberC(100);
    BOOL boolean = TRUE;
    while(boolean){
        if(estPremier(p)==TRUE){
            boolean = FALSE;
        }else{
            p = random_numberC(100);
        }
    }
    return p;
}
