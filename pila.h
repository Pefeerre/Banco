void crear_pila(struct transaccion** transacciones);
void agregar_elemento_pila(struct transaccion** transacciones, int codigo, long monto);
void liberar_pila(struct transaccion* pila);