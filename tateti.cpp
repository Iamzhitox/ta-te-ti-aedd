#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <windows.h>
using namespace std;

struct player {
    string name;
    char ficha;
};

void menuPlayers( char c[][4] );
void singlePlayer( char c[][4] );
void multiPlayer( char c[][4] );
void personTurn( char c[][4], int & turn, player p, bool & win );
void botTurn( char c[][4], int & turn, player b, bool & win, player p );
void print( char c[][4] );
void evaluar( char c[][4], player p, bool & win );
void vaciar( char c[][4] );
void ia( char c[][4], player b, player p );
void ubicar( char c[][4], player b, player p, int caso );

bool diagonalPrincipal (char c[][4], char ficha, int &ubicacion);
bool diagonalSecundaria (char c[][4], char ficha, int &ubicacion);
bool filas (char c[][4], char ficha, int &ubicacion);
bool columnas (char c[][4], char ficha, int &ubicacion);

int main() {
    system("cls");
    
    char cuadro[4][4];
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            cuadro[i][j] = ' ';
        }
    }
    
    menuPlayers(cuadro);
    
    return 0;
}

void menuPlayers ( char c[][4] ) {
    int option;
    cout << "============================" << endl;
    cout << "|    Modalidad de juego    |" << endl;
    cout << "============================" << endl << endl;
    cout << "1: 1 jugador vs. computadora" << endl;
    cout << "2: 1 vs. 1" << endl << endl;
    cout << "3: Salir" << endl << endl << "\t\t";
    do {
        cin >> option;
    } while ( option < 0 || option > 3 );

    switch (option) {
        case 1:
            singlePlayer(c);
            break;
        case 2:
            multiPlayer(c);
        default:
            break;
        }    
}

void singlePlayer( char c[][4] ) {
    system("cls");
    player person, bot; int ficha;
    bot.name  = "La Maquina";

    cout << "============================" << endl;
    cout << "| Hola, como te llamas? :D |" << endl;
    cout << "============================" << endl;
    cout << "\t"; cin >> person.name;

    system("cls");
    cout << "============================" << endl;
    cout << "|   Que fichas preferis?   |" << endl;
    cout << "============================" << endl << endl;
    cout << "\t  1: O" << endl << "\t  2: X" << endl << endl;
    cout << "\t\t"; cin >> ficha;
    switch (ficha) {
        case 1:
            person.ficha = 'O';
            bot.ficha = 'X';
            break;
        case 2:
            person.ficha = 'X';
            bot.ficha = 'O';
            break;
        default:
            break;
    }
    int turno = 1;
    bool win = false;
    string ganador;

    do {
        system("cls");
        if ( turno != 1 ) {
            cout << endl << endl;
        }
        personTurn(c, turno, person, win);
        if (!win && turno < 10) {
            system("cls");
            cout << endl << endl;
            botTurn(c, turno, bot, win, person);
        }

    } while ( turno < 10 && !win );

    if (!win) {
        cout << endl << endl;
        print(c);
        cout << "====================" << endl;
        cout << "  HAN EMPATADO!!!  " << endl;
        cout << "====================" << endl << endl;
    }
    system("pause");

}
void multiPlayer( char c[][4] ) {
    system("cls");
    player player1, player2; int ficha;

    cout << "=================================" << endl;
    cout << "|  Nombre del jugador Numero 1  |" << endl;
    cout << "=================================" << endl;
    cout << "\t"; cin >> player1.name;

    system("cls");
    cout << "=================================" << endl;
    cout << "|  Nombre del jugador Numero 2  |" << endl;
    cout << "=================================" << endl;
    cout << "\t"; cin >> player2.name;

    ficha = rand() % 2;
    if (ficha == 0) {
        player1.ficha = 'O';
    } else {
        player1.ficha = 'X';
    }

    switch (ficha) {
        case 0:
            player2.ficha = 'X';
            break;
        default:
            player2.ficha = 'O';
            break;
    }

    system("cls");
    cout << "===============================" << endl;
    cout << player1.name << " juega con las fichas: " << player1.ficha << endl;
    cout << "===============================" << endl;

    cout << "===============================" << endl;
    cout << player2.name << " juega con las fichas: " << player2.ficha << endl;
    cout << "===============================" << endl;

    Sleep(3500);

    int turno = 1;
    bool win = false;
    string ganador;

    do {
        system("cls");
        if ( turno != 1 ) {
            cout << "Tu turno " << player1.name << "!" << endl << endl;
        }
        personTurn(c, turno, player1, win);
        if (!win && turno < 10) {
            system("cls");
            cout << "Tu turno " << player2.name << "!" << endl << endl;
            personTurn(c, turno, player2, win);
        }

    } while ( turno < 10 && !win );

    if (!win) {
        cout << endl << endl;
        print(c);
        cout << "====================" << endl;
        cout << "  HAN EMPATADO!!!  " << endl;
        cout << "====================" << endl << endl;
    }
    system("pause");

}


