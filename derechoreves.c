/* 
||||||DESCRIPCIÓN DEL PROGRAMA:|||||||
El programa recibe dos archivos de texto, uno con el tablero y otro con las palabras a buscar en el tablero. El programa busca las palabras en el tablero y escribe en un archivo de salida las coordenadas de la primera letra de cada palabra encontrada. El programa también escribe en el archivo de salida el número de palabras encontradas y el nombre de cada palabra.

===============
= BIBLIOTECAS =
=============== 
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> // Para medir el tiempo de ejecución

/*
========================
= Estructuras de datos =
========================
*/

// Tablero: contiene las dimensiones del tablero y las celdas
typedef struct {
    int filas;
    int columnas;
} Tablero;

#define MAX 50 // máximo número de tablero

// Direcciones posibles: Norte, Sur, Oeste, Este, Noroeste, Noreste, Suroeste, Sureste
Tablero direcciones[8] = {
    {-1, 0},   // Arriba
    {1, 0},    // Abajo
    {0, -1},   // Izquierda
    {0, 1},    // Derecha
    {-1, -1},  // Diagonal arriba izquierda
    {-1, 1},   // Diagonal arriba derecha
    {1, -1},   // Diagonal abajo izquierda
    {1, 1}     // Diagonal abajo derecha
};

/*
=========================
= ALGORITMO DE BÚSQUEDA =
=========================
*/

// Verifica si una posición (x,y) es válida en el tablero
// Entradas: Coordenadas x, y, dimensiones del tablero (filas y columnas)
// Salida: Valor booleano indicando si la posición es válida
bool esValido(int x, int y, int filas, int columnas) {
    return x >= 0 && x < filas && y >= 0 && y < columnas;
}

// Busca una palabra en el tablero desde una posición (x,y) en todas las direcciones
// Entradas: El tablero, posición inicial (x, y), palabra a buscar, dimensiones del tablero
// Salida: Valor booleano indicando si la palabra fue encontrada
bool buscarPalabra(char tablero[MAX][MAX], int x, int y, const char* palabra, int filas, int columnas) {
    int len = strlen(palabra);

    for (int dir = 0; dir < 8; dir++) {
        int k, fila_actual = x + direcciones[dir].filas, columna_actual = y + direcciones[dir].columnas;

        for (k = 1; k < len; k++) {
            if (!esValido(fila_actual, columna_actual, filas, columnas) || tablero[fila_actual][columna_actual] != palabra[k]) {
                break;
            }
            fila_actual += direcciones[dir].filas;
            columna_actual += direcciones[dir].columnas;
        }

        if (k == len) {
            return true;
        }
    }

    return false;
}

/*
======================
= MANEJO DE ARCHIVOS =
======================
*/

// LISTA.OUT

// Lee el tablero desde el archivo
// Entradas: Archivo desde donde se leerá, array para almacenar el tablero, punteros para dimensiones del tablero
// Salida: Ninguna (el tablero se almacena en el array proporcionado)
void leerTablero(FILE *archivo, char tablero[MAX][MAX], int *filas, int *columnas) {
    fscanf(archivo, "%d %d", filas, columnas);
    for (int i = 0; i < *filas; i++) {
        for (int j = 0; j < *columnas; j++) {
            fscanf(archivo, " %c", &tablero[i][j]);
        }
    }
}

// Lee las palabras desde el archivo
// Entradas: Archivo desde donde se leerán las palabras, array para almacenar las palabras
// Salida: Cantidad de palabras leídas
int leerPalabras(FILE *archivo, char palabras[MAX][MAX]) {
    int numPalabras;
    fscanf(archivo, "%d", &numPalabras);
    for (int i = 0; i < numPalabras; i++) {
        fscanf(archivo, "%s", palabras[i]);
    }
    return numPalabras;
}

// TABLERO.OUT

// Reemplaza la palabra en el tablero por asteriscos (*)
// Entradas: Tablero, posición inicial (x,y) y palabra a reemplazar
// Salida: Ninguna (el tablero se modifica internamente)
void reemplazarPalabra(char tablero[][MAX], int x, int y, char palabra[]) {
    int longitudPalabra = strlen(palabra);
    int direcciones[8][2] = {
        {-1, 0},   // Arriba
        {1, 0},    // Abajo
        {0, -1},   // Izquierda
        {0, 1},    // Derecha
        {-1, -1},  // Diagonal arriba izquierda
        {-1, 1},   // Diagonal arriba derecha
        {1, -1},   // Diagonal abajo izquierda
        {1, 1}     // Diagonal abajo derecha
    };

    // Verifica en todas las direcciones
    for (int d = 0; d < 8; d++) {
        int i = x;
        int j = y;
        int k = 0;
        bool coincide = true;

        // Verifica si la palabra coincide con la dirección actual
        while (k < longitudPalabra && coincide) {
            if (tablero[i][j] != palabra[k]) {
                coincide = false;
            } else {
                i += direcciones[d][0];
                j += direcciones[d][1];
                k++;
            }
        }

        // Si la palabra coincide, reemplaza las letras por asteriscos
        if (coincide) {
            i = x;
            j = y;
            for (k = 0; k < longitudPalabra; k++) {
                tablero[i][j] = '*';
                i += direcciones[d][0];
                j += direcciones[d][1];
            }
        }
    }
}

