#include "../includes/tablaSimbolos.h"
#define TABLESIZE 256

TABLA_HASH * tablaSimbolosGlobal = NULL;
TABLA_HASH * tablaSimbolosLocal = NULL;

STATUS declararGlobal(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
	if (tablaSimbolosGlobal == NULL)
		tablaSimbolosGlobal = crear_tabla(TABLESIZE);
	if (tablaSimbolosGlobal)
		return insertar_simbolo(tablaSimbolosGlobal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	else
		return ERR;
}


STATUS declararLocal(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
	if (tablaSimbolosLocal)
		return insertar_simbolo(tablaSimbolosLocal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	else
		return ERR;
}// 4, 5, 6, 7, 8


INFO_SIMBOLO *usoGlobal(const char* lexema) {
	if (tablaSimbolosGlobal)
		return buscar_simbolo(tablaSimbolosGlobal, lexema);
	else
		return NULL;
}


INFO_SIMBOLO *usoLocal(const char* lexema) {
	if (tablaSimbolosLocal && tablaSimbolosGlobal) {
		INFO_SIMBOLO * aux = buscar_simbolo(tablaSimbolosLocal, lexema);
		if (aux)
			return aux;
		else
			return buscar_simbolo(tablaSimbolosGlobal, lexema);
	}
	else
		return NULL;
}


STATUS declararFuncion(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
	if (tablaSimbolosGlobal == NULL) {
		tablaSimbolosGlobal = crear_tabla(TABLESIZE);
		if (tablaSimbolosGlobal == NULL)
			return ERR;
	}

	liberar_tabla(tablaSimbolosLocal);
	tablaSimbolosLocal = crear_tabla(TABLESIZE);

	if (tablaSimbolosLocal) {
		if (insertar_simbolo(tablaSimbolosGlobal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param) == ERR) {
			liberar_tabla(tablaSimbolosLocal);
			tablaSimbolosLocal = NULL;
			return ERR;
		}
		return insertar_simbolo(tablaSimbolosLocal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	} else {
		return ERR;
	}
}

void cerrarFuncion() {
	liberar_tabla(tablaSimbolosLocal);
	tablaSimbolosLocal = NULL;
}

void limpiarTablas() {
	cerrarFuncion();
	liberar_tabla(tablaSimbolosGlobal);
	tablaSimbolosGlobal = NULL;
}