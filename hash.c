#include<stdio.h>
#include "hash.h"
#include <ctype.h>
#include <string.h>
#include<stdlib.h>
#include "pila.h"
#include "lista.h"
#include "interfaz.h"


void agregar_elemento_hash(struct cliente* nuevo){

  int indice_abecedario = toupper(nuevo->apellido[0]) - 65;        //codigo ASCII a indices del 0 al 25
  agregar_elemento_lista(&hash_apellido[indice_abecedario],nuevo);

}

void crear_hash(){
  for(int i = 0; i< 26; i++){
    hash_apellido[i] = NULL;
  }
  ESTADO_HASH = 1;
}

void liberar_hash(){
    for(int i = 0; i< 26; i++){
      if(hash_apellido[i] != NULL){
        liberar_lista(hash_apellido[i]);
      }
  }
  ESTADO_HASH = 0;
}

int remover_elemento_hash(char apellido[200], int rut){
  int indice_abecedario = toupper(apellido[0]) - 65;

  if((strcmp(hash_apellido[indice_abecedario]->apellido, apellido) == 0) && (hash_apellido[indice_abecedario]->id == rut)){ //Si es que coincide con el primero en el bucket
    struct cliente* tmp = hash_apellido[indice_abecedario]->next;
    free(hash_apellido[indice_abecedario]);
    hash_apellido[indice_abecedario] = tmp;
  }else{
    struct cliente* it = hash_apellido[indice_abecedario];

    while(it->next != NULL && (strncmp(it->next->apellido, apellido,200) || (it->next->id != rut))){
      it = it->next;
    }
    if(it->next == NULL){
      printf("El cliente que desea eliminar no existe\n");
      pausa_enter();
      return 0;
    }else{
      struct cliente* tmp = it->next->next;
      liberar_pila(it->next->transacciones);
      free(it->next);
      it->next = tmp;

    }
  }
  return 1;
}
