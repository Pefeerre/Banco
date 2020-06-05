Alumnos: Diego Aguilar, Pedro Fresno
Sección 1.
Este programa sirve para administrar cuentas de un banco, recibe los datos en archivos .txt en un formato estándar y tambien por input al terminal. Cuenta con 8 funciones distintas.
Se han agregado funciones específicas para la interfaz del programa y se han puesto en la librería interfaz.h. Estas funciones no están necesariamente dentro de los contenidos evaluados para esta tarea. Los únicos errores encontrados a estas funciones corresponden a cuando se ingresan letras al pedirse numeros en scanf.
La funcion Formato_Titulos() formatea cadenas de texto con mayusculas y minusculas, y esta se usa cada vez que se introduce texto cosa de que los elementos de un cliente no deben introducirse necesariamente con mayusculas y minusculas especificas.
Las funciones crear_lista, crear_hash y crear_pila lo único que hacen es inicializar los punteros de cabecera en NULL.
La función de buscar cliente devuelve un arreglo de punteros de máximo 10, que apuntan directamente a los elementos del hash. Esta función se usa en cada operación que implique editar un cliente o simplemente mostrarlo. Luego, estos son seleccionados refiriéndose al índice (el mostrado en el terminal, menos uno) del arreglo de punteros de clientes coincidentes con la búsqueda.
