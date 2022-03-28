/*TOMA Bogdan-Nicolae-313CB*/

#include <stdio.h>
#include "lista2.h"
#include <string.h>
#include "thash.h"

int codHash(void * element, size_t M)
{
    TServer * server = (TServer*) element;
    int s = 0, i = 0;
    char * key = server->key;

    while(key[i] != '\0'){
        s += (int)key[i] - '\0';
        i++;
    }
    return (s%M);
}
void afisareServer(void* element,FILE *out){
    TServer * server = (TServer *) element;
    fprintf(out,"%s ",server->value);
}
int cmpServer(void *e1, void *e2){
    TServer * server1 = (TServer*) e1;
    TServer * server2 = (TServer*) e2;

    if(strcmp(server1->key,server2->key) != 0){
        return 0;
    }
    return 1;
}
int cmpKey(void *e1, void *e2){
    char * key1 = (char*)e1;
    char * key2 = (char*)e2;

    if(strcmp(key1,key2) != 0)
        return 0;
    return 1;
}
void freeServer(void * el){
    free( ((TServer*)el)->key );
    free( ((TServer*)el)->value );
    free(el);
}
int main(int argc, char **argv)
{   
    size_t M;
    char filename1[50], filename2[50];
    M = atoi(argv[1]);

    strcpy(filename1,argv[2]);
    strcpy(filename2,argv[3]);

    FILE *in = fopen(filename1,"rt");
    if(in == NULL){
        printf("eroare deschidere fisier");
        return -1;
    }
    FILE *out = fopen(filename2,"wr");
    if(out == NULL){
        printf("eroare deschidere fisier");
        return -1;
    }

    TH *h = NULL;
    h = (TH *)IniTH(M,codHash);

    char * line = NULL;
	size_t len = 0;

    while (getline(&line, &len, in) != -1){
        char * comanda = strtok(line, " ");
        if(comanda[strlen(comanda) - 1] == '\n'){
               comanda[strlen(comanda) - 1] = '\0';
        }

        if(strcmp(comanda,"put") == 0){
            TServer *server = malloc(sizeof(TServer));

            char * key = strtok(NULL," ");
            char * value = strtok(NULL," ");

            if(value[strlen(value) - 1] == '\n'){
               value[strlen(value) - 1] = '\0';
            }

            server->key = calloc(strlen(key) + 5,sizeof(char));
            server->value = calloc(strlen(value) + 5,sizeof(char));

            strcpy(server->key, key);
            strcpy(server->value, value);

            int rez;
            rez = InsTH(h,(void*)server,cmpServer);
            if(!rez)
                freeServer(server);
        }
        if(strcmp(comanda,"print") == 0){
            AfiTH(h,afisareServer,out);
        }

        if(strcmp(comanda,"get") == 0){
            char * key3 = strtok(NULL," ");
            if(key3[strlen(key3) - 1] == '\n'){
               key3[strlen(key3) - 1] = '\0';
            }
            TServer * server = malloc(sizeof(TServer));              //vom folosi server pentru a afla codul key-ului citit
            server->key = calloc(strlen(key3) + 5,sizeof(char));

            strcpy(server->key, key3);
            int cod = codHash(server,M);
            getTH(h,cmpKey,key3,out,cod);

            free(server->key);
            free(server);
        }

        if(strcmp(comanda,"remove") == 0){
            char * key2 = strtok(NULL," ");
            if(key2[strlen(key2) - 1] == '\n'){
               key2[strlen(key2) - 1] = '\0';
            }
            TServer * server = malloc(sizeof(TServer));              //vom folosi server pentru a afla codul key-ului citit
            server->key = calloc(strlen(key2) + 5,sizeof(char));

            strcpy(server->key, key2);
            int cod = codHash(server,M);

            removeTH(h,cod,key2,freeServer);
            free(server->key);
            free(server);
        }
        if(strcmp(comanda,"print_bucket") == 0){
            char * number = strtok(NULL," ");
            if(number[strlen(number) - 1] == '\n'){
               number[strlen(number) - 1] = '\0';
            }
            int n = atoi(number);
            if(n < h->M)
                print_bucketNR(h,afisareServer,out,n);
        }
        if(strcmp(comanda,"find") == 0){
            char * key1 = strtok(NULL," ");
            if(key1[strlen(key1) - 1] == '\n'){
               key1[strlen(key1) - 1] = '\0';
            }
             TServer * server = malloc(sizeof(TServer)); //vom folosi server pentru a afla codul key-ului citit
            server->key = calloc(strlen(key1) + 5,sizeof(char));

            strcpy(server->key, key1);
            int cod = codHash(server,M);
            findTH(h,cmpKey,key1,out,cod);

            free(server->key);
            free(server);
        }
    }
    free(line);
    DistrTH(&h,freeServer);
    fclose(in);
    fclose(out);
    return 0;
}