#include <stdio.h>
#include <ctype.h>
#include "hash.h"
#include "interfaz.h"

void imprime_apellidos(char desde, char hasta){
  int inf = toupper(desde) - 65;
  int sup = toupper(hasta) - 65;

  for(int i = inf; i<sup+1; i++){
    struct cliente *it = hash_apellido[i];
    while(it != NULL){
     printf("%s \n", it->apellido);
     it = it->next;
    }
  }
}

void imprime_lista(struct cliente* it){

  while(it != NULL){
  printf("---------------------------------\n");
  printf("| cliente:  %s %s\n", it->nombre,it->apellido);
  printf("|                 \n");
  printf("| id:       %i\n",it->id);
  printf("----------------------------------\n\n");
  it = it->next;
  }
   
}

void imprime_transacciones(struct transaccion* it){
  if(it == NULL){
    printf("la transacción no existe\n");
  }else{  
    while(it != NULL){
      if(it->codigo_operacion == 101){
        printf("Deposito por: %i\n", it->monto);
      }else{
        printf("Retiro por: %i\n", it->monto);
      }
    it = it->next;
    }
  } 
}

void imprime_cliente(struct cliente* cliente){
  if(cliente == NULL){
    printf("el cliente no extiste\n");
  }else{
    printf("Cliente:   %s %s\n", cliente->nombre,cliente->apellido);
    printf("id:        %i\n",cliente->id);
    printf("genero:    %s\n", cliente->genero);
    printf("mail:      %s\n", cliente->mail);
    printf("direccion: %s\n", cliente->direccion);
  }
}

void pausa_enter(){

  while( getchar() != '\n');
  getchar();

}