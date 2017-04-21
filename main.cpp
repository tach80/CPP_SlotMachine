/* 
 * Archivo:   main.cpp
 * Autor: administrador
 *
 * Creado el 20 de febrero de 2017, a las 14:16
 */

// Librerías y cabeceras
#include <iostream> // Librería básica de consola.
#include <cstdlib> // Para rand.
#include <ctime> // Para tener fecha (como semilla inicial para rand).

// Variables globales (mala idea)
const int g_SLOTS=3; // Casillas para cada tirada.
const int g_SYMBOLS=5; // Valores posibles que pueden salir.
const int g_COST=1; // "Precio" por partida

//Funciones

// Comprobador de premio en filas
int f_filas (int array[][g_SLOTS]) {
    int l_premio = 0; // Para devolver un valor al main.
    for (int a = 0; a < g_SLOTS; a++) {
        int prize_checker = 0; // Registro de igualdades entre símbolos.
        for (int b = 0; b < g_SLOTS - 1; b++) {
            if (array[a][b] == array[a][b+1]) {
                prize_checker = prize_checker + 1;
            }
        }
        if (prize_checker == g_SLOTS - 1) {
            l_premio = l_premio + array[a][0];
        }
    }
    return l_premio;
}

// Comprobador de premio en columnas.
int f_columnas (int array[][g_SLOTS]) {
    int l_premio = 0; // Para devolver un valor al main.
    for (int a = 0; a < g_SLOTS; a++) {
        int prize_checker = 0; // Registro de igualdades entre símbolos.
        for (int b = 0; b < g_SLOTS - 1; b++) {
            if (array[b][a] == array[b+1][a]) {
                prize_checker = prize_checker + 1;
            }
        }
        if (prize_checker == g_SLOTS - 1) {
            l_premio = l_premio + array[0][a];
        }
    }
    return l_premio;
}

// Comprobador de premio en la diagona principal.
int f_diagonal (int array[][g_SLOTS]) {
    int l_premio = 0; // Para devolver valor al main.
    int prize_checker = 0; // Registro de igualdades entre símbolos.
    for (int a = 0; a < g_SLOTS - 1; a++) {
        if (array[a][a] == array[a+1][a+1]) {
            prize_checker = prize_checker + 1;
        }
        if (prize_checker == g_SLOTS - 1) {
            l_premio = l_premio + array[0][0];
        }
    }
    return l_premio;
}

// Comprobador de premio en la diagona secundaria.
int f_secundaria (int array[][g_SLOTS]){
    int l_premio = 0; // Para devolverle valor al main.
    int prize_checker = 0; // Registro de igualdades entre símbolos.
    for (int a = g_SLOTS-1; 0 < a; a--) {
        // La suma es a + b = g_SLOTS - 1 
        if (array[a][g_SLOTS-1-a] == array[a-1][g_SLOTS-a]) {
            prize_checker = prize_checker + 1;
        }
        if (prize_checker == g_SLOTS - 1) {
            l_premio = l_premio + array[g_SLOTS-1][0];
        }
    }
    return l_premio;
}

/*
 * Hagamos esto un poco más complicado: las tiradas se almacenan como matrices
 * 3x3, y son 9 elementos ordenados. Ahora, las comprobaciones para premio se
 * hacen por filas, columnas y diagonales (principal y secundaria).
 */

int main(int argc, char** argv) {
    // Recuperemos el array multidimensional.
    int resultados[g_SLOTS][g_SLOTS];
    // Expliquemos algunas variables un poco más.
    int dinero = 0; // Dinero que introduce el jugador.
    int premio = 0; // Tokens ganados en las partidas.
    int bote = 0; // Tokens acumulados a lo largo de las partidas.
    int total = 0; // Partidas totales jugadas.
    // Variables de texto para control de entrada de usuario.
    char answer[2] = "y"; // Para seguir jugando (o no).
    char addprize[2] = "y"; // Para añadir el premio a las tiradas (o no).
    
    // Un poco de texto por pantalla, para pedir instrucciones.
    std::cout << "Bienvenido a esta máquina de azar.\n";
    std::cout << "¿Cuánto dinero quieres introducir?: ";
    std::cin >> dinero;
    std::cout << "Vamos a hacer " << dinero/g_COST << " tiradas.\n\n";

    
    // Iniciamos el generador aleatorio.
    srand(time(NULL));
    // Este while es para controlar si el jugador quiere continuar o no.
    while ((answer[0] == 'y')||(answer[0] == 'Y')) {
        if (dinero >= 1) {
            dinero = dinero - g_COST; // Descontamos una tirada.
            total = total + 1;
            premio = 0; // Reiniciamos el premio.
    
            // Rellenemos y mostremos la matriz (evitamos un bucle).
            for (int a = 0; a < g_SLOTS; a++) {// Esto marca las filas.
                for (int b = 0; b < g_SLOTS; b++) {// Y esto las columnas.
                    resultados[a][b] = std::rand() % g_SYMBOLS + 1;
                    std::cout << resultados[a][b] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
    
            // Creo que puedo hacer esto con funciones y punteros.
            // Comprobación de las filas.
            premio = premio + f_filas(resultados);
    
            // Comprobación de las columnas.
            premio = premio + f_columnas(resultados);
            
            // Vamos con la diagonal principal.
            premio = premio + f_diagonal(resultados);
            
            // La diagonal secundaria puede ser un poco más complicada...
            premio = premio + f_secundaria(resultados);

            
            // Sumamos los premios y los mostramos juntos al final.
            if (premio != 0) {
                std::cout << "¡Has ganado! Tu premio es de " << premio << "€.\n\n";
                std::cout << "¿Quieres añadir el premio para tener más tiradas?: ";
                std::cin >> addprize;
                if ((addprize[0] == 'y')||(addprize[0] == 'Y')) {
                    dinero = dinero + premio;
                } else {
                    bote = bote + premio; // Si no, el premio va al bote.
                }
            } else {
                std::cout << "Vuelve a intentarlo.\n\n";
            }
            // Ahora, para saber si queremos seguir tirando o no...
            std::cout << "Te quedan " << dinero/g_COST << " tiradas.\n";
            std::cout << "Tu premio acumulado es " << bote << "€.\n";
            std::cout << "¿Quieres seguir jugando? (y/n): ";
            std::cin >> answer;
            std::cout << std::endl;
        } else {
            std::cout << "Lo siento, no te quedan tiradas.\n\n";
            answer[0]='n';
            // ¿Y si queremos añadir el bote para seguir jugando?
            // ¿O si queremos liquidar el dinero metido?
        }
    }
    
    // Final del programa, resumen de los datos.
    std::cout << "Al final de la partida,\nhas jugado " << total << " rondas\n";
    std::cout << "y tu premio acumulado es de " << bote << "€.\n";
        
    return 0;
}