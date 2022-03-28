/*TOMA Bogdan-Nicolae-313CB*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "lista2.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*,FILE *out);     /* functie afisare un element */
typedef void (*TF1)(void*);   /*functie eliberare un element*/
typedef int (*TFHash)(void*,size_t);  /*functie hash*/

typedef struct
{
    size_t M;
    TFHash fh;
    TLDI *v;
} TH;

TH* IniTH(size_t M, TFHash fh);
int InsTH(TH*a, void* ae, TFCmp f);
void AfiTH(TH*a, TF afiEl,FILE * out);
void getTH(TH* h, TFCmp f, void * e, FILE *out,int cod);
void findTH(TH* h, TFCmp f, void * e, FILE *out, int cod);
int print_bucketNR(TH *h, TF afiel, FILE *out, int n);
int removeTH(TH *h, int cod, char * key, TF1 fe);
void DistrTH(TH** ah, TF1 fe);

#endif