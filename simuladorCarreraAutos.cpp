/*
    * Autores:
        * Ignacio Mora Barrientos.
        * Joaquin Pérez Larrañaga.
*/

// Bibliotecas necesarias
#include <iostream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <random>
#include <chrono>
#include <mutex>
#include <vector>

using namespace std;
using namespace this_thread;
using namespace chrono;

// Variables globales
#define mtrMinimo 50
#define autoMinimo 2
int intPosicionCarrera = 1;
vector<int> arrPosiciones;
// Inicializar mutex
mutex newMutex;
// Cambiar color al texto
#define clrVerde "\033[32m"
#define clrReset "\033[0m"


// Estructura de auto
struct varAuto {
    int intPosicionFinal = 0;
    int intMetrosRecorridos = 0;
    int intUltimoAvance = 0;
    int intIndice = 0;
};

/*
    Funcion para crear valores aleatorios en un rango determinado
    Hace empleo de libreria random para evitar que en cada iteracion de la hebra se genere el mismo valor
*/
int funAleatorio(int min, int max){
    // Crear una variable para almacenar el motor
    random_device randomEngine;
    // Crear rango de valores
    uniform_int_distribution<int> rango(min, max);
    // Devolver valor generado
    return rango(randomEngine);
}

/*
    Funcion para validar argumentos
    Devuelve un 1 si encuentra un error y un 0 si no encuentra ninguno
*/
int funValidacion(int argc, char* argv[]){
    // Validacion de argumentos al momento de ejecutar
    if (argc != 3) {
        cerr << "Uso correcto del comando: " << argv[0] << " <cantidad de kilometros> <cantidad de autos>" << endl;
        return 1;
    }
    // Validacion de longitud de la carrera
    if (atoi(argv[1]) < mtrMinimo) {
        cerr << "La cantidad de kilometros de la carrera debe ser almenos " << mtrMinimo << endl;
        return 1;
    }
    // Validacion de cantidad de autos
    if (atoi(argv[2]) < autoMinimo) {
        cerr << "Debe/n de haber almenos "<< autoMinimo << " auto/s para simular la carrera." << endl;
        return 1;
    }
    return 0;
}

/*
    Funcion que se encarga del avance de un auto
    El auto avanza hasta recorrer la carrera por completo
*/
varAuto funAvance(varAuto& competidor, int mtrCarrera){
    do{
        // Aleatorizar avance del auto
        competidor.intUltimoAvance = funAleatorio(0, 10);
        // Guardar avance total del auto
        competidor.intMetrosRecorridos += competidor.intUltimoAvance;
        
        #ifdef debug
            cout << "Avance aleatorio del auto: " << competidor.intUltimoAvance << endl;
            cout << "Metros recorridos del auto: " << competidor.intMetrosRecorridos << endl;
        #endif

        // Cout
        if (competidor.intMetrosRecorridos < mtrCarrera){
            // Si con el ultimo avance aun no llega a la meta
            cout << "Auto " << competidor.intIndice << " avanza " << competidor.intUltimoAvance << " metros (total: " << competidor.intMetrosRecorridos << " metros)" << endl;
            // Aleatorizar tiempo en que el competidor puede volver a avanzar (valores entre 100 y 500)
            int intTiempo = funAleatorio(100, 500);

            #ifdef debug
            cout << "Tiempo generado: " << intTiempo << endl;
            #endif

            // Espera de 100 a 500 ms entre cada iteracion de la hebra
            sleep_for(milliseconds(intTiempo));
        }       

    } while (competidor.intMetrosRecorridos < mtrCarrera);
        // Si con el ultimo avance llega a la meta, actualizar marcador de posiciones global
        newMutex.lock();
        arrPosiciones.push_back(competidor.intIndice);
        competidor.intPosicionFinal = intPosicionCarrera;
        intPosicionCarrera += 1;
        newMutex.unlock();
        // Mostar por pantalla
        cout << clrVerde << "Auto " << competidor.intIndice << " avanza " << competidor.intUltimoAvance << " metros y termina la carrera en el lugar " << competidor.intPosicionFinal << clrReset << endl;
        // Devolver a competidor
        return competidor;
}

// Funcion main
int main(int argc, char* argv[]) {
    // Validar argumentos
    if (funValidacion(argc, argv) != 0) {
        return 1;
    }
    // Asignar valores del parametro a variables
    int intMetros = atoi(argv[1]);
    int intAutos = atoi(argv[2]);
    
    #ifdef debug
        // Obtener cantidad de procesadores
        int intProcesadores = sysconf(_SC_NPROCESSORS_ONLN);
        cout << "Cantidad de procesadores del hardware: " << intProcesadores << endl;
    #endif

    // Display de datos
    cout << "Distancia total de la carrera: " << intMetros << " metros" << endl;
    cout << "Cantidad de competidores: " << intAutos << endl;
    cout << "=============================================" << endl;
    // Crear arreglos
    thread hebras[intAutos];
    varAuto competidoresHebra[intAutos];
    // Logica de cada hebra
    for (int i = 0; i < intAutos; i++) {
        // Entregar indice del auto a la funcion
        competidoresHebra[i].intIndice = i + 1;
        // Llamada a funcion
        hebras[i] = thread(funAvance, ref(competidoresHebra[i]), intMetros);
    }
    // Join de hebras
    for (int i = 0; i < intAutos; i++){
        hebras[i].join();
    }

    // Display de tabla de posiciones
    cout << endl << endl << "Lugar\tAuto" << endl << "=================" << endl;
    for (int i = 0; i < intAutos; i++){
        cout << i + 1 << "\tAuto " << arrPosiciones[i] << endl;
    }
    cout << endl;
    return 0;
}