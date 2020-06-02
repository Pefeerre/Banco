void crear_pila(struct transaccion** transacciones);
void agregar_elemento_pila(struct transaccion** transacciones, int codigo, long monto);
void liberar_pila(struct transaccion* pila);
int remover_elemento_pila(struct transaccion** transacciones);
int total_cuenta(struct transaccion *transacciones);
