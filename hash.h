struct transaccion{
  int codigo_operacion;
  int monto;
  struct transaccion* next;
};

struct cliente{
  int id;
  char nombre[60];
  char apellido[60];
  char mail[80];
  char genero[10]; 
  char direccion[100];
  struct transaccion* transacciones;
  struct cliente* next;
};


void crear_hash();
void agregar_elemento_hash(struct cliente* nuevo);
int remover_elemento_hash(char apellido[200], int rut);
void liberar_hash();
int ESTADO_HASH; //indica si el hash ya está creado

struct cliente* hash_apellido[26];  //cada espacio de este arreglo representa una letra del abecedario de forma ordenada.
