#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <windows.h>
using namespace std;


int lanzarDados();
string pedirNombreJugador1();
string pedirNombreJugador2();
int quienComienza(string nombreJugador1, string nombreJugador2);
int juego(string nombreJugador1, string nombreJugador2, int comienza, string &ganador);
int evaluarDados1(int cantDados ,int dados1[]);
int evaluarDados2(int cantDados ,int dados2[]);
void estadisticas(string nombreJugador1, string nombreJugador2, int pdv, string &ganador);
void cerditos();

int lanzarDados(){ //Funcion solo para que tire dados cada vez que la llamemos. Me parece la mejor opcion que poner en cada uno de los casos como pensamos anteriormente//
    return (rand()%6+1);
}

string pedirNombreJugador1(){ //Funcion que pide el nombre del jugador 1
    string nombreJugador1;
    cout<<"Ingresar el nombre del jugador 1: "<<endl;
    rlutil::setColor(rlutil::CYAN);
    cin>>nombreJugador1;
    rlutil::setColor(rlutil::WHITE);

    return nombreJugador1;
}

string pedirNombreJugador2(){ //Funcion que pide el nombre del jugador 2
    string nombreJugador2;
    cout<<"Ingresar el nombre del jugador 2: "<<endl;
    rlutil::setColor(rlutil::RED);
    cin>>nombreJugador2;
    rlutil::setColor(rlutil::WHITE);

    return nombreJugador2;
}

int quienComienza(string nombreJugador1, string nombreJugador2){ //Funcion para saber quien comienza

    srand(time(NULL)); //Inicializacion del tiempo para los dados//

    int jugador_1[2] = {},jugador_2[2] = {}; //Se usa para los puntos de los jugadores//
    int MayorPuntaje_Jugador1 = 0, MayorPuntaje_Jugador2 = 0; //Para comparar la suma de los dos dados arrojados
    int DadoMasGrande_Jugador1 = 0, DadoMasGrande_Jugador2 = 0; //Para comparar el dado mas grande de cada uno
    char comenzar; //Para entrar y salir del while
    int ComienzaJugador1 = 0, ComienzaJugador2 = 0;

    cout << endl << "Primero debemos saber quien comienza " << endl << "Arranca tirando los dados : " << nombreJugador1 << endl;
    cout << endl << "¿Quieres comenzar? (S/N)" << endl << endl;


    cin >> comenzar; //Comenzar es una varible de tipo char para que se ingrese S o N//

    cout << endl;

    //Parte para saber quien es el que arranca a jugar la primera ronda//

    while(comenzar == 'S' || comenzar == 's'){
        cout << "Tiro de: ";
        rlutil::setColor(rlutil::CYAN);
        cout << nombreJugador1<<endl;
        rlutil::setColor(rlutil::WHITE);

        for(int i=0;i<2;i++){
            jugador_1[i] = lanzarDados();
            cout << "Dado #" << i+1 << ": " << jugador_1[i] << endl;
            MayorPuntaje_Jugador1 += jugador_1[i];
            if(jugador_1[i] > DadoMasGrande_Jugador1){
                DadoMasGrande_Jugador1 = jugador_1[i];
            }

        }

        cout << endl;
        cout << "Tiro de: ";
        rlutil::setColor(rlutil::RED);
        cout << nombreJugador2 << endl;
        rlutil::setColor(rlutil::WHITE);

        for(int g=0;g<2;g++){
            jugador_2[g] = lanzarDados();
            cout << "Dado #" << g+1 <<": "<< jugador_2[g] << endl;
            MayorPuntaje_Jugador2 += jugador_2[g];
            if(jugador_2[g] > DadoMasGrande_Jugador2){
                DadoMasGrande_Jugador2 = jugador_2[g];
            }
        }

        if(MayorPuntaje_Jugador1 > MayorPuntaje_Jugador2 || DadoMasGrande_Jugador1 > DadoMasGrande_Jugador2){
            cout << endl <<"Comienza ";
            rlutil::setColor(rlutil::CYAN);
            cout << nombreJugador1 << endl << endl;
            rlutil::setColor(rlutil::WHITE);
            ComienzaJugador1 = 1;
            comenzar = 'n';
            return ComienzaJugador1;
        }
        else{
            if(MayorPuntaje_Jugador2 > MayorPuntaje_Jugador1 || DadoMasGrande_Jugador2 > DadoMasGrande_Jugador1){
                cout << endl <<"Comienza ";
                rlutil::setColor(rlutil::RED);
                cout << nombreJugador2 << endl << endl;
                rlutil::setColor(rlutil::WHITE);
                ComienzaJugador2 = 2;
                comenzar = 'n';
                return ComienzaJugador2;
            }
            else{
                cout << endl << "Hubo un empate. Se vuelven a tirar los dados" << endl;
                comenzar = 's';
            }
        }
    }
    return 0; //Puesto por las dudas ya que arroja un warning
}

