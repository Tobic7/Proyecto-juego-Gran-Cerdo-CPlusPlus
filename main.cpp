#include <iostream>
#include <cstdlib>
#include <time.h>
#include "rlutil.h"
#include <windows.h>


using namespace std;

#include "funciones.h"

int main()
{
    int opcion, comienza, pdv = -1;
    string nombreJugador1, nombreJugador2, ganador;
    char resp;

    do{

    rlutil::cls();

    rlutil::locate(50, 8);
    rlutil::setColor(rlutil::LIGHTMAGENTA);
    cout<<" GRAN CERDO "<<endl;
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(50, 10);
    cout<<" 1 - Jugar "<<endl;
    rlutil::locate(50, 11);
    cout<<" 2 - Estadisticas "<<endl;
    rlutil::locate(50, 12);
    cout<<" 3 - Cerditos "<<endl;
    rlutil::locate(50, 14);
    cout<<" 0 - Salir "<<endl;


    cin >> opcion;

    cout<<endl;

    switch(opcion){
    case 1:
        rlutil::cls();
        nombreJugador1 = pedirNombreJugador1();
        nombreJugador2 = pedirNombreJugador2();

        system("pause");
        rlutil::cls();

        comienza = quienComienza(nombreJugador1, nombreJugador2);

        system("pause");
        rlutil::cls();

        pdv = juego(nombreJugador1, nombreJugador2, comienza, ganador);

        system("pause");
        rlutil::cls();
        break;
    case 2:
        rlutil::cls();
        estadisticas(nombreJugador1, nombreJugador2, pdv, ganador);
        system("pause");
        break;
    case 3:
        rlutil::cls();
        cerditos();
        system("pause");
        break;
    case 0:
        rlutil::cls();
        cout << "Desea salir del juego?"<<endl;
        cout << "Ingrese (S) para 'SI' o (N) para 'NO'"<<endl;
        cin >> resp;
        if (resp == 'S' || resp == 's'){
            cout << "Saliendo el juego..."<<endl;
        }
        else{
            cout << "Ok, a seguir jugando!"<<endl;
            opcion = 1;
        }
        system("pause");
        break;
    default:
        cout<<"La opcion ingresada es incorrecta" << endl;
        system("pause");
        break;
    }


    }while(opcion != 0);
}