void personTurn( char c[][4], int & turn, player  p, bool & win ) {
    char cX; int x, y;
    if (turn == 1) {
        cout << "Tu turno, " << p.name << "!" << endl;
        cout << "============================" << endl;
        cout << "|  Elige las coordenadas.  |" << endl;
        cout << "============================" << endl << endl;
        cout << "Formato de coordenadas: LETRA, NUMERO" << endl;
        cout << "Ejemplo de insercion: a [espacio] 2" << endl;
    }
    print(c);
    cout << endl << "Coordenadas: "; 
    
    do {
        cin >> cX >> y;
        switch (cX) {
            case 'a':
                x = 1;
                break;
            case 'b':
                x = 2;
                break;
            case 'c':
                x = 3;
                break;
            default:
                break;
        }
        y--;
		x--;
    } while ( !isspace(c[x][y]) );
    
    c[x][y] = p.ficha;

    system("cls");
    cout << endl << endl;
    print(c);
    Sleep(2000);
    if ( turn > 4 ) {
        evaluar(c,p,win);
    }
    turn++;

}
void botTurn( char c[][4], int & turn, player b, bool & win, player p ) {
    int x, y;
    srand(time(NULL));
    system("cls");
    cout << endl << endl;
    print(c);
    cout << endl << "Turno de la maquina..." << endl;
    Sleep(500);

    if ( turn > 3 ) {
        cout << "Entrando a la IA" << endl;
        ia( c, b, p );
    } else {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while ( !isspace(c[x][y]) );
        c[x][y] = b.ficha;
    }


    system("cls");
    cout << endl << endl;
    print(c);
    cout << endl << "Turno de la maquina..." << endl;
    Sleep(2500);
    if ( turn > 4 ) {
        // cout << "Esta evaluando, che..." << endl;
        evaluar(c,b,win);
    }
    turn++;

}

void ia( char c[][4], player b, player p ) {
    int caso = 0;

    if (diagonalPrincipal(c,b.ficha,caso)) {
        cout << "Entrando al caso 1..." << endl;
        ubicar(c,b,p,caso);
    } else if (diagonalSecundaria(c,p.ficha,caso)) {
        cout << "Entrando al caso 2..." << endl;
        ubicar(c,b,p,caso);        
    } else if (filas(c,b.ficha,caso)) {
        cout << "Entrando al caso " << caso << "..." << endl;
        ubicar(c,b,p,caso);                
    } else if (columnas(c,b.ficha,caso)) {
        cout << "Entrando al caso " << caso << "..." << endl;
        ubicar(c,b,p,caso);          
    } else if (diagonalPrincipal(c,p.ficha,caso)) {
        cout << "Entrando al caso 1..." << endl;
        ubicar(c,b,p,caso);
    } else if (diagonalSecundaria(c,p.ficha,caso)) {
        cout << "Entrando al caso 2..." << endl;
        ubicar(c,b,p,caso);        
    } else if (filas(c,p.ficha,caso)) {
        cout << "Entrando al caso " << caso << "..." << endl;
        ubicar(c,b,p,caso);                
    } else if (columnas(c,p.ficha,caso)) {
        cout << "Entrando al caso " << caso << "..." << endl;
        ubicar(c,b,p,caso);                
    } else {
        cout << "Entrando al caso 0..." << endl;
        ubicar(c,b,p,caso);
    }
}

