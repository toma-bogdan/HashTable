/*TOMA Bogdan-Nicolae-313CB*/

#include "thash.h"

TH* IniTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLDI *) calloc(M, sizeof(TLDI));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}
void getTH(TH* h, TFCmp f, void * e, FILE *out,int cod)
{
    TLDI p, el;
    
    p = h->v[cod];
        if(p){
            for(el = p; ; el = el->urm){
                if(f( ((TServer*)el->info)->key, (char*)e) == 1){
                    fprintf(out,"%s\n",((TServer*)el->info)->value);
                    return;
                }
                if(el->urm == p)
                    break;
            }
        }
        fprintf(out,"NULL\n");
}
void findTH(TH* h, TFCmp f, void * e, FILE *out,int cod)
{
    TLDI p, el;
    int ok = 0;
    
    p = h->v[cod];
        if(p){
            for(el = p; ; el = el->urm){
                if(f( ((TServer*)el->info)->key, (char*)e) == 1){
                    fprintf(out,"True\n");
                    ok = 1;
                    break;
                }
                if(el->urm == p)
                    break;
            }
        }
    if(ok == 0){
        fprintf(out,"False\n");
    }
}
void AfiTH(TH* ah, TF afiEl, FILE * out)
{
    TLDI p, el;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            fprintf(out,"%d: ",i);
            for(el = p; ; el = el->urm){
                afiEl(el->info,out);
                if(el->urm == p)
                    break;
            }
            fprintf(out,"\n");
        }
    }
}
int print_bucketNR(TH *h, TF afiel, FILE *out, int n)
{
    TLDI p;
    p = h->v[n];
    if(!p){
        fprintf(out,"VIDA\n");
        return 0;
    }
    for(; ; p = p->urm){
        afiel(p->info,out);
        if(p->urm == h->v[n])
            break;
    }
    fprintf(out,"\n");
    return 1;
}
int InsTH(TH*a, void* ae, TFCmp f)
{
    int cod = a->fh(ae,a->M), rez;
    TLDI el;
    for(el = a->v[cod]; el != NULL; el = el->urm) {
        if (f(el->info, ae) == 1)
            return 0;
        if(el->urm == a->v[cod])
            break;
    }

    rez = InsL(a->v+cod, ae); 
    return rez;
}
int removeTH(TH *h, int cod, char * key, TF1 fe)
{
    TLDI l = h->v[cod];
    //Verificare lista vida:
    if(!l)
        return 0;
    
    //Verificare lista cu un singur element + stergere:
    if(l == l->urm){
            if(strcmp( ((TServer*)l->info)->key, key) == 0){
            l->urm = NULL;
            l->pre = NULL;
            fe(l->info);
            free(l);
            h->v[cod] = NULL;
            return 1;
        }
    }
    int rez;
    rez = removeLista(&h->v[cod],key,fe);

    return rez;
}
void DistrTH(TH** ah, TF1 fe)
{
    TLDI * p, el, aux;

    //parcurgere cu pointeri
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->urm;
            aux->pre = NULL;
            fe(aux->info);
            free(aux);
            if(el == *p)
                break;
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}