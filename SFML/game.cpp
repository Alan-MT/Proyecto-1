#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

struct Cancion {
    string nombre;
    Cancion* siguiente;
    Cancion* anterior;
};

//void reproducirCancion(Cancion* cancion);
void reproducciones();
Cancion* primerNodo = NULL;
Cancion* ultimoNodo = NULL;
Cancion* nodoActual = NULL;
Music musica;

void agregarCancion(string nombreCancion) {
    Cancion* nuevaCancion = new Cancion{nombreCancion, NULL, NULL};
    if (ultimoNodo) {
        ultimoNodo->siguiente = nuevaCancion;
        nuevaCancion->anterior = ultimoNodo;
        ultimoNodo = nuevaCancion;
    } else {
        primerNodo = nuevaCancion;
        ultimoNodo = nuevaCancion;
    }
}

void reproducirCancion(Cancion* cancion) {
    if (musica.openFromFile(cancion->nombre)) {
        musica.play();
        reproducciones();
        while (musica.getStatus() == Music::Playing) {
            // Espera a que termine la canci�n
        }
    }
}
void pausarCancion(){
	Music music;
	sleep(seconds(2));
    music.pause();
}
void reproducirPlaylist() {
	
	nodoActual = primerNodo;
    while (nodoActual) {
        reproducirCancion(nodoActual);
        nodoActual = nodoActual->siguiente;
    }
}

void siguienteCancion() {
	musica.pause();
	//pausarCancion();
    if (nodoActual->siguiente) {
        nodoActual = nodoActual->siguiente;
        reproducirCancion(nodoActual);
    }
}

void anteriorCancion() {
	musica.pause();
    if (nodoActual->anterior) {
        nodoActual = nodoActual->anterior;
        reproducirCancion(nodoActual);
    }
}
void reproducciones(){
	agregarCancion("cancion1.ogg");
    agregarCancion("cancion2.ogg");
    agregarCancion("cancion3.ogg");
    nodoActual = primerNodo;
    //reproducirCancion(nodoActual);
    
    char opcion;
    do {
        cout << "Opciones:\n";
        cout << "n: siguiente\n";
        cout << "p: anterior\n";
        cout << "k: reproducir";
        cout << "q: salir\n";
        cin >> opcion;
        switch (opcion) {
            case 'n':
                siguienteCancion();
                break;
            case 'p':
                anteriorCancion();
                break;
            case 'k':
               reproducirCancion(nodoActual);
                break;
            case 'i':
			//	pausarCancion(nodoActual);
            	break;
            default:
            	
                break;
        }
    } while (opcion != 'q');
  
}
int main() {
	reproducciones();
  return 0;
}