void evaluar( char c[][4], player p, bool & win ) {
    //
    // cout << "Evaluando ..." << endl;
    // Sleep(200);
    system("cls");

    char d[4][4];
    vaciar(d);    //

    int i = 0, j = 0; 
    bool find = true;

    while ( find && i <= 2 ) {
        if ( c[i][i] != p.ficha ) {
            find = false;
            
        } else {
            //
            d[i][i] = (char)254;
            
            //
        }
        i++;
    }

    //
    // cout << "Testeo caso #1" << endl << endl;
    // print(d);
    // Sleep(200);
    // system("cls");
    // vaciar(d);    
    //
    win = find ? true : false;

    if (!win) {
        find = true; i = 0, j = 2;
        while ( find && i <= 2 && j >= 0 ) {
            if ( c[i][j] != p.ficha ) {
                find = false;
                
            } else {
                //
                d[i][j] = (char)254;
                
                //
            }
            i++;
            j--;
        }

        //
        // cout << "Testeo caso #2" << endl << endl;
        // print(d);
        // Sleep(200);
        // system("cls");
        // vaciar(d);
        //

        win = find ? true : false;

        if (!win) {
            find = false; i = 0, j = 0;
            while ( i <= 2 && !find ) {
                j = 0, find = true;
                while ( find && j <= 2 ) {
                    if ( c[i][j] != p.ficha ) {
                        find = false;
                        
                    }  else {
                        //
                        d[i][j] = (char)254;
                        
                        //
                    }
                    j++;
                }

                // //
                // cout << "Testeo caso #3 - " << i+1 << endl << endl;
                // print(d);
                // Sleep(200);
                // system("cls");
                // vaciar(d);
                // //
                i++;
            }

            win = find ? true : false;

            if (!win) {
                find = false; i = 0;
                int j;
                while ( i <= 2 && !find ) {
                    j = 0, find = true;
                    while ( find && j <= 2 ) {
                        if ( c[j][i] != p.ficha ) {
                            find = false;
                            
                        } else {
                            //
                            d[j][i] = (char)254;
                            
                            //
                        }
                        j++;
                    }

                    // //
                    // cout << "Testeo caso #4 - " << i+1 << endl << endl;
                    // print(d);
                    // Sleep(200);
                    // system("cls");
                    // vaciar(d);
                    // //
                    i++;
                }

                win = find ? true : false;
            }
        } 
    }

    char name[p.name.length()];
    name[p.name.length()] = '\0';
    for ( int i = 0; i < p.name.length(); i++ ) {
        name[i] = p.name[i];
        name[i] = toupper(name[i]);
    }

    if (win == true) {
        cout << endl << endl;
        print(c);
        cout << "============================" << endl;
        cout << "  HA GANADO " << name << "!!!" << endl;
        cout << "============================" << endl << endl;
    }

}
void ubicar( char c[][4], player b, player p, int caso ) {
    // cout << "Ubicando..." << endl;
    // Sleep(1500);

    int j,i; bool find;
    switch (caso) {
        case 1:
            i = 0; find = false;
            while ( i <= 2 && !find ) {
                if (isspace(c[i][i])) {
                    c[i][i] = b.ficha;
                    find = true;
                } else {
                    i++;
                }
            }
            break;
        case 2:
            j = 0, i = 2; find = false;
            while (!find && i >= 0) {
                if (isspace(c[i][j])) {
                    c[i][j] = b.ficha;
                    find = true;
                } else {
                    i--;
                    j++;
                }
            }
            break;
        case 3: case 4: case 5:
            j = 0;
            if (caso==3) {i=0;} else if (caso==4) {i=1;} else if (caso==5) {i=2;} 
            while ( j <= 2 && !find ) {
                if (c[i][j] != p.ficha) {
                    c[i][j] = b.ficha;
                    find = true;
                } else {
                    j++;
                }
            }
            break;    
        case 6: case 7: case 8:
            j = 0;
            if (caso==6) {i=0;} else if (caso==7) {i=1;} else if (caso==8) {i=2;} 
            while ( j <= 2 && !find ) {
                if (c[j][i] != p.ficha) {
                    c[j][i] = b.ficha;
                    find = true;
                } else {
                    j++;
                }
            }
            break;    
        default:
            int x,y;
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while ( !isspace(c[x][y]) );
            c[x][y] = b.ficha;
            break;
    }
}

