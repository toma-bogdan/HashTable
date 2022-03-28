/*TOMA Bogdan-Nicolae-313CB*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#ifndef _LISTA_DUBLU_INLANTUITA_
#define _LISTA_DUBLU_INLANTUITA_

typedef struct celula2
{
  void *info;              /* adresa element extern */
  struct celula2 *pre, *urm;  /* legaturi spre celulele vecine */
} TCelula2, *TLDI;

typedef struct 
{
    char* key;
    char* value;
}TServer;

typedef void (*TF1)(void*);
int InsL(TLDI *l, void * e);
int removeLista(TLDI *l,char *key,TF1 fe);

#endif