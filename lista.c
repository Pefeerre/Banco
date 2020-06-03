#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

void crear_lista(struct cliente** lista){
  *lista = NULL;
}

int agregar_elemento_lista(struct cliente** lista, struct cliente *elemento){
  struct cliente* nuevo_elemento = malloc(sizeof(struct cliente));
  *nuevo_elemento = *elemento;


  if(*lista == NULL){
    *lista = nuevo_elemento;
    nuevo_elemento->next = NULL;
  }else{
    struct cliente* it = *lista;
    while(it->next != NULL){
      it = it->next;
    }
    it->next = nuevo_elemento;
    nuevo_elemento->next = NULL;
  }
  return 0;
}

void liberar_lista(struct cliente* lista){

  if(lista == NULL){
    printf("la lista a liberar no existe\n");
  }else{
    struct cliente* tmp;
    while(lista->next != NULL){
      tmp = lista->next;
      free(lista);
      lista = tmp;
    }
    free(lista); // libera ultimo espacio
   }
}
