/*TOMA Bogdan-Nicolae-313CB*/

#include "lista2.h"

int InsL(TLDI *l, void * e)
{
    TLDI aux = malloc(sizeof(TCelula2));
    if(!aux)
        return 0;

    aux->info = e;
    //Inserare in lista vida:
    if(*l == NULL){
        aux->pre = aux->urm = aux;
        *l = aux;

        return 1;
    }
    //lista are un singur element:
    if(strcmp( ((TServer*)(*l)->urm->info)->key , ((TServer*)(*l)->info)->key ) == 0){
        if(strcmp( ((TServer *)(*l)->info)->key, ((TServer *)aux->info)->key) > 0){
            aux->urm = *l;
            aux->pre = *l;
            (*l)->urm = aux;
            (*l)->pre = aux;
            *l = aux;
        }else
        {
            aux->urm = *l;
            aux->pre = *l;
            (*l)->urm = aux;
            (*l)->pre = aux;
        }
        return 1;
    }


    TLDI p = (*l)->urm ,u;
    u = (*l)->pre;
    int ok = 0;

    //Verificare inserare la inceput de lista:
    if(strcmp( ((TServer *)(*l)->info)->key, ((TServer *)aux->info)->key) > 0){
        aux->urm = *l;
        aux->pre = u;
        u->urm = aux;
        (*l)->pre = aux;
        *l = aux;
        return 1;
    }
    //Inserare in mijlocul listei:
    for(; p != *l; p = p->urm){
        if(strcmp(((TServer*)p->info)->key, ((TServer *)aux->info)->key) > 0){
            aux->pre = p->pre;
            aux->urm = p;
            p->pre->urm = aux;
            p->pre = aux;
            ok = 1;
            break;
        }
    }
    //Inserare la sfarsit:
    if(ok == 0){
    aux->urm = *l;
    aux->pre = u;
    u->urm = aux;
    (*l)->pre = aux;
    }

    return 1;
}
int removeLista(TLDI *l,char *key, TF1 fe)
{
    TLDI p = (*l)->urm, u = (*l)->pre;

    //Verificare stergere "primul" element:
    if(strcmp( ((TServer*)(*l)->info)->key, key) == 0)
    {   
        TLDI aux = *l;
        *l = (*l)->urm;
        u->urm = *l;
        (*l)->pre = u;

        aux->urm = NULL;
        aux->pre = NULL;

        fe(aux->info);
        free(aux);
        return 1;
    }

    //Verificare stergere element care nu este "inceputul" listei:
    for(;p != *l; p = p->urm)
    {
       if(strcmp( ((TServer*)p->info)->key, key) == 0){
           TLDI aux = p;
           p = p->pre;
           p->urm = aux->urm;
           aux->urm->pre = p;

           aux->urm = NULL;
           aux->pre = NULL;

           fe(aux->info);
           free(aux);
           return 1;
       } 
    }

    return 0;
}