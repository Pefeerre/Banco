#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "pila.h"


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
    printf("no hay transacciones por remover");
    return 0;

  }else{
    struct transaccion* tmp = (*transacciones)->next;
    free(*transacciones);
    *transacciones = tmp;
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