int evaluarDados1(int cantDados ,int dados1[]){ //Funcion para evaluar los dados del jugador 1

    if (cantDados == 3) {
        if( (dados1[0]!= dados1[1] && dados1[0] != dados1[2] && dados1[1] != dados1[2]) && (dados1[0] != 1 && dados1[1] != 1 && dados1[2] != 1) ){
            //Si las caras son distintas entre sí y ninguna de ellas es un as
            return 1;
        }
        else if( (dados1[0] == dados1[1] && dados1[0] == dados1[2] && dados1[1] == dados1[2]) && dados1[0] != 1 ){
            //Si las caras son iguales entre sí y no son ases:
            return 2;
        }
        else if( (dados1[0]!= dados1[1] && dados1[0] != dados1[2] && dados1[1] != dados1[2]) && (dados1[0] == 1 || dados1[1] == 1 || dados1[2] == 1) ){
            //Si las caras son distintas entre sí y hay un as entre ellas:
            return -1; // Se retornar el -1 para saber que el cerdo pierde los puntos de la ronda
        }
        else if( (dados1[0] == dados1[1] || dados1[0] == dados1[2] || dados1[1] == dados1[2]) && (dados1[0] == 1 && dados1[1] == 1 ) || (dados1[1] == 1 && dados1[2] == 1) || (dados1[0] == 1 && dados1 [2] == 1 ) ){
            //Si dos de las caras son iguales entre sí y son ases
            return -2; // Se retorna el -2 para saber que el cerdo pierde los puntos que venia acumulando en la ronda y en total
        }
        else if((dados1[0] == dados1[1] && dados1[0] == dados1[2] && dados1[1] == dados1[2]) && dados1[0] == 1){
            //Si se está lanzando con tres dados y tres de las caras son iguales entre sí y son ases:
            return -3; // Se retornar -3 para saber que el cerdo le cede los puntos al otro cerdo y pierde todo.
        }
    }
    if(cantDados == 2){
        if( (dados1[0] != dados1[1]) && (dados1[0] != 1 && dados1[1] != 1) ){
            //Si las caras son distintas entre sí y ninguna de ellas es un as
            return 1;
        }
        else if( (dados1[0] == dados1[1]) && (dados1[0] != 1) ){
            //Si las caras son iguales entre sí y no son ases:
            return 2;
        }
        else if( (dados1[0] != dados1[1]) && (dados1[0] == 1 || dados1[1] == 1) ){
            //Si las caras son distintas entre sí y hay un as entre ellas:
            return -1; // Se retornar el -1 para saber que el cerdo pierde los puntos de la ronda
        }
        else if(dados1[0] == dados1[1] && dados1[0] == 1){
            //Si dos de las caras son iguales entre sí y son ases
            return -2; // Se retorna el -2 para saber que el cerdo pierde los puntos que venia acumulando en la ronda y en total
        }
    }
    return 0; //Puesto por las dudas ya que arroja un warning
}

int evaluarDados2(int cantDados ,int dados2[]){ //Funcion para evaluar los dados del jugador 2

    if (cantDados == 3) {
        if( (dados2[0]!= dados2[1] && dados2[0] != dados2[2] && dados2[1] != dados2[2]) && (dados2[0] != 1 && dados2[1] != 1 && dados2[2] != 1) ){
            //Si las caras son distintas entre sí y ninguna de ellas es un as
            return 1;
        }
        else if( (dados2[0] == dados2[1] && dados2[0] == dados2[2] && dados2[1] == dados2[2]) && (dados2[0] != 1)){
            //Si las caras son iguales entre sí y no son ases:
            return 2;
        }
        else if( (dados2[0]!= dados2[1] && dados2[0] != dados2[2] && dados2[1] != dados2[2]) && (dados2[0] == 1 || dados2[1] == 1 || dados2[2] == 1) ){
            //Si las caras son distintas entre sí y hay un as entre ellas:
            return -1; // Se retornar el -1 para saber que el cerdo pierde los puntos de la ronda
        }
        else if( (dados2[0] == dados2[1] || dados2[0] == dados2[2] || dados2[1] == dados2[2]) && (dados2[0] == 1 && dados2[1] == 1 ) || (dados2[1] == 1 && dados2[2] == 1) || (dados2[0] == 1 && dados2 [2] == 1 ) ){
            //Si dos de las caras son iguales entre sí y son ases
            return -2; // Se retorna el -2 para saber que el cerdo pierde los puntos que venia acumulando en la ronda y en total
        }
        else if( (dados2[0] == dados2[1] && dados2[0] == dados2[2] && dados2[1] == dados2[2]) && (dados2[0] == 1 && dados2[1] == 1 && dados2[2] == 1) ){
            //Si se está lanzando con tres dados y tres de las caras son iguales entre sí y son ases:
            return -3; // Se retornar -3 para saber que el cerdo le cede los puntos al otro cerdo y pierde todo.
        }
    }
    if(cantDados == 2){
        if( (dados2[0] != dados2[1]) && (dados2[0] != 1 && dados2[1] != 1) ){
            //Si las caras son distintas entre sí y ninguna de ellas es un as
            return 1;
        }
        else if( (dados2[0] == dados2[1]) && (dados2[0] != 1) ){
            //Si las caras son iguales entre sí y no son ases:
            return 2;
        }
        else if( (dados2[0] != dados2[1]) && (dados2[0] == 1 || dados2[1] == 1) ){
            //Si las caras son distintas entre sí y hay un as entre ellas:
            return -1; // Se retornar el -1 para saber que el cerdo pierde los puntos de la ronda
        }
        else if(dados2[0] == dados2[1] && dados2[0] == 1){
            //Si dos de las caras son iguales entre sí y son ases
            return -2; // Se retorna el -2 para saber que el cerdo pierde los puntos que venia acumulando en la ronda y en total
        }
    }
    return 0; //Puesto por las dudas ya que arroja un warning
}