// Escribe el tablero modificado en el archivo
// Entradas: Archivo de salida, tablero, dimensiones del tablero, palabra a buscar
// Salida: Ninguna (el tablero modificado se escribe en el archivo)
void escribirTableroModificado(FILE *archivo, char tablero[][MAX], int filas, int columnas, char palabra[]) {
    char tableroTemporal[MAX][MAX];
    
    // Copia el tablero original en un tablero temporal
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tableroTemporal[i][j] = tablero[i][j];
        }
    }
    
    // Reemplaza la palabra encontrada por asteriscos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tablero[i][j] == palabra[0] && buscarPalabra(tablero, i, j, palabra, filas, columnas)) {
                reemplazarPalabra(tableroTemporal, i, j, palabra);
            }
        }
    }
    
    // Escribe el tablero modificado en el archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fprintf(archivo, "%c ", tableroTemporal[i][j]);
        }
        fprintf(archivo, "\n");
    }
    fprintf(archivo, "\n"); // Espacio adicional entre tableros
}

/*
========
= MAIN =
========
*/

int main(int argc, char *argv[]) {

    clock_t inicio = clock();
    // Verifica que se ingresen los archivos de entrada
    if (argc != 3) {
        printf("Uso: %s <archivo_tablero> <archivo_palabras>\n", argv[0]);
        return 1;
    }

    // Variables
    char tablero[MAX][MAX];
    int filas, columnas;
    int palabrasEncontradasX[MAX], palabrasEncontradasY[MAX];
    char palabras[MAX][MAX];
    int contadorPalabras = 0;

    // Aperura de archivos
    FILE *archivo_tablero = fopen(argv[1], "r");
    FILE *archivo_palabras = fopen(argv[2], "r");

    // Verifica que los archivos se hayan abierto correctamente
    if (!archivo_tablero || !archivo_palabras) {
        printf("Error al abrir los archivos de entrada.\n");
        return 1;
    }

    printf("Iniciando la lectura de archivos...\n");

    // Variables para el nombre de los archivos de salida
    int numero;
    char nombre_tableros_out[100];
    char nombre_lista_out[100];

    sscanf(argv[1], "tablero%d.ini", &numero); // Extrae el número del nombre del archivo tablero.
    sprintf(nombre_tableros_out, "tablero%d.out", numero); // Crea el nombre del archivo de salida de tableros.
    sprintf(nombre_lista_out, "lista%d.out", numero); // Crea el nombre del archivo de salida de la lista.

    // Apertura de archivos de salida
    FILE *archivo_tableros = fopen(nombre_tableros_out, "w");
    FILE *archivo_salida = fopen(nombre_lista_out, "w");

    // Verifica que los archivos de salida se hayan abierto correctamente
    if (!archivo_tableros || !archivo_salida) {
        printf("Error al crear los archivos de salida.\n");
        return 1;
    }

    // Lectura de tablero y palabras
    fscanf(archivo_tablero, "%d %d", &filas, &columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(archivo_tablero, " %c", &tablero[i][j]);
        }
    }

    // Busca las palabras en el tablero
    int numPalabras;
    fscanf(archivo_palabras, "%d", &numPalabras);

    printf("Lectura de archivos completada.\n");

    for (int w = 0; w < numPalabras; w++) { // Recorre todas las palabras
        char palabra[MAX];
        fscanf(archivo_palabras, "%s", palabra);
        bool encontrada = false;
        // Busca la palabra en el tablero
        for (int i = 0; i < filas && !encontrada; i++) {
            for (int j = 0; j < columnas && !encontrada; j++) {
                if (tablero[i][j] == palabra[0] && buscarPalabra(tablero, i, j, palabra, filas, columnas)) {
                    palabrasEncontradasX[contadorPalabras] = i + 1;
                    palabrasEncontradasY[contadorPalabras] = j + 1;
                    strcpy(palabras[contadorPalabras], palabra);
                    contadorPalabras++;
                    encontrada = true;
                    // Escribe el tablero modificado en el archivo de salida
                    escribirTableroModificado(archivo_tableros, tablero, filas, columnas, palabra);
                }
            }
        }
    }

    printf("Numero total de palabras buscadas: %d\n", numPalabras);
    printf("Numero total de palabras encontradas: %d\n", contadorPalabras);


    // Escribe la lista de palabras encontradas en el archivo de salida
    fprintf(archivo_salida, "%d\n", contadorPalabras);
    for (int i = 0; i < contadorPalabras; i++) {
        fprintf(archivo_salida, "%d %d (%s)\n", palabrasEncontradasX[i], palabrasEncontradasY[i], palabras[i]);
    }

    // Cierra los archivos
    fclose(archivo_tablero);
    fclose(archivo_palabras);
    fclose(archivo_salida);
    fclose(archivo_tableros);

    // Mide el tiempo de ejecución
    clock_t fin = clock();
    double tiempo_ejecucion = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f segundos\n", tiempo_ejecucion);

    // Fin del programa
    return 0;
}
