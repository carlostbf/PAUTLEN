#ifndef GENERACION_H
#define GENERACION_H
#include "types.h"


/**
 * @brief: escribe en el fichero la cabecera de compatibilidad para que el codigo nasm funcione tambien en otros SO
 * @param: fpams: el archivo donde se va a escribir
 */
void escribir_cabecera_compatibilidad(FILE* fpasm);

/**
 * @brief: escribe la subseccion .data del codigo ensamblador con los mensajes de error en caso de division por cero y de acceso a un array fuera de su rango
 * @param: fpams: el archivo donde se va a escribir
 */
void escribir_subseccion_data(FILE* fpasm);

/**
 * @brief: escribe la cabecera de la subseccion .bss del codigo ensamblador donde se declaran las variables de uso global. Tambien declara por defecto la variable auxiliar __esp
 * @param: fpams: el archivo donde se va a escribir
 */
void escribir_cabecera_bss(FILE* fpasm);

/**
 * @brief: escribe, en la subseccion .bss, una variable global, dado un tipo y un tamano (si resulta ser un array)
 * @param: fpams: el archivo donde se va a escribir
 * @param: nombre: el nombre de la variable a declarar
 * @param: tipo: el tipo de dato de la variable a declarar. puede ser ENTERO o BOOLEANO
 * @param: tamano: el tamano que ocupa la variable a declarar. deberia ser 1 si se trata de un escalar. De lo contrario, el numero de elementos del array
 */
void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano);

/**
 * @brief: escribe el comienzo del segmento de codigo, con las declaraciones de las funciones de alfalib.o
 * @param: fpams: el archivo donde se va a escribir
 */
void escribir_segmento_codigo(FILE* fpasm);

/**
 * @brief: escribe la etiquieta de inicio: main y ademas guarda en [__esp] la direccion actual de la pila (esp) para poder recuperarla en caso de error
 * @param: fpams: el archivo donde se va a escribir
 */
void escribir_inicio_main(FILE* fpasm);

/**
 * @brief:escribe el final del codigo ensamblador, con la gestion de errores (como division por 0 o acceso fuera del rango de un vector)
 * @param: fpams: el archivo donde se va a escribir
 */
void escribir_fin(FILE* fpasm);

/**
 * @brief: escribe en la pila un operando, que puede ser un valor o el contenido de una direccion de memoria
 * @param: fpams: el archivo donde se va a escribir
 * @param: nombre: el nombre del operando a escribir. si fuera un numero, sería el string de dicho numero p.e "27". De lo contrario es el nombre de la variable
 * @param: es_var: un flag que indica si el operando es un literal (FALSE) o si es una variable (TRUE) en cuyo caso se escribe su valor
 */
void escribir_operando(FILE * fpasm, char * nombre, int es_var);

/**
 * @brief: escribe en la pila un operando que va a ser la direccion de un elemento de un vector (indexado). Necesariamente, el indice con el que se indexa el vector
 * debe encontrarse en la pila, ya sea como valor o como direccion, pues se puede indexar con o bien como [1] o bien [indice] siendo indice una variable
 * @param: fpams: el archivo donde se va a escribir
 * @param: nombre: el nombre de la base del vector
 * @param: indice_es_direccion: un flag que indica si el indice que hay en la cima de la pila es una direccion (TRUE) o un valor (FALSE)
 * @param: rango: es el ultimo indice valido para el vector. Se utiliza para comprobar que no hay error de acceso (tratar de acceder fuera de los limites del vector)
 */
void escribir_elemento_vector(FILE* fpasm, char* nombre, int indice_es_direccion, int rango);

/**
 * @brief: escribe el codigo nasm para asignar a una variable aquello que haya en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: nombre: es el nombre de la variable donde se va a realizar la asignacion (parte derecha de la asignacion)
 * @param: es_referencia: es un flag que determina si lo que hay en la cima de la pila es una direccion (TRUE) o un valor (FALSE)
 */
void asignar(FILE * fpasm, char * nombre, int es_referencia);

/**
 * @brief: escribe el codigo nasm para asignar a un elemento de un vector. En la cima de la pila debe estar la parte derecha de la asignacion y debajo de esta, la
 * direccion en donde se va a asignar (la parte izquierda de la asignacion)
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia: un flag que determina si la parte derecha de la asignacion es una direccion (TRUE) o es un valor (FALSE)
 */
void asignar_vector(FILE * fpasm, int es_referencia);

/**
 * @brief: escribe el codigo nasm para realizar la suma de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void sumar(FILE * fpasm, int es_referencia_1, int es_referencia_2);

/**
 * @brief: escribe el codigo nasm para realizar la operacion de cambio de signo sobre el operando que se encuentra en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia: un flag que determina si el elemento que esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void cambiar_signo(FILE * fpasm, int es_referencia);//probar

/**
 * @brief: escribe el codigo nasm para realizar la operacion de negacion sobre el operando que se encuentra en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia: un flag que determina si el elemento que esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: cuantos_no: es un contador para el salto interno que requiere esta operacion.
 */
void no(FILE * fpasm, int es_referencia, int cuantos_no);//probar

/**
 * @brief: escribe el codigo nasm para realizar una llamada a la funcion de alfalib.o que lee de stdin
 * @param: fpams: el archivo donde se va a escribir
 * @param: tipo: es un flag que indica si el valor que se va a leer es de tipo entero (ENTERO) o booleano (BOOLEANO)
 */
void leer(FILE * fpasm, char * nombre, int tipo);

/**
 * @brief: escribe el codigo nasm para realizar una llamada a la funcion de alfalib.o que escribe en stdout
 * @param: fpams: el archivo donde se va a escribir
 * @param: tipo: es un flag que indica si el valor que se va a escribir es de tipo entero (ENTERO) o booleano (BOOLEANO)
 */
void escribir(FILE * fpasm, int es_referencia, int tipo);

/**
 * @brief: escribe el codigo nasm para realizar la resta de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void restar(FILE * fpasm, int es_referencia_1, int es_referencia_2);//probar

/**
 * @brief: escribe el codigo nasm para realizar la multiplicacion de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void multiplicar(FILE * fpasm, int es_referencia_1, int es_referencia_2);//probar

/**
 * @brief: escribe el codigo nasm para realizar la division de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void dividir(FILE * fpasm, int es_referencia_1, int es_referencia_2);//probar

/**
 * @brief: escribe el codigo nasm para realizar la operacion or de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void o(FILE * fpasm, int es_referencia_1, int es_referencia_2);//probar

/**
 * @brief: escribe el codigo nasm para realizar la operacion and de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void y(FILE * fpasm, int es_referencia_1, int es_referencia_2);//probar

/**
 * @brief: escribe el codigo nasm para realizar la comparacion de igualdad de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void igual(FILE* fpasm, int es_referencia_1, int es_referencia_2, int cuantos_if);

/**
 * @brief: escribe el codigo nasm para realizar la comparacion de desigualdad de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void distinto(FILE* fpasm, int es_referencia_1, int es_referencia_2, int cuantos_if);

/**
 * @brief: escribe el codigo nasm para realizar la comparacion "mayor que" de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void mayor(FILE* fpasm, int es_referencia_1, int es_referencia_2, int cuantos_if);

/**
 * @brief: escribe el codigo nasm para realizar la comparacion "mayor o igual que" de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void mayor_igual(FILE* fpasm, int es_referencia_1, int es_referencia_2, int cuantos_if);

/**
 * @brief: escribe el codigo nasm para realizar la comparacion "menor que" de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void menor(FILE* fpasm, int es_referencia_1, int es_referencia_2, int cuantos_if);

/**
 * @brief: escribe el codigo nasm para realizar la comparacion "menor o igual que" de los dos operandos que se deben encontrar en la cima de la pila
 * @param: fpams: el archivo donde se va a escribir
 * @param: es_referencia_1: un flag que determina si el elemento que NO esta en la cima es una direccion (TRUE) o un valor (FALSE)
 * @param: es_referencia_2: un flag que determina si el elemento que SI esta en la cima es una direccion (TRUE) o un valor (FALSE)
 */
void menor_igual(FILE* fpasm, int es_referencia_1, int es_referencia_2, int cuantos_if);
#endif