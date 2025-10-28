#include <iostream>
#include <ctime>
#include <cstdlib>


void tablero(char *espacios);
void t_jug(char *espacios, char jugador);
void t_pc(char *espacios, char computadora);
bool ganador(char *espacios, char jugador,char computadora);
bool empate(char *espacios);

int main() {

    char espacios[9]={' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char jugador = 'X';
    char computadora = 'O';
    bool run = true;

    tablero(espacios);
  
    while (run){

        t_jug(espacios, jugador);
        tablero(espacios);
        if(ganador(espacios, jugador, computadora)){
            run = false;
            break;
        }
        if(empate(espacios)){
            run = false;
            break;
        }
        t_pc(espacios, computadora);
        tablero(espacios);
        if(ganador(espacios, jugador, computadora)){
            run = false;
            break;
        }
        if(empate(espacios)){
            run = false;
            break;
        }
    }


    std::cout << "Gracias por participar";
    return 0;

}
void tablero(char *espacios) {

    std::cout <<'\n';
    std::cout << "     |     |     "<< '\n';
    std::cout << "  " << espacios[0] << "  |  " << espacios[1] << "  |   " << espacios[2] << "  "<< '\n';
    std::cout << "_____|_____|_____" << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "   " << espacios[3] << " |  " << espacios[4] << "  |   " << espacios[5] << "  "<< '\n';
    std::cout << "_____|_____|_____" << '\n';
    std::cout << "     |     |     "<< '\n';
    std::cout << "  " << espacios[6] << "  |  " << espacios[7] << "  |   " << espacios[8] << "  "<< '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << '\n';
}
void t_jug(char *espacios, char jugador){

    int numero;
    do
    {
        std::cout << "Ingresa una casilla del 1-9: ";
        std::cin >> numero;
        numero--;

        if (espacios[numero] == ' '){
            espacios[numero] = jugador;
            break;
        }
        

    } 
    
    while ((!numero > 8 || !numero < 8));
    
}
void t_pc(char *espacios, char computadora){

    int numero;
    srand(time(0)); //para escoger un numero al azar

    while (true){
        numero = rand() % 9;
        if (espacios[numero] = ' '){
            espacios[numero] = computadora;
        }
        
    }
    
}
bool ganador(char *espacios, char jugador,char computadora){
    
    if ((espacios[0] != ' ') && (espacios[0] == espacios[1]) && (espacios[1] == espacios[2])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else if ((espacios[3] != ' ') && (espacios[3] == espacios[4]) && (espacios[4] == espacios[5])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else if ((espacios[6] != ' ') && (espacios[6] == espacios[7]) && (espacios[7] == espacios[8])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else if ((espacios[0] != ' ') && (espacios[0] == espacios[3]) && (espacios[3] == espacios[6])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else if ((espacios[1] != ' ') && (espacios[1] == espacios[4]) && (espacios[4] == espacios[7])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else if ((espacios[2] != ' ') && (espacios[2] == espacios[5]) && (espacios[5] == espacios[8])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else if ((espacios[0] != ' ') && (espacios[0] == espacios[4]) && (espacios[4] == espacios[8])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else if ((espacios[2] != ' ') && (espacios[2] == espacios[4]) && (espacios[4] == espacios[6])){
        espacios[0] == jugador ? std::cout << "¡ERES EL GANADOR!\n" : std::cout << "¡PERDISTE :(!\n" ;
    }
    else {
        return false;
    }

    return true;
}
bool empate(char *espacios){

    for (int  i = 0; i < 9; i++){
        
        if(espacios[i] == ' '){
            return false;
        }
    }
   
    return true;
}
