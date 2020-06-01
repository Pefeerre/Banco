#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "hash.h"
#include "pila.h"
#include "lista.h"
#include "interfaz.h"

struct cliente* buscar_cliente(char palabra_clave[100], char tipo_de_busqueda);
struct cliente* buscar_por_id(int id);
int leer_archivo(char *nombre_archivo);
void siguente_elemento(FILE* archivo, char *a_rellenar);


int main(void){

  char buffer[100];
  int bufferid;
  int exit = 0;
  int aux_trans;
  int codigo_trans;
  ESTADO_HASH = 0;

  while(exit == 0){
    system("clear");
    printf("$$---------------MENU----------------$$\n\n");
    printf("1-  Cargar archivo de clientes\n");
    printf("2-  Agregar cliente\n");
    printf("3-  Buscar cliente\n");
    printf("4-  Eliminar cliente\n");
    printf("5-  Agregar transacciones\n");
    printf("9-  Cerrar programa\n");

    fflush(stdin);
    int opcion;
    scanf("%i",&opcion);

    switch(opcion){

      case 1:  // Cargar archivo de clientes
        if(ESTADO_HASH != 0){
          printf("1.1-  reemplazar base de datos actual\n");
          printf("1.2-  agregar archivo a base de datos\n");
          int opcion1;
          scanf("%i", &opcion1);
          if(opcion1 == 1){
            liberar_hash();
          }
        }

        printf("introduzca el nombre del archivo\n");
        scanf("%s", buffer);

        if(leer_archivo(buffer) == 0){
          system("clear");
          printf("archivo cargado con exito\n");
            sleep(1);
        }
        break;

      case 2: // Agregar cliente nuevo

        printf("agregar cliente:\n");
        struct cliente *nuevo = malloc(sizeof(struct cliente));

        while( getchar() != '\n');
        printf("\n rut (sin puntos ni guion): ");
        scanf("%i-", &(nuevo->id));

        while( getchar() != '\n');
        printf("\n Nombre: ");
        scanf("%s", nuevo->nombre);

        while( getchar() != '\n');
        printf("\n Apellido: ");
        scanf("%s", nuevo->apellido);

        while( getchar() != '\n');
        printf("\n Sexo: ");
        scanf("%s", nuevo->genero);

        while( getchar() != '\n');
        printf("\n mail: ");
        scanf("%s", nuevo->mail);

        while( getchar() != '\n');
        printf("\n Direccion: ");
        scanf("%s", nuevo->direccion);

        if(ESTADO_HASH == 0){
          crear_hash();
        }
        agregar_elemento_hash(nuevo);
        printf("cliente agregado\n");
        sleep(1);

        break;

      case 3:  // Buscar cliente

        printf("1. Buscar cliente por apellido\n");
        printf("2. Buscar cliente por nombre\n");
        printf("3. Buscar cliente por rut\n");
        int opcion_busqueda;
        scanf("%i", &opcion_busqueda);

        struct cliente* coincidencias;

        switch(opcion_busqueda){

          case 1: // buscar por apellido

            scanf("%s", buffer);
            coincidencias = buscar_cliente(buffer, 'a');
            if(coincidencias == NULL){
              printf("no se han encontrado coincidencias para %s\n", buffer);
              pausa_enter();
              break;
            }else{
              imprime_lista(coincidencias);
              pausa_enter();
            }
            liberar_lista(coincidencias);
            break;

          case 2: // buscar por nombre

            scanf("%s", buffer);
            coincidencias = buscar_cliente(buffer, 'n');
            if(coincidencias == NULL){
              printf("no se han encontrado coincidencias para %s\n", buffer);
              pausa_enter();
              break;
            }else{
              imprime_lista(coincidencias);
              pausa_enter();
            }
            liberar_lista(coincidencias);
            break;

          case 3: // buscar por id

            scanf("%i", &bufferid);
            coincidencias = buscar_por_id(bufferid);
            if(coincidencias == NULL){
              printf("no se han encontrado coincidencias para %i\n", bufferid);
              pausa_enter();
              break;
            }else{
              imprime_lista(coincidencias);
              pausa_enter();
            }
            liberar_lista(coincidencias);
            break;

        }

      break;

      case 4: // Eliminar cliente

        printf("Ingrese el apellido del cliente:\n");

        scanf("%s", buffer);
        coincidencias = buscar_cliente(buffer, 'a');
        if(coincidencias == NULL){
          printf("no se han encontrado coincidencias para %s\n", buffer);
          pausa_enter();
          break;
        }else{
          imprime_lista(coincidencias);
        }


        printf("Ingrese el RUT del cliente:\n");

        scanf("%i",&bufferid);
        if(remover_elemento_hash(buffer, bufferid)){
          system("clear");
          printf("Cliente eliminado satisfactoriamente\n");
          sleep(1);
        }
        liberar_lista(coincidencias);

        break;

      case 5: // Agrgar transacciones

        printf("Ingrese el apellido del cliente:\n");

        scanf("%s", buffer);
        coincidencias = buscar_cliente(buffer, 'a');
        if(coincidencias == NULL){
          printf("no se han encontrado coincidencias para %s\n", buffer);
          pausa_enter();
          break;
        }else{
          imprime_lista(coincidencias);
        }

        printf("Ingrese el RUT del cliente:\n");

        scanf("%i",&bufferid);
        coincidencias = buscar_por_id(bufferid);
        printf("1-  Deposito\n");
        printf("2-  Retiro\n");
        scanf("%i",&aux_trans); // crear funcion para pedir introduccion segun opciones disponibles
        codigo_trans = 1 + aux_trans*100;

        long monto_trans;
        printf("Ingrese el monto\n");
        scanf("%li", &monto_trans);

        agregar_elemento_pila(&(coincidencias->transacciones), codigo_trans, monto_trans);
        imprime_transacciones(coincidencias->transacciones);
        pausa_enter();
        break;

      case 9:
        exit = 1;
        system("clear");
        break;

    }
  }


  return 0;
}


struct cliente* buscar_cliente(char palabra_clave[100], char tipo_de_busqueda){

  struct cliente* coincidencias;
  struct cliente* it;
  crear_lista(&coincidencias);

  if(tipo_de_busqueda == 'n'){ //busqueda por nombre

    for(int i = 0; i<26; i++){
      it = hash_apellido[i];

      while(it != NULL){

        if(strncmp(it->nombre, palabra_clave, 100) == 0){
          struct cliente* buscado = malloc(sizeof(struct cliente));
          *buscado = *it;
          agregar_elemento_lista(&coincidencias, it);
        }
        it = it->next;
      }
    }
    return coincidencias;

 }else if(tipo_de_busqueda == 'a'){ //busqueda por apellido
    int indice_abecedario = toupper(palabra_clave[0]) - 65;
    it = hash_apellido[indice_abecedario];

      while(it != NULL){
        if(strncmp(it->apellido, palabra_clave, 100) == 0){
          struct cliente* buscado = malloc(sizeof(struct cliente));
          *buscado = *it;
          agregar_elemento_lista(&coincidencias, buscado);
        }
        it = it->next;
      }

    return coincidencias;
 }else{
   printf("el modo de busqueda no es valido\n");
   return NULL;
 }
}

struct cliente* buscar_por_id(int id){

  struct cliente* buscado;

  for(int i = 0; i<26; i++){
    buscado = hash_apellido[i];
    while(buscado != NULL){
      if(buscado->id == id){
        return buscado;
      }
      buscado = buscado->next;
    }
  }
  return NULL;
}

int leer_archivo(char *nombre_archivo){

  FILE*archivo = fopen(nombre_archivo, "r");

  if(archivo == NULL){
  printf("No se encuentra el archivo %s\n", nombre_archivo);
  return -1;
  }

  if(ESTADO_HASH == 0) crear_hash(); // inicializa los buckets del hash a NULL

  fscanf(archivo, "id	nombre	apellido	email	genero	direccion\n"); //avanza el archivo


  while(feof(archivo) == 0){
    struct cliente* nuevo = malloc(sizeof(struct cliente));

    fscanf(archivo,"%i  ",&(nuevo->id));
    siguente_elemento(archivo, nuevo->nombre);
    siguente_elemento(archivo, nuevo->apellido);
    siguente_elemento(archivo, nuevo->mail);
    siguente_elemento(archivo, nuevo->genero);
    siguente_elemento(archivo, nuevo->direccion);
    crear_pila(&(nuevo->transacciones));

    if(feof(archivo) == 0){
      agregar_elemento_hash(nuevo);
    }else{
      free(nuevo);
    }

  }
  fclose(archivo);
  return 0;
}
void siguente_elemento(FILE* archivo, char *a_rellenar){ //lee hasta el siguente tab y genera un espacio de tamaño ajustado para guardar el dato
  char buffer[200];
  int i = 0;

  while( i < 200 && feof(archivo) == 0){
    buffer[i] = fgetc(archivo);
    if(buffer[i] == '\t' || buffer[i] == '\n'){
      break;
    }
    i++;
  }
  buffer[i] = 0; //indica final del string

  if(i != 0){
    strcpy(a_rellenar, buffer);
  }

}