void print( char c[][4] ) {
    char barra[4] = {' ', '|', ' ', '\0'};
    char letter = 97;
    cout << "     1   2   3" << endl;
    cout << "   ------------- " << endl;
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            if (j==0) {
                cout << letter << " ";
                letter++;
            }
            cout << barra << c[i][j];
        }
        cout << barra << endl;
        cout << "   ------------- " << endl;
    }
}
void vaciar(char c[][4]) {

    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            c[i][j] = ' ';
        }
    }

}

bool diagonalPrincipal (char c[][4], char ficha, int &ubicacion) {
    int count = 0;
    bool place = true;

    for ( int i = 0; i <= 2; i++ ) {
        if (c[i][i] == ficha) {
            count++;
        } else if (!isspace(c[i][i])) {
            place = false;
        }
    }
    if (count == 2 && place) {
        ubicacion = 1;
        return true;
    }
    return false;
}
bool diagonalSecundaria (char c[][4], char ficha, int &ubicacion) {
    int j = 0, count = 0;
    bool place = true;

    for ( int i = 2; i >= 0; i--, j++ ) {
        if (c[i][j] == ficha) {
            count++;
        } else if (!isspace(c[i][j])) {
            place = false;
        }
    }
    if (count == 2 && place) {
        ubicacion = 2;
        return true;
    }
    return false;
}
bool filas (char c[][4], char ficha, int &ubicacion) {
    int i = 0, count = 0;
    bool place = true;

    while ( i <= 2 && count != 2) {
        count = 0; place = true;
        for ( int j = 0; j <= 2; j++ ) {
            if (c[i][j] == ficha) {
                count++;
            } else if (!isspace(c[i][j])) {
                place = false;
            }
        }
        i++;
    }
    if (count == 2 && i-1 == 0 && place) {
        ubicacion = 3;
        return true;
    } else if (count == 2 && i-1 == 1 && place) {
        ubicacion = 4;
        return true;
    } else if (count == 2 && i-1 == 2 && place) {
        ubicacion = 5;
        return true;
    }
    return false;
}
bool columnas (char c[][4], char ficha, int &ubicacion) {
    int i = 0, count = 0;
    bool place = true;

    while ( i <= 2 && count != 2) {
        count = 0; place = true;
        for ( int j = 0; j <= 2; j++ ) {
            if (c[j][i] == ficha) {
                count++;
            } else if (!isspace(c[j][i])) {
                place = false;
            }
        }
        i++;
    }
    if (count == 2 && i-1 == 0 && place) {
        ubicacion = 6;
        return true;
    } else if (count == 2 && i-1 == 1 && place) {
        ubicacion = 7;
        return true;
    } else if (count == 2 && i-1 == 2 && place) {
        ubicacion = 8;
        return true;
    }
    return false;
}



