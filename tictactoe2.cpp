#include <iostream>
#include <vector>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para inicializar la semilla de rand()
#include <limits>  // Para el manejo de errores de std::cin

using namespace std;

// --- DECLARACIÓN DE FUNCIONES ---
void mostrarTablero(const vector<char>& espacios);
void turnoJugador(vector<char>& espacios, char jugador);
void turnoCPU(vector<char>& espacios, char computadora);
void turnoJugador2(vector<char>& espacios, char jugador); // Para el modo 1 vs 1
bool verificarGanador(const vector<char>& espacios, char jugador);
bool verificarEmpate(const vector<char>& espacios);
void jugar(int modoJuego);
void menuPrincipal();

// --- DEFINICIÓN DE FUNCIONES ---

/**
 * Muestra el tablero de Tic Tac Toe.
 * Se han añadido números de referencia para indicar al usuario las casillas (1-9).
 * El vector de 9 caracteres que representa el tablero.
 */
void mostrarTablero(const vector<char>& espacios) {
    // Muestra el tablero y los números de referencia de las casillas
    cout << "\n--- TABLERO ---\t--- REFERENCIA ---\n";
    for (int i = 0; i < 3; ++i) {
        // Línea superior divisora
        cout << "   |   |   \t   |   |   \n";
        // Contenido de la fila
        for (int j = 0; j < 3; ++j) {
            cout << " " << espacios[i * 3 + j] << " ";
            if (j < 2) cout << "|";
        }
        cout << "\t"; // Espacio entre tablero y referencia
        // Referencia de la casilla
        for (int j = 0; j < 3; ++j) {
            cout << " " << (i * 3 + j + 1) << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        // Línea inferior divisora
        if (i < 2) {
            cout << "___|___|___\t___|___|___\n";
        } else {
            cout << "   |   |   \t   |   |   \n";
        }
    }
    cout << "---------------\n";
}

/**
 * Procesa el turno de un jugador humano. Incluye la validación de entradas.
 * Espacios El vector del tablero.
 * El símbolo del jugador ('X' o 'O').
 */
void turnoJugador(vector<char>& espacios, char jugador) {
    int numero;
    bool entradaValida = false;

    do {
        cout << "Jugador " << jugador << ", ingresa la casilla (1-9): ";
        
        // 1. Validar que la entrada sea un número
        if (!(cin >> numero)) {
            cout << "¡Entrada inválida! Por favor, ingresa un número del 1 al 9.\n";
            // Limpia el estado de error de cin y descarta la entrada restante
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Vuelve a pedir la entrada
        }

        // 2. Validar rango (1-9) y disponibilidad
        if (numero >= 1 && numero <= 9) {
            int indice = numero - 1;
            if (espacios[indice] == ' ') {
                espacios[indice] = jugador;
                entradaValida = true;
            } else {
                cout << "¡Casilla ocupada! Elige otra.\n";
            }
        } else {
            cout << "¡Rango inválido! Ingresa un número del 1 al 9.\n";
        }

    } while (!entradaValida);
}

/**
 * @brief Lógica para la jugada de la CPU.
 * @param espacios El vector del tablero.
 * @param computadora El símbolo de la computadora ('O').
 */
void turnoCPU(vector<char>& espacios, char computadora) {
    int numero;
    
    // Inicialización del generador de números aleatorios (solo una vez por juego)
    // Se recomienda poner srand(time(0)) en main o una función de inicialización,
    // pero por simplicidad se mantiene aquí (aunque se ejecuta en cada turno).
    srand(time(0)); 

    while (true) {
        numero = rand() % 9; // Genera un índice aleatorio de 0 a 8
        
        // CORRECCIÓN: Usar == para comparación, no = (asignación)
        if (espacios[numero] == ' ') { 
            espacios[numero] = computadora;
            cout << "La CPU (" << computadora << ") juega en la casilla " << numero + 1 << ".\n";
            break; // Sale del bucle una vez que hace la jugada
        }
    }
}

/**
 * @brief Función auxiliar para el turno del Jugador 2 en modo Humano vs Humano.
 * @param espacios El vector del tablero.
 * @param jugador El símbolo del Jugador 2 ('O').
 */
void turnoJugador2(vector<char>& espacios, char jugador) {
    turnoJugador(espacios, jugador);
}

/**
 * @brief Verifica todas las combinaciones ganadoras.
 * @param espacios El vector del tablero.
 * @param jugador El símbolo del jugador actual.
 * @return true si el jugador actual ha ganado, false en caso contrario.
 */
bool verificarGanador(const vector<char>& espacios, char jugador) {
    // Definición de todas las combinaciones ganadoras (índices)
    const int combinaciones[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Filas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columnas
        {0, 4, 8}, {2, 4, 6}             // Diagonales
    };

    for (int i = 0; i < 8; ++i) {
        if (espacios[combinaciones[i][0]] != ' ' &&
            espacios[combinaciones[i][0]] == espacios[combinaciones[i][1]] &&
            espacios[combinaciones[i][1]] == espacios[combinaciones[i][2]]) {
            
            // Imprime el mensaje de ganador
            if (espacios[combinaciones[i][0]] == jugador) {
                 cout << "¡FELICIDADES! ¡El Jugador " << jugador << " ha GANADO!\n";
            } else {
                 cout << "¡El Jugador " << (jugador == 'X' ? 'O' : 'X') << " ha GANADO!\n";
            }
            return true;
        }
    }
    return false;
}

/**
 *  Verifica si hay un empate (tablero lleno sin ganador).
 *  espacios El vector del tablero.
 *  true si es empate, false en caso contrario.
 */
bool verificarEmpate(const vector<char>& espacios) {
    for (char espacio : espacios) {
        if (espacio == ' ') {
            return false; // Todavía hay casillas vacías
        }
    }
    cout << "¡Empate! El tablero está lleno.\n";
    return true; // Tablero lleno
}

/**
 * lógica principal del ciclo de juego.
 * modoJuego 1 para Humano vs Humano, 2 para Humano vs CPU.
 */
void jugar(int modoJuego) {
    // Uso de std::vector en lugar de C-style array
    vector<char> espacios(9, ' '); 
    char jugadorX = 'X';
    char jugadorO = 'O'; // Puede ser CPU u otro jugador humano
    char jugadorActual = jugadorX;
    bool run = true;

    cout << "\n¡Comienza el juego de Gato! El Jugador 'X' inicia.\n";
    if (modoJuego == 1) {
        cout << "Modo: Jugador vs Jugador.\n";
    } else {
        cout << "Modo: Jugador vs CPU.\n";
    }

    while (run) {
        mostrarTablero(espacios);
        
        // Determinar qué función de turno usar
        if (jugadorActual == jugadorX) {
            turnoJugador(espacios, jugadorX);
        } else {
            if (modoJuego == 2) {
                turnoCPU(espacios, jugadorO);
            } else {
                turnoJugador2(espacios, jugadorO);
            }
        }

        // Revisar estado después de la jugada
        if (verificarGanador(espacios, jugadorActual)) {
            mostrarTablero(espacios);
            run = false;
        } else if (verificarEmpate(espacios)) {
            mostrarTablero(espacios);
            run = false;
        } else {
            // Cambiar de turno
            jugadorActual = (jugadorActual == jugadorX ? jugadorO : jugadorX);
        }
    }
}

/**
 * Muestra el menú principal y maneja la selección del usuario (Mejora Opcional).
 */
void menuPrincipal() {
    int opcion;
    do {
        cout << "\n==============================\n";
        cout << "     JUEGO TIC TAC TOE     \n";
        cout << "==============================\n";
        cout << "1. Jugar vs Humano (X vs O)\n";
        cout << "2. Jugar vs CPU (X vs O)\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opción: ";

        // Validar entrada del menú
        if (!(cin >> opcion)) {
            cout << "¡Opción inválida! Por favor, ingresa un número.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0; // Para que el bucle continúe
            continue;
        }

        switch (opcion) {
            case 1:
            case 2:
                // La función jugar() maneja el juego
                jugar(opcion); 
                break;
            case 3:
                cout << "\nGracias por participar. ¡Adiós!\n";
                break;
            default:
                cout << "Opción no reconocida. Intenta de nuevo.\n";
                break;
        }
    } while (opcion != 3);
}

// --- FUNCIÓN PRINCIPAL MAIN ---
int main() {
    // srand(time(0)); // Mejor inicializar la semilla aquí si se usa std::rand
    menuPrincipal();
    return 0;
}