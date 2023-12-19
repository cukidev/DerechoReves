# DerechoReves

Derecho revés es una implementación en C que se basa en el juego "Sopa de Letras" funciona en base a tableros de n tamano, y este es capaz de encontrar palabras dadas en una lista dentro de ese tablero, considerando tanto que esten de forma vertical y horizontal.

Por lo cual, dado una lista en "lista-n-.lst" y un tablero de nombre "tablero-n-.ini", el programa será capaz de leer los elementos de la lista, buscarlos y posteriormente entregar dos archivos de salida con sus resultados.

# ¿Cómo usar? 

Para poder ejecutar de manera correcta la implementacion, es necesario tener instalado MinGW, para la ejecucion en la consola de comandos. 

Para acceder, se debe buscar la ruta de la carpeta contenedora del ejecutable y de los dos archivos de entrada.

Para los archivos de entrada, este se debe llamar tablero ”n” junto con la extension .in, y otro que contenga la lista, ”lista n”, con extension.lst

Para llevar a cabo la correcta ejecucion basta solo con llamar al nombre del ejecutable junto con las dos entradas, por ejemplo:

* Primero se compila el programa: gcc -o main derechoreves.c

* Luego se ejecuta:
./main tablero1.ini lista1.lst

Finalmente, se crearán dos archivos de salida: ”tablero.out”, el cual contendra la cantidad de tableros equivalente a la cantidad de palabras encontradas, y otroarchivo, llamado ”lista.out”, el cual contendra una lista con las palabras contenidas y sus respectivas coordenadas.

* Se adjuntan dos archivos de prueba, tanto lista1, lista2 como tablero1 y tablero2 para poder usar la aplicación, no obstante, debería ser capaz de leer cualquier archivo mientras siga el formato establecido anteriormente.

# Evitemos errores.

Unos posibles errores pueden darse a que los archivos de entrada no esten ubicados en la misma ruta de ejecución, por lo que hay que tener cuidado con eso.

Si no hacemos correcto uso de esto, nos aparecera un mensaje de error diciendo que no se pudo crear el archivo de salida. Para evitarlo solo basta seguir con los pasos indicados anteriormente.