int juego(string nombreJugador1, string nombreJugador2, int comienza, string &ganador){ //"comienza" es para saber que jugador salio en la funcion quiencomienza. 1 para el jug 1 y 2 para el jug 2

    srand(time(NULL)); //Inicializacion del tiempo para los dados//

    int jugador_1[3]={},jugador_2[3]={}; //Se usa para los puntos de los jugadores//
    bool turnoJugador1 = false, turnoJugador2 = false; //Para saber de quien es el turno//
    bool barroJugador1 = false, barroJugador2 = false; //Para saber si algun jugador se hundio en el barro//
    int contOinkJugador1 = 0, contOinkJugador2 = 0; //Contador de Oinks
    char continuar = 'n'; //Para que entre al while//
    int rondasJugador1 = 1, rondasJugador2 = 1, puntosJugador1 = 0, puntosJugador2 = 0, puntosRondaJugador1 = 0, puntosRondaJugador2 = 0, puntosEvaluadosJugador1 = 0, puntosEvaluadosJugador2 = 0;
    int cantDados; //Para saber la cantidad de dados a arrojar//
    int analizarDados1, analizarDados2; //Para que me retorne la evaluacion de dados//
    int maxLanzamientosJugador1 = 0, maxLanzamientosJugador2 = 0; //Para la comparacion de cuantas veces lanzo cada jugador y comparar al final del juego
    int masTrufas1 = 0, masTrufas2 = 0, Cada50Trufas1 = 0, Cada50Trufas2 = 0, Oinks1 = 0, Oinks2 = 0, cerdoCodicioso1 = 0, cerdoCodicioso2 = 0, sumaPDV1 = 0, sumaPDV2 = 0, puntosGanador = 0;


    Sleep(1000);

    if(comienza == 1){
        turnoJugador1 = true;
    }
    else{
        turnoJugador2 = true;
    }


    for(int i=0;i<10;i++){

        int lanzamientosJugador1 = 1; //Para contar los lanzamientos que realiza el jugador 1
        int lanzamientosJugador2 = 1; //Para contar los lanzamientos que realiza el jugador 2

        while ( continuar == 'n' || continuar == 'N'){

            ////////////////////// PARTE PRIMER JUGADOR - EVALUACION DE DADOS CON 2 Y 3 /////////////////////////
            if(turnoJugador1 == true){
                if(barroJugador1 == true || barroJugador2 == true){
                    rlutil::setColor(rlutil::LIGHTMAGENTA);
                    cout << "Gran Cerdo" << endl;
                    rlutil::setColor(rlutil::WHITE);
                    cout << "-------------------------------------------------------------------------------" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    cout << nombreJugador1;
                    rlutil::setColor(rlutil::WHITE);
                    cout << ": " << puntosJugador1 << " Trufas acumuladas" << "                        ";
                    rlutil::setColor(rlutil::RED);
                    cout << nombreJugador2;
                    rlutil::setColor(rlutil::WHITE);
                    cout << ": " <<puntosJugador2 << " Trufas acumuladas" << endl;
                    cout << endl<< "Turno: ";
                    rlutil::setColor(rlutil::CYAN);
                    cout << nombreJugador1 ;
                    rlutil::setColor(rlutil::WHITE);
                    cout << "            " << "Ronda: " << rondasJugador1 << "            " << "Lanzamiento #" << lanzamientosJugador1 <<endl;
                    cantDados = 3;

                    for(int a=0; a<cantDados; a++){
                            jugador_1[a] = lanzarDados();
                            cout << endl << "Dado #" << a+1 <<": "<< jugador_1[a] << endl << endl;
                        }

                    analizarDados1 = evaluarDados1(cantDados, jugador_1);

                    if(analizarDados1 == 1){
                            puntosRondaJugador1 = jugador_1[0] + jugador_1[1] + jugador_1[2];
                            puntosEvaluadosJugador1 += jugador_1[0] + jugador_1[1] + jugador_1[2];
                            cout << "Puntos de la ronda: " << puntosRondaJugador1 << endl;
                            cout << "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            cout << "Puede decidir si volver a lanzar los dados o plantarse y ceder el turno al otro cerdo." << endl;
                            cout << endl << "¿Continuar? S para pasar de turno / N para tirar de nuevo." << endl;
                            cin >> continuar;
                        }
                        else if(analizarDados1 == 2){
                            cout << endl << "OINK" << endl << endl;
                            contOinkJugador1++;
                            puntosEvaluadosJugador1 += (jugador_1[0] + jugador_1[1] + jugador_1[2]) * 2;
                            puntosRondaJugador1 = (jugador_1[0] + jugador_1[1] + jugador_1[2]) * 2;
                            cout << "Puntos de la ronda: " << puntosRondaJugador1 << endl;
                            cout << "Acumulas trufas por el doble de la suma de las caras al total de la la ronda" << endl;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            cout << "Estas obligado a tirar de nuevo" << endl;
                            system("pause");
                        }
                        else if(analizarDados1 == -1){
                            cout << "Pierdes todas las trufas que venias acumulando en la ronda actual y le cedes el turno al otro cerdo." << endl;
                            puntosEvaluadosJugador1 = 0;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            continuar = 's';
                            system("pause");
                        }
                        else if(analizarDados1 == -2){
                            cout<< "Te hundiste en el barro. Pierdes todas las trufas que venias acumulando en las rondas anteriores y en la actual ademas le cedes el turno al otro cerdo." << endl;
                            puntosJugador1 = 0;
                            puntosRondaJugador1 = 0;
                            puntosEvaluadosJugador1 = 0;
                            barroJugador1 = true;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            continuar = 's';
                            system("pause");
                        }
                        else if(analizarDados1 == -3){
                            cout << "Le transferis todas las trufas que venias acumulando en las rondas anteriores y en la actual a "<<nombreJugador2<<". Pierdes el turno."<<endl;
                            puntosJugador2 += puntosRondaJugador1 + puntosJugador1;
                            puntosJugador1 = 0;
                            puntosRondaJugador1 = 0;
                            continuar = 's';
                            system("pause");
                        }

                }
                else if(puntosJugador1 > 50 && puntosJugador2 > 50){
                        rlutil::setColor(rlutil::LIGHTMAGENTA);
                        cout << "Gran Cerdo" << endl;
                        rlutil::setColor(rlutil::WHITE);
                        cout << "-------------------------------------------------------------------------------" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        cout << nombreJugador1;
                        rlutil::setColor(rlutil::WHITE);
                        cout << ": " << puntosJugador1 << " Trufas acumuladas" << "                        ";
                        rlutil::setColor(rlutil::RED);
                        cout << nombreJugador2;
                        rlutil::setColor(rlutil::WHITE);
                        cout << ": " <<puntosJugador2 << " Trufas acumuladas" << endl;
                        cout << endl<< "Turno: ";
                        rlutil::setColor(rlutil::CYAN);
                        cout << nombreJugador1 ;
                        rlutil::setColor(rlutil::WHITE);
                        cout << "            " << "Ronda: " << rondasJugador1 << "            " << "Lanzamiento #" << lanzamientosJugador1 <<endl;
                        cantDados = 3;

                        for(int s=0; s<cantDados; s++){
                            jugador_1[s] = lanzarDados();
                            cout << endl << "Dado #" << s+1 <<": "<< jugador_1[s] << endl << endl;
                        }

                        analizarDados1 = evaluarDados1(cantDados, jugador_1);

                        if(analizarDados1 == 1){
                            puntosRondaJugador1 = jugador_1[0] + jugador_1[1] + jugador_1[2];
                            puntosEvaluadosJugador1 += jugador_1[0] + jugador_1[1] + jugador_1[2];
                            cout << "Puntos de la ronda: " << puntosRondaJugador1 << endl << endl;
                            cout << "Sumaste: "<< puntosEvaluadosJugador1 << endl << endl;
                            cout << "Puede decidir si volver a lanzar los dados o plantarse y ceder el turno al otro cerdo." << endl;
                            cout << endl << "¿Continuar? S para pasar de turno / N para tirar de nuevo." << endl;
                            cin >> continuar;
                        }
                        else if(analizarDados1 == 2){
                            cout << endl << "OINK" << endl << endl;
                            contOinkJugador1++;
                            puntosEvaluadosJugador1 += (jugador_1[0] + jugador_1[1] + jugador_1[2]) * 2;
                            puntosRondaJugador1 = jugador_1[0] + jugador_1[1] + jugador_1[2];
                            cout << "Puntos de la ronda: " << puntosRondaJugador1 << endl;
                            cout << "Acumulas trufas por el doble de la suma de las caras al total de la la ronda" << endl;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            cout << "Estas obligado a tirar de nuevo" << endl;
                            system("pause");
                        }
                        else if(analizarDados1 == -1){
                            cout << "Pierdes todas las trufas que venias acumulando en la ronda actual y le cedes el turno al otro cerdo." << endl;
                            puntosEvaluadosJugador1 = 0;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            continuar = 's';
                            system("pause");
                        }
                        else if(analizarDados1 == -2){
                            cout<< "Te hundiste en el barro. Pierdes todas las trufas que venias acumulando en las rondas anteriores y en la actual ademas le cedes el turno al otro cerdo." << endl;
                            puntosJugador1 = 0;
                            puntosRondaJugador1 = 0;
                            puntosEvaluadosJugador1 = 0;
                            barroJugador1 = true;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            continuar = 's';
                            system("pause");
                        }
                        else if(analizarDados1 == -3){
                            cout << "Le transferis todas las trufas que venias acumulando en las rondas anteriores y en la actual a "<<nombreJugador2<<". Pierdes el turno."<<endl;
                            puntosJugador2 += puntosRondaJugador1 + puntosJugador1;
                            puntosJugador1 = 0;
                            puntosRondaJugador1 = 0;
                            continuar = 's';
                            system("pause");
                        }
                    }
                    else{
                        rlutil::setColor(rlutil::LIGHTMAGENTA);
                        cout << "Gran Cerdo" << endl;
                        rlutil::setColor(rlutil::WHITE);
                        cout << "-------------------------------------------------------------------------------" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        cout << nombreJugador1;
                        rlutil::setColor(rlutil::WHITE);
                        cout << ": " << puntosJugador1 << " Trufas acumuladas" << "                        ";
                        rlutil::setColor(rlutil::RED);
                        cout << nombreJugador2;
                        rlutil::setColor(rlutil::WHITE);
                        cout << ": " <<puntosJugador2 << " Trufas acumuladas" << endl;
                        cout << endl<< "Turno: ";
                        rlutil::setColor(rlutil::CYAN);
                        cout << nombreJugador1 ;
                        rlutil::setColor(rlutil::WHITE);
                        cout << "            " << "Ronda: " << rondasJugador1 << "            " << "Lanzamiento #" << lanzamientosJugador1 <<endl;
                        cantDados = 2;

                        for(int d=0; d<cantDados; d++){
                            jugador_1[d] = lanzarDados();
                            cout << endl << "Dado #" << d+1 <<": "<< jugador_1[d] << endl << endl;
                        }

                        analizarDados1 = evaluarDados1(cantDados, jugador_1);

                        if(analizarDados1 == 1){
                            puntosRondaJugador1 = jugador_1[0] + jugador_1[1];
                            puntosEvaluadosJugador1 += jugador_1[0] + jugador_1[1];
                            cout << "Puntos de la ronda: " << puntosRondaJugador1 << endl;
                            cout << "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            cout << "Puede decidir si volver a lanzar los dados o plantarse y ceder el turno al otro cerdo." << endl;
                            cout << endl << "¿Continuar? S para pasar de turno / N para tirar de nuevo." << endl;
                            cin >> continuar;
                        }
                        else if(analizarDados1 == 2){
                            cout << endl << "OINK" << endl << endl;
                            contOinkJugador1++;
                            puntosEvaluadosJugador1 += (jugador_1[0] + jugador_1[1]) * 2;
                            puntosRondaJugador1 = jugador_1[0] + jugador_1[1];
                            cout << "Puntos de la ronda: " << puntosRondaJugador1 << endl;
                            cout << "Acumulas trufas por el doble de la suma de las caras al total de la la ronda" << endl;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            cout << "Estas obligado a tirar de nuevo" << endl;
                            system("pause");
                        }
                        else if(analizarDados1 == -1){
                            cout << "Pierdes todas las trufas que venias acumulando en la ronda actual y le cedes el turno al otro cerdo." << endl;
                            puntosEvaluadosJugador1 = 0;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            continuar = 's';
                            system("pause");
                        }
                        else if(analizarDados1 == -2){
                            cout<< "Te hundiste en el barro. Pierdes todas las trufas que venias acumulando en las rondas anteriores y en la actual ademas le cedes el turno al otro cerdo." << endl;
                            puntosJugador1 = 0;
                            puntosRondaJugador1 = 0;
                            puntosEvaluadosJugador1 = 0;
                            barroJugador1 = true;
                            cout<< "Sumaste: "<< puntosEvaluadosJugador1 << endl;
                            continuar = 's';
                            system("pause");
                        }
                    }
                }

            ////////////////////// PARTE SEGUNDO JUGADOR - EVALUACION DE DADOS CON 2 Y 3 /////////////////////////

            else{
                if(turnoJugador2 == true){
                    if(barroJugador2 == true || barroJugador1 ==true){
                        rlutil::setColor(rlutil::LIGHTMAGENTA);
                        cout << "Gran Cerdo" << endl;
                        rlutil::setColor(rlutil::WHITE);
                        cout << "-------------------------------------------------------------------------------" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        cout << nombreJugador1 ;
                        rlutil::setColor(rlutil::WHITE);
                        cout << ": " << puntosJugador1 << " Trufas acumuladas"<< "                        " ;
                        rlutil::setColor(rlutil::RED);
                        cout << nombreJugador2 ;
                        rlutil::setColor(rlutil::WHITE);
                        cout << ": " <<puntosJugador2  << " Trufas acumuladas"<< endl;
                        cout << endl << "Turno: ";
                        rlutil::setColor(rlutil::RED);
                        cout<< nombreJugador2;
                        rlutil::setColor(rlutil::WHITE);
                        cout << "            " << "Ronda: " << rondasJugador2 << "            " << "Lanzamiento #" << lanzamientosJugador2 <<endl;

                        cantDados = 3;

                        for(int f=0; f<cantDados; f++){
                            jugador_2[f] = lanzarDados();
                            cout << endl << "Dado #" << f+1 <<": "<< jugador_2[f] << endl << endl;
                        }

                        analizarDados2 = evaluarDados2(cantDados, jugador_2);

                            if(analizarDados2 == 1){
                                puntosEvaluadosJugador2 += jugador_2[0] + jugador_2[1] + jugador_2[2];
                                puntosRondaJugador2 = jugador_2[0] + jugador_2[1] + jugador_2[2];
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Sumaste: " << puntosEvaluadosJugador2 << endl;
                                cout << "Puede decidir si volver a lanzar los dados o plantarse y ceder el turno al otro cerdo." << endl;
                                cout << "¿Continuar? S para pasar de turno / N para tirar de nuevo." << endl;
                                cin >> continuar;
                            }
                            else if(analizarDados2 == 2){
                                cout << "OINK" << endl;
                                contOinkJugador2++;
                                puntosEvaluadosJugador2 += (jugador_2[0] + jugador_2[1] + jugador_2[2]) * 2;
                                puntosRondaJugador2 = jugador_2[0] + jugador_2[1] + jugador_2[2];
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Acumulas trufas por el doble de la suma de las caras al total de la la ronda" << endl;
                                cout << "Sumaste: "<< puntosEvaluadosJugador2 << endl << endl << endl;
                                cout << "Estas obligado a tirar de nuevo" << endl;
                                continuar = 'n';
                                system("pause");
                            }
                            else if(analizarDados2 == -1){
                                cout << "Pierdes todas las trufas que venias acumulando en la ronda actual y le cedes el turno al otro cerdo." << endl;
                                puntosEvaluadosJugador2 = 0;
                                cout << "Sumaste: " << puntosEvaluadosJugador2 << endl;
                                continuar = 's';
                                system("pause");
                            }
                            else if(analizarDados2 == -2){
                                cout<< "Te hundiste en el barro. Pierdes todas las trufas que venias acumulando en las rondas anteriores y en la actual, ademas le cedes el turno al otro cerdo." << endl;
                                puntosJugador2 = 0;
                                puntosRondaJugador2 = 0;
                                puntosEvaluadosJugador2 = 0;
                                barroJugador2 = true;
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Sumaste: "<< puntosEvaluadosJugador2 << endl;
                                continuar = 's';
                                system("pause");
                            }
                            else if(analizarDados2 == -3){
                                cout << "Le transferis todas las trufas que venias acumulando en las rondas anteriores y en la actual a "<<nombreJugador1<<". Pierdes el turno."<<endl;
                                puntosJugador1 += puntosRondaJugador2 + puntosJugador2;
                                puntosJugador2 = 0;
                                puntosRondaJugador2 = 0;
                                continuar = 's';
                                system("pause");
                            }

                    }
                    else{
                        if(puntosJugador1 > 50 && puntosJugador2 > 50){
                            rlutil::setColor(rlutil::LIGHTMAGENTA);
                            cout << "Gran Cerdo" << endl;
                            rlutil::setColor(rlutil::WHITE);
                            cout << "-------------------------------------------------------------------------------" << endl;
                            rlutil::setColor(rlutil::CYAN);
                            cout << nombreJugador1 ;
                            rlutil::setColor(rlutil::WHITE);
                            cout << ": " << puntosJugador1 << " Trufas acumuladas"<< "                        " ;
                            rlutil::setColor(rlutil::RED);
                            cout << nombreJugador2 ;
                            rlutil::setColor(rlutil::WHITE);
                            cout << ": " <<puntosJugador2  << " Trufas acumuladas"<< endl;
                            cout << endl << "Turno: ";
                            rlutil::setColor(rlutil::RED);
                            cout<< nombreJugador2;
                            rlutil::setColor(rlutil::WHITE);
                            cout << "            " << "Ronda: " << rondasJugador2 << "            " << "Lanzamiento #" << lanzamientosJugador2 <<endl;

                            cantDados = 3;

                            for(int g=0; g<cantDados; g++){
                            jugador_2[g] = lanzarDados();
                            cout << endl << "Dado #" << g+1 << ": " << jugador_2[g] << endl << endl;
                            }

                            analizarDados2 = evaluarDados2(cantDados, jugador_2);

                            if(analizarDados2 == 1){
                                puntosEvaluadosJugador2 += jugador_2[0] + jugador_2[1] + jugador_2[2];
                                puntosRondaJugador2 = jugador_2[0] + jugador_2[1] + jugador_2[2];
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Sumaste: " << puntosEvaluadosJugador2 << endl;
                                cout << "Puede decidir si volver a lanzar los dados o plantarse y ceder el turno al otro cerdo." << endl;
                                cout << "¿Continuar? S para pasar de turno / N para tirar de nuevo." << endl;
                                cin >> continuar;
                            }
                            else if(analizarDados2 == 2){
                                cout << "OINK" << endl;
                                contOinkJugador2++;
                                puntosEvaluadosJugador2 += (jugador_2[0] + jugador_2[1] + jugador_2[2]) * 2;
                                puntosRondaJugador2 = jugador_2[0] + jugador_2[1] + jugador_2[2];
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Acumulas trufas por el doble de la suma de las caras al total de la la ronda" << endl;
                                cout << "Sumaste: "<< puntosEvaluadosJugador2 << endl << endl << endl;
                                cout << "Estas obligado a tirar de nuevo" << endl;
                                continuar = 'n';
                                system("pause");
                            }
                            else if(analizarDados2 == -1){
                                cout << "Pierdes todas las trufas que venias acumulando en la ronda actual y le cedes el turno al otro cerdo." << endl;
                                puntosEvaluadosJugador2 = 0;
                                cout << "Sumaste: " << puntosEvaluadosJugador2 << endl;
                                continuar = 's';
                                system("pause");
                            }
                            else if(analizarDados2 == -2){
                                cout<< "Te hundiste en el barro. Pierdes todas las trufas que venias acumulando en las rondas anteriores y en la actual, ademas le cedes el turno al otro cerdo." << endl;
                                puntosJugador2 = 0;
                                puntosRondaJugador2 = 0;
                                puntosEvaluadosJugador2 = 0;
                                barroJugador2 = true;
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Sumaste: "<< puntosEvaluadosJugador2 << endl;
                                continuar = 's';
                                system("pause");
                            }
                            else if(analizarDados2 == -3){
                                cout << "Le transferis todas las trufas que venias acumulando en las rondas anteriores y en la actual a "<<nombreJugador1<<". Pierdes el turno."<<endl;
                                puntosJugador1 += puntosRondaJugador2 + puntosJugador2;
                                puntosJugador2 = 0;
                                continuar = 's';
                                system("pause");
                            }

                        }
                        else{
                            rlutil::setColor(rlutil::LIGHTMAGENTA);
                            cout << "Gran Cerdo" << endl;
                            rlutil::setColor(rlutil::WHITE);
                            cout << "-------------------------------------------------------------------------------" << endl;
                            rlutil::setColor(rlutil::CYAN);
                            cout << nombreJugador1 ;
                            rlutil::setColor(rlutil::WHITE);
                            cout << ": " << puntosJugador1 << " Trufas acumuladas"<< "                        " ;
                            rlutil::setColor(rlutil::RED);
                            cout << nombreJugador2 ;
                            rlutil::setColor(rlutil::WHITE);
                            cout << ": " <<puntosJugador2  << " Trufas acumuladas"<< endl;
                            cout << endl << "Turno: ";
                            rlutil::setColor(rlutil::RED);
                            cout<< nombreJugador2;
                            rlutil::setColor(rlutil::WHITE);
                            cout << "            " << "Ronda: " << rondasJugador2 << "            " << "Lanzamiento #" << lanzamientosJugador2 <<endl;
                            cantDados = 2;

                            for(int h=0; h < cantDados; h++){
                                jugador_2[h] = lanzarDados();
                                cout << endl << "Dado #" << h+1 << ": " << jugador_2[h] << endl << endl;
                            }
                            analizarDados2 = evaluarDados2(cantDados, jugador_2);
                            if(analizarDados2 == 1){
                                puntosEvaluadosJugador2 += jugador_2[0] + jugador_2[1];
                                puntosRondaJugador2 = jugador_2[0] + jugador_2[1];
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Sumaste: " << puntosEvaluadosJugador2 << endl;
                                cout << "Puede decidir si volver a lanzar los dados o plantarse y ceder el turno al otro cerdo." << endl;
                                cout << "¿Continuar? S para pasar de turno / N para tirar de nuevo." << endl;
                                cin >> continuar;
                            }
                            else if(analizarDados2 == 2){
                                cout << "OINK" << endl;
                                contOinkJugador2++;
                                puntosEvaluadosJugador2 += (jugador_2[0] + jugador_2[1]) * 2;
                                puntosRondaJugador2 = (jugador_2[0] + jugador_2[1]) * 2;
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Acumulas trufas por el doble de la suma de las caras al total de la la ronda" << endl;
                                cout << "Sumaste: "<< puntosEvaluadosJugador2 << endl << endl << endl;
                                cout << "Estas obligado a tirar de nuevo" << endl;
                                continuar = 'n';
                                system("pause");
                            }
                            else if(analizarDados2 == -1){
                                cout << "Pierdes todas las trufas que venias acumulando en la ronda actual y le cedes el turno al otro cerdo." << endl;
                                puntosEvaluadosJugador2 = 0;
                                cout << "Sumaste: " << puntosEvaluadosJugador2 << endl;
                                continuar = 's';
                                system("pause");
                            }
                            else if(analizarDados2 == -2){
                                cout<< "Te hundiste en el barro. Pierdes todas las trufas que venias acumulando en las rondas anteriores y en la actual, ademas le cedes el turno al otro cerdo." << endl;
                                puntosJugador2 = 0;
                                puntosRondaJugador2 = 0;
                                puntosEvaluadosJugador2 = 0;
                                barroJugador2 = true;
                                cout << "Puntos de la ronda: " << puntosRondaJugador2 << endl;
                                cout << "Sumaste: "<< puntosEvaluadosJugador2 << endl;
                                continuar = 's';
                                system("pause");
                            }
                        }
                    }
                }
            }

            if(continuar == 's' || continuar == 'S'){
                if(turnoJugador1 == true){
                   if(puntosEvaluadosJugador1 > 0){
                        puntosJugador1 += puntosEvaluadosJugador1;
                        puntosRondaJugador1 = 0;
                        puntosEvaluadosJugador1 = 0;

                    }
                    else{
                        puntosRondaJugador1 = 0;
                        puntosEvaluadosJugador1 = 0;

                    }
                }
                else{
                    if(puntosEvaluadosJugador2 > 0){
                        puntosJugador2 += puntosEvaluadosJugador2;
                        puntosEvaluadosJugador2 = 0;
                        puntosRondaJugador2 = 0;

                    }
                    else{            //Este if y else funciona como para saber si la persona perdio los puntos. El 0 viene desde mas arriba es decir que si los puntos evaluados que vienen son 0, entonces les saca los puntos.
                        puntosRondaJugador2 = 0;
                        puntosEvaluadosJugador2 = 0;

                    }
                }

            }
            else if(turnoJugador1 == true){
                    lanzamientosJugador1++;

                }
                else{
                    lanzamientosJugador2++;

                }
                rlutil::cls();
            }

        //////////////////////// ESTO ES FUERA DEL WHILE ///////////////////////////

        continuar = 'n';

        ////////////////////////// PARA SABER LA MAX CANTIDAD DE VECES QUE TIRO CADA JUGADOR //////////////////////////////
        if(lanzamientosJugador1 > maxLanzamientosJugador1){
            maxLanzamientosJugador1 = lanzamientosJugador1;
        }
        if(lanzamientosJugador2 > maxLanzamientosJugador2){
            maxLanzamientosJugador2 = lanzamientosJugador2;
        }

        ///////////////////////// PARA QUE CAMBIE DE TURNO Y LE TOQUE AL OTRO JUGADOR //////////////////////////
        if(turnoJugador1 == true){
            rondasJugador1++;
            turnoJugador1 = false;
            turnoJugador2 = true;
        }
        else{
            rondasJugador2++;
            turnoJugador2 = false;
            turnoJugador1 = true;
        }
    }

    ////////////////////////// ESTO ES FUERA DEL FOR //////////////////////////////

    /////////////////////// DESARROLLO DE FIN DE JUEGO ////////////////////////////

    if(puntosJugador1 == puntosJugador2){
        masTrufas1 = 5;
        masTrufas2 = 5;
    }
    else if(puntosJugador1 > puntosJugador2){
        masTrufas1 = 5;
    }
    else{
        masTrufas2 = 5;
    }

    Cada50Trufas1 = puntosJugador1 / 50;
    Cada50Trufas2 = puntosJugador2 / 50;

    Oinks1 = 2 * contOinkJugador1;
    Oinks2 = 2 * contOinkJugador2;

    if(maxLanzamientosJugador1 == maxLanzamientosJugador2){
        cerdoCodicioso1 = 3;
        cerdoCodicioso2 = 3;
    }
    else if(maxLanzamientosJugador1 > maxLanzamientosJugador2){
        cerdoCodicioso1 = 3;
    }
    else{
        cerdoCodicioso2 = 3;
    }

    sumaPDV1 = masTrufas1 + Cada50Trufas1 + Oinks1 + cerdoCodicioso1;
    sumaPDV2 = masTrufas2 + Cada50Trufas2 + Oinks2 + cerdoCodicioso2;

    if(sumaPDV1 == sumaPDV2){
        ganador = "empate";
    }
    else if(sumaPDV1 > sumaPDV2){
        ganador = nombreJugador1;
        puntosGanador = sumaPDV1;
    }
    else{
        ganador = nombreJugador2;
        puntosGanador = sumaPDV2;
    }

    ///////////////////////// HITO DE FIN DE JUEGO ///////////////////////////

    rlutil::setColor(rlutil::LIGHTMAGENTA);
    cout << "Gran Cerdo" << endl;
    rlutil::setColor(rlutil::WHITE);
    cout << "--------------------------------------------------------------------------" << endl << endl;

    cout << "        HITO" << "                     " ;
    rlutil::setColor(rlutil::CYAN);
    cout << nombreJugador1 << "                  " ;
    rlutil::setColor(rlutil::RED);
    cout << nombreJugador2 << endl;
    rlutil::setColor(rlutil::WHITE);
    cout << "--------------------------------------------------------------------------" << endl;

    cout << "Mas trufas en total:           " <<  masTrufas1 << " " << "(" << puntosJugador1 << " trufas)" << "          " << masTrufas2 << " " << "(" << puntosJugador2<< " trufas)" << endl;
    cout << "Cada 50 trufas:                " << Cada50Trufas1 << " " << "(" << (Cada50Trufas1 * 50) << " trufas)" << "          " << Cada50Trufas2 << " " << "(" << (Cada50Trufas2 * 50) << " trufas)" <<endl;
    cout << "Oinks:                         " << Oinks1 << " " << "("  << contOinkJugador1 << " Oinks)" << "           " << Oinks2 << " "<< "(" << contOinkJugador2 << " Oinks)"  << endl;
    cout << "Cerdo codisioso:               " << cerdoCodicioso1 << " " << "(" << maxLanzamientosJugador1 << " lanzamientos)" << "    " << cerdoCodicioso2 <<" " << "(" << maxLanzamientosJugador2 << " lanzamientos)" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "TOTAL                                " << sumaPDV1 << "                      " << sumaPDV2 << endl << endl;

    cout << "GANADOR: " << ganador << " con "<< puntosGanador<<" puntos de victoria."<< endl;

    if(sumaPDV1 == sumaPDV2){
        return 0;
    }
    else if(sumaPDV1 > sumaPDV2){
        return sumaPDV1;
    }
    else{
        return sumaPDV2;
    }
}

void estadisticas(string nombreJugador1, string nombreJugador2, int pdv, string &ganador){  //Se paso el string de ganador por referencia. Lo modifica en la funcion juego y me lo devuelve modificado a esta funcion.
    if(pdv == -1){
        cout << "Aun no hay ganadores " << endl;
        Sleep(700);
        cout << "Lamentablemente :( " << endl;
    }
    else if(pdv == 0){
        cout << "Es un empate \nPero no se desanimen, pueden volver a intentarlo"<<endl;
    }
    else{
        cout << "El o la ganador/a es: "<< ganador <<" con "<< pdv <<" puntos de victoria." << endl;
    }
}

void cerditos(){
    cout << "---------------------------------" << endl;
    rlutil::setColor(rlutil::GREEN);
    cout << "        !Grupo Numero 38!" << endl;
    rlutil::setColor(rlutil::WHITE);
    cout << "---------------------------------" << endl;
    cout << "Caminos, Tobias     Legajo: 27554" << endl;
    cout << "Paz, Ayrton         Legajo: 28006" << endl;
    cout << "Leguizamon, Nahuel  Legajo: 29984" << endl;
    cout << "---------------------------------" << endl;
}


#endif // FUNCIONES_H_INCLUDED
