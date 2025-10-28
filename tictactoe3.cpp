#include <iostream>
#include <vector>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

using namespace std;

// Función para mostrar el tablero
void mostrarTablero(const vector<vector<char>>& tablero) {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << tablero[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---------\n";
    }
    cout << "\n";
}

// Función para verificar si hay un ganador
char verificarGanador(const vector<vector<char>>& tablero) {
    // Verificar filas
    for (int i = 0; i < 3; ++i) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ') {
            return tablero[i][0];
        }
    }
    // Verificar columnas
    for (int j = 0; j < 3; ++j) {
        if (tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j] && tablero[0][j] != ' ') {
            return tablero[0][j];
        }
    }
    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ') {
        return tablero[0][0];
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ') {
        return tablero[0][2];
    }
    return ' '; // No hay ganador
}

// Función para verificar si hay empate
bool verificarEmpate(const vector<vector<char>>& tablero) {
    for (const auto& fila : tablero) {
        for (char celda : fila) {
            if (celda == ' ') return false;
        }
    }
    return true;
}

// Función para el turno del jugador humano
void turnoJugador(vector<vector<char>>& tablero, char simbolo) {
    int fila, columna;
    while (true) {
        cout << "Jugador " << simbolo << ", ingresa fila y columna (ejemplo: 1 3): ";
        cin >> fila >> columna;
        fila--; columna--; // Ajustar a índices
        if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ') {
            tablero[fila][columna] = simbolo;
            break;
        } else {
            cout << "Movimiento inválido. Intenta de nuevo.\n";
        }
    }
}

// Función para el turno de la CPU (elige una celda vacía aleatoria)
void turnoCPU(vector<vector<char>>& tablero, char simbolo) {
    vector<pair<int, int>> celdasVacias;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tablero[i][j] == ' ') {
                celdasVacias.push_back({i, j});
            }
        }
    }
    if (!celdasVacias.empty()) {
        int indice = rand() % celdasVacias.size();
        tablero[celdasVacias[indice].first][celdasVacias[indice].second] = simbolo;
        cout << "CPU juega en fila " << (celdasVacias[indice].first + 1) << ", columna " << (celdasVacias[indice].second + 1) << "\n";
    }
}

// Función principal del juego
void jugar(bool vsCPU) {
    vector<vector<char>> tablero(3, vector<char>(3, ' '));
    char jugadorActual = 'X';
    bool turnoCPUActivo = (vsCPU && rand() % 2 == 0); // CPU puede empezar aleatoriamente si es vs CPU

    while (true) {
        mostrarTablero(tablero);
        
        if (vsCPU && turnoCPUActivo) {
            turnoCPU(tablero, 'O');
            turnoCPUActivo = false;
        } else {
            turnoJugador(tablero, jugadorActual);
            if (vsCPU) turnoCPUActivo = true;
        }

        char ganador = verificarGanador(tablero);
        if (ganador != ' ') {
            mostrarTablero(tablero);
            cout << "¡Jugador " << ganador << " gana!\n";
            break;
        }
        if (verificarEmpate(tablero)) {
            mostrarTablero(tablero);
            cout << "¡Es un empate!\n";
            break;
        }

        // Cambiar turno
        if (!vsCPU) {
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
        }
    }
}

// Función para mostrar el menú
int mostrarMenu() {
    int opcion;
    cout << "\n=== Tic Tac Toe ===\n";
    cout << "1. Jugar contra otro jugador\n";
    cout << "2. Jugar contra la CPU\n";
    cout << "3. Salir\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cout << "\n";
    return opcion;
}

int main() {
    srand(time(0)); // Semilla para números aleatorios
    while (true) {
        int opcion = mostrarMenu();
        if (opcion == 1) {
            jugar(false); // Juego vs humano
        } else if (opcion == 2) {
            jugar(true); // Juego vs CPU
        } else if (opcion == 3) {
            cout << "¡Hasta luego!\n";
            break;
        } else {
            cout << "Opción inválida. Intenta de nuevo.\n";
        }
        
        // Opción de reiniciar después de cada juego
        char reiniciar;
        cout << "¿Quieres jugar de nuevo? (s/n): ";
        cin >> reiniciar;
        if (reiniciar != 's' && reiniciar != 'S') {
            cout << "¡Hasta luego!\n";
            break;
        }
    }
    return 0;
}
