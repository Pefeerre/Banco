#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "hash.h"
#include "pila.h"
#include "lista.h"
#include "interfaz.h"

#define BUFF 1000
#define BUF_COINCIDENCIAS 10

struct cliente** buscar_cliente(char palabra_clave[100], char tipo_de_busqueda, int* n_coincidencias);
struct cliente* buscar_por_id(int id);
int leer_archivo(char *nombre_archivo);
void siguente_elemento(FILE* archivo, char *a_rellenar);


int main(void){

  char buffer[BUFF];
  int bufferint;
  int exit = 0;
  ESTADO_HASH = 0;
  struct cliente* seleccion;
  int n_coincidencias;

  while(exit == 0){
    system("clear");
    printf("$$---------------MENU----------------$$\n\n");
    printf("1-  Cargar archivo de clientes\n");
    printf("2-  Agregar cliente\n");
    printf("3-  Buscar cliente\n");
    printf("4-  Eliminar cliente\n");
    printf("5-  Agregar transacciones\n");
    printf("6-  Deshacer ultima transaccion cliente\n");
    printf("7-  Generar lista segun ultima transaccion\n");
    printf("8-  Generar lista con los clientes con mas dinero\n");
    printf("9-  Cerrar programa\n");

    int opcion = pide_opcion(9);

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
          mensaje_feedback("archivo cargado con exito\n");
        }
        break;

      case 2: // Agregar cliente nuevo

        printf("agregar cliente:\n");
        struct cliente *nuevo = malloc(sizeof(struct cliente));

        printf("\n rut (sin puntos ni guion): ");
        scanf("%i-", &(nuevo->id));

        while( getchar() != '\n');
        printf("\n Nombre: ");
        scanf("%s", nuevo->nombre);
        Formato_Titulos(nuevo->nombre);

        while( getchar() != '\n');
        printf("\n Apellido: ");
        scanf("%s", nuevo->apellido);
        Formato_Titulos(nuevo->apellido);

        while( getchar() != '\n');
        printf("\n Sexo: ");
        scanf("%s", nuevo->genero);
        Formato_Titulos(nuevo->genero);

        while( getchar() != '\n');
        printf("\n mail: ");
        scanf("%s", nuevo->mail);

        while( getchar() != '\n');
        printf("\n Direccion: ");
        siguente_elemento(stdin, nuevo->direccion);
        Formato_Titulos(nuevo->direccion);

        crear_pila(&(nuevo->transacciones));

        if(ESTADO_HASH == 0){
          crear_hash();
        }
        agregar_elemento_hash(nuevo);
        mensaje_feedback("cliente agregado");

        break;

      case 3:  // Buscar cliente

        printf("1. Buscar cliente por apellido\n");
        printf("2. Buscar cliente por nombre\n");
        printf("3. Buscar cliente por rut\n");
        int opcion_busqueda = pide_opcion(3);

        struct cliente** coincidencias;

        switch(opcion_busqueda){

          case 1: // buscar por apellido
            printf("Ingrese el apellido del cliente: ");

            scanf("%s", buffer);
            Formato_Titulos(buffer);
            coincidencias = buscar_cliente(buffer, 'a',&n_coincidencias);
            if(*coincidencias == NULL){
              printf("no se han encontrado coincidencias para %s\n", buffer);
              pausa_enter();
              break;
            }
            printf("\n    SELECCIONE CLIENTE PARA VER DETALLE:\n");
            int opcion3 = pide_opcion(n_coincidencias);
            seleccion = coincidencias[opcion3-1];
            imprime_cliente_detalle(seleccion);
            pausa_enter();
            break;

          case 2: // buscar por nombre
            printf("Ingrese el nombre del cliente: ");

            scanf("%s", buffer);
            Formato_Titulos(buffer);
            coincidencias = buscar_cliente(buffer, 'n', &n_coincidencias);
            if(*coincidencias == NULL){
              printf("no se han encontrado coincidencias para %s\n", buffer);
              pausa_enter();
              break;
            }
            printf("\n    SELECCIONE CLIENTE PARA VER DETALLE:\n");
            opcion3 = pide_opcion(n_coincidencias);
            seleccion = coincidencias[opcion3-1];
            imprime_cliente_detalle(seleccion);
            pausa_enter();
            break;

          case 3: // buscar por id
            printf("ingrese id: ");

            scanf("%i", &bufferint);
            struct cliente* buscado  = buscar_por_id(bufferint);
            if(coincidencias == NULL){
              printf("no se han encontrado coincidencias para %i\n", bufferint);
              pausa_enter();
              break;
            }else{
              imprime_cliente_detalle(buscado);
              pausa_enter();
            }
            break;

        }

      break;

      case 4: // Eliminar cliente

        printf("Ingrese el apellido del cliente: ");

        scanf("%s", buffer);
        Formato_Titulos(buffer);
        coincidencias = buscar_cliente(buffer, 'a',&n_coincidencias);
        if(*coincidencias == NULL){
          printf("no se han encontrado coincidencias para %s\n", buffer);
          pausa_enter();
          break;
        }

        printf("seleccione al cliente:\n");
        int opcion4 = pide_opcion(n_coincidencias);
        seleccion = coincidencias[opcion4-1];

        if(remover_elemento_hash(seleccion->apellido,seleccion->id)){
          mensaje_feedback("Cliente eliminado satisfactoriamente\n");
        }

        break;

      case 5: // Agregar transacciones

        printf("Ingrese el apellido del cliente: ");

        scanf("%s", buffer);
        Formato_Titulos(buffer);
        coincidencias = buscar_cliente(buffer, 'a',&n_coincidencias);
        if(*coincidencias == NULL){
          printf("no se han encontrado coincidencias para %s\n", buffer);
          pausa_enter();
          break;
        }

        printf("seleccione al cliente:\n");
        int opcion5 = pide_opcion(n_coincidencias);
        seleccion = coincidencias[opcion5-1];

        printf("1-  Deposito\n");
        printf("2-  Retiro\n");
        int opcion_trans = pide_opcion(2);
        int codigo_trans = 1 + opcion_trans*100;

        long monto_trans;
        printf("Ingrese el monto\n");
        fflush(stdin);
        scanf("%li", &monto_trans);
        if(codigo_trans == 201 && monto_trans  > total_cuenta(seleccion->transacciones)){
            printf("El monto a retirar excede el maximo\n");
        }else{
          agregar_elemento_pila(&(seleccion->transacciones), codigo_trans, monto_trans);
          printf("transaccion hecha\n");
        }

        printf("total en cuenta: %i\n", total_cuenta(seleccion->transacciones));
        pausa_enter();
        break;

      case 6: // Eliminar ultima transaccion
        printf("Ingrese el apellido del cliente: ");

        scanf("%s", buffer);
        Formato_Titulos(buffer);
        coincidencias = buscar_cliente(buffer, 'a',&n_coincidencias);
        if(*coincidencias == NULL){
          printf("no se han encontrado coincidencias para %s\n", buffer);
          pausa_enter();
          break;
        }

        printf("seleccione al cliente:\n");
        int opcion6 = pide_opcion(n_coincidencias);
        seleccion = coincidencias[opcion6-1];

        if(remover_elemento_pila(&(seleccion->transacciones))){
          mensaje_feedback("ultima transaccion ha sido removida\n");
          printf("lista de transacciones:\n");
          imprime_transacciones(seleccion->transacciones);
          printf("total en cuenta: $ %i\n",total_cuenta(seleccion->transacciones));
          pausa_enter();
        }
        break;

      case 7:

        printf("Ingrese el monto minimo de deposito:");
        scanf("%i", &bufferint);

        struct cliente* lista_min;
        crear_lista(&lista_min);
        monto_minimo(&lista_min, bufferint);
        imprime_lista(lista_min);
        pausa_enter();

        break;

      case 8:

        printf("Ingrese el numero de clientes que desea ver:");
        scanf("%i", &bufferint);

        struct cliente* lista_top;
        crear_lista(&lista_top);
        monto_maximo(&lista_top);
        imprime_lista_detalle(lista_top, bufferint);
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


struct cliente** buscar_cliente(char palabra_clave[100], char tipo_de_busqueda, int *n_coincidencias){
//crea un arreglo de punteros de los elementos del hash que coincidan
  struct cliente** coincidencias = malloc(BUF_COINCIDENCIAS*sizeof(struct cliente*));
  *coincidencias = NULL;
  struct cliente* it;
  *n_coincidencias = 0;
  if(tipo_de_busqueda == 'n'){ //busqueda por nombre

    for(int i = 0; i<26; i++){
      it = hash_apellido[i];

      while(it != NULL){

        if(strncmp(it->nombre, palabra_clave, 100) == 0 && *n_coincidencias < BUF_COINCIDENCIAS){
          coincidencias[*n_coincidencias] = it;
          (*n_coincidencias)++;
          imprime_cliente(it, *n_coincidencias);
        }
        it = it->next;
      }
    }
    return coincidencias;

 }else if(tipo_de_busqueda == 'a'){ //busqueda por apellido
    int indice_abecedario = toupper(palabra_clave[0]) - 65;
    it = hash_apellido[indice_abecedario];

      while(it != NULL){

        if(strncmp(it->apellido, palabra_clave, 100) == 0 && *n_coincidencias < BUF_COINCIDENCIAS){
          coincidencias[*n_coincidencias] = it;
          (*n_coincidencias)++;
          imprime_cliente(it, *n_coincidencias);
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
  pausa_enter();
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
void siguente_elemento(FILE* archivo, char *a_rellenar){ //lee hasta el siguente tab
  char buffer[200];
  int i = 0;

  while( i < 200 && feof(archivo) == 0){
    buffer[i] = fgetc(archivo);
    if(buffer[i] == '\t' || buffer[i] == '\n'){
      break;
    }
    i++;
  }
  while(i<100){
      buffer[i] = 0; //indica final del string
      i++;
  }

    strcpy(a_rellenar, buffer);

}
