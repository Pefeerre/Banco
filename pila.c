#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "pila.h"
#include "lista.h"


void crear_pila(struct transaccion** transacciones){
  (*transacciones) = NULL;
}

void agregar_elemento_pila(struct transaccion** transacciones, int codigo, long monto){

  struct transaccion* nueva_transaccion = malloc(sizeof(struct transaccion));
  nueva_transaccion->codigo_operacion = codigo;
  nueva_transaccion->monto = monto;

  if(*transacciones == NULL){
    (*transacciones) = nueva_transaccion;
    (*transacciones)->next = NULL;

  }else{
    struct transaccion* tmp = (*transacciones);
    (*transacciones) = nueva_transaccion;
    (*transacciones)->next = tmp;
  }
}

int remover_elemento_pila(struct transaccion** transacciones){

  if(*transacciones == NULL){
    printf("no hay transacciones por remover\n");
    return 0;

  }else{
    struct transaccion* tmp = (*transacciones);
    *transacciones = (*transacciones)->next;
    free(tmp);
  }
  return 1;
}

void liberar_pila(struct transaccion* pila){
  struct transaccion* tmp;
  while(pila != NULL){
    tmp = pila->next;
    free(pila);
    pila = tmp;
  }
}

int total_cuenta(struct transaccion *transacciones){
  int total = 0;
  struct transaccion *it = transacciones;
  while(it != NULL){
    if(it->codigo_operacion == 101) {
      total = total + it->monto;
    }else{
      total = total - it->monto;
    }
    it = it->next;
  }
  return total;
}

void monto_minimo(struct cliente** lista, int monto_min){
  
  struct cliente *it;

  for(int i = 0; i<26; i++){
      it = hash_apellido[i];
      while(it != NULL){
        if(it->transacciones != NULL){
          if(it->transacciones->codigo_operacion == 101 && it->transacciones->monto > monto_min){
          agregar_elemento_lista(lista, it);
          }
        }
        it = it->next; 
      }
  }
}

void monto_maximo(struct cliente** lista){

  struct cliente *it;
  for(int i = 0; i<26; i++){
    it = hash_apellido[i];
    while(it != NULL){
      
      if(it->transacciones != NULL){
        agregar_elemento_ordenado(lista, it);
      }
      it = it->next; 
    }
  } 
}
