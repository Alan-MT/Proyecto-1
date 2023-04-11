#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Cancion{
    string titulo;
    string path;
    int ID;
    Cancion *siguiente; // Puntero al siguiente nodo
};

struct ListaReproduccion{
    int indice;
    string nombre;
    string descripcion;
    Cancion *primera;
    ListaReproduccion *siguiente;// puntero
};

// VOID
void imprimirCanciones(Cancion *cabeza);
void agregarCancion(Cancion *&cabeza, string titulo, string pat, int id);
void eliminarCancion(Cancion *&cabeza, int id);
void crearLista(ListaReproduccion *&listado, string nombre, string descripcion, Cancion *primero);
void cancionesLista(ListaReproduccion *listaRepro, Cancion *lista);
void imprimirLista(ListaReproduccion *lista);
void eliminarLista(ListaReproduccion *&listad);
void listadosRepro(ListaReproduccion listad);
void actualizarDatos(ListaReproduccion *listado);
void agregarCancioneAlista(ListaReproduccion *cambio, Cancion *lista, int indicador);
void eliminarCancionLista(ListaReproduccion *listaRepro);

//void menuOperaCancion(Cancion *Cabeza);
// TIPO
string path();
int identificador(Cancion *cabeza, int inicio);
// TIPO CANCION
Cancion *buscarCancion(Cancion *cabeza, string nac);
Cancion *menuOperaCancion(Cancion *cabeza);
// TIPO LISTA REPRODUCCION
ListaReproduccion *menuOperaPlaylist(ListaReproduccion *&listados, Cancion *listadoCanciones);




void menuPrincipal(Cancion *cabeza, ListaReproduccion *listados)
{
    Cancion *listadosCanciones = cabeza; 

    int opcion;
    do
    {

        cout << " __________________________________\n";
        cout << "|       REPRODUCTOR DE MUSICA      |\n";
        cout << "|  -------  MUSIC-PLAYER --------  |\n";
        cout << "|1. Operaciones de canciones       | \n";
        cout << "|2. Operaciones de Playlist        |\n";
        cout << "|3. Reproduccion                   | \n";
        cout << "|4. Carga Masiva de canciones      | \n";
        cout << "|5. SALIR                          |\n";
        cout << "|Digite la opciones que desee hacer|\n";
        cout << " __________________________________\n ->";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            listadosCanciones = menuOperaCancion(listadosCanciones);
            break;
        case 2:
            listados = menuOperaPlaylist(listados, listadosCanciones);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            cout << "Hasta pronto\n";
            break;
        default:
            cout << "Esa opcion no esta dentro del sistema";
            break;
        }
    } while (opcion != 5);
}
Cancion *menuOperaCancion(Cancion *cabeza)
{

    int contador = 1;
    string nac;
    Cancion *cancion;
    Cancion nueva;
    int numero;
    do
    {

        cout << "\n __________________________________\n";
        cout << "|      OPERACION DE CANCIONES      |\n";
        cout << "|  -------  MUSIC-PLAYER --------  |\n";
        cout << "|1. INSERTAR                       | \n";
        cout << "|2. ELIMINAR                       |\n";
        cout << "|3. BUSCAR NOMBRE                  | \n";
        cout << "|4. LISTAR CANCIONES               | \n";
        cout << "|5. REGRESAR                       |\n";
        cout << "|Digite la opciones que desee hacer|\n";
        cout << " __________________________________\n ->";
        cin >> numero;
        string titulo;
        string pat;
        switch (numero)
        {
        case 1:
            cout << "Ingrese el titulo de la cancion que desea agregar: ";
            cin >> titulo;
            pat = path();
            agregarCancion(cabeza, titulo, pat, contador);
            break;
        case 2:
            cout << "Quieres eliminar la cancion atravez de: \n";
            cout << "1: ID \n 2: Titulo\n";
            cin >> numero;
            eliminarCancion(cabeza, numero);
            break;
        case 3:
            cout << "Ingrese el titulo de la cancion que desea buscar: ";
            cin >> nac;
            cancion = buscarCancion(cabeza, nac);
            if (cancion != NULL)
            {
            cout << "TITULO: " << cancion->titulo << "  PATH: " << cancion->path << "  ID: " << cancion->ID << endl;
            }
            else
            {
                cout << "La cancion " << nac << " no fue encontrada." << endl;
            }
            break;
        case 4:
            imprimirCanciones(cabeza);
            break;
        case 5:
            cout << "CARGANDO\n";
            break;
        default:
            cout << "Esa opcion no esta dentro del sistema";
            break;
        }
    } while (numero != 5);
    return cabeza;
}

void agregarCancion(Cancion *&cabeza, string titulo, string path, int ID)
{

    if (!titulo.empty())
    {
        Cancion *nuevaCancion = new Cancion;
        nuevaCancion->titulo = titulo;
        nuevaCancion->path = path;
        nuevaCancion->ID = ID;
        nuevaCancion->siguiente = NULL;
        if (cabeza == NULL)
        {
            cabeza = nuevaCancion;
            cout << "Cancion Agregada";
        }
        else
        {
            Cancion *actual = cabeza;
            while (actual->siguiente != NULL)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevaCancion;
            cout << "Cancion Agregada";
        }
    }
    else
    {
        cout << "DEBES INGRESAR EL TITULO";
    }
}

void eliminarCancion(Cancion *&primero, int numero)
{
    Cancion *nodoActual = primero;
    Cancion *nodoAnterior = NULL;
    string titulo;
    if (numero == 1)
    {
        cout << "Ingrese el ID de la cancion que desea eliminar: ";
        cin >> numero;
        while (nodoActual != NULL && nodoActual->ID != numero)
        {
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
        }
    }
    else if (numero == 2)
    {
        cout << "Ingrese el titulo de la cancion que desea eliminar: ";
        cin >> titulo;
        while (nodoActual != NULL && nodoActual->titulo != titulo)
        {
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
        }
    }

    int opcion;
    cout << "Esta seguro que deseas borrar la cancion\n";
    cout << "ID " << nodoActual->ID << "--" << nodoActual->titulo << "|\n";
    cout << "1. SI \n2.NO\n";
    cin >> opcion;
    if (opcion == 1)
    {
        if (nodoActual == NULL)
        {
            cout << "La canción no se encuentra en la lista" << endl;
            return;
        }

        if (nodoAnterior == NULL)
        {
            primero = nodoActual->siguiente;
        }
        else
        {
            nodoAnterior->siguiente = nodoActual->siguiente;
        }
        delete nodoActual;
        cout << "Canción eliminada de la lista" << endl;
    }
}

void imprimirCanciones(Cancion *cabeza)
{
    int contador = 0;
    if (cabeza == NULL)
    {
        cout << "La lista de canciones esta vacia." << endl;
    }
    else
    {
        cout << "Lista de canciones:" << endl;
        Cancion *actual = cabeza;
        while (actual != NULL)
        {
            contador++;
            actual->ID = contador;
            cout << "TITULO: " << actual->titulo << "  PATH: " << actual->path << "  ID: " << actual->ID << endl;
            actual = actual->siguiente;
        }
    }
}

Cancion *buscarCancion(Cancion *cabeza, string titulo)
{
    Cancion *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->titulo == titulo)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}
Cancion *buscarCancionlista(Cancion *primero, int id) {
    Cancion *actual = primero;
    while (actual != NULL && actual->ID != id) {
        actual = actual->siguiente;
    }
    return actual;
}

string path()
{
    string resultado;
    int numeroAleatorio;
    char letraAleatoria;
    // Inicializar la semilla para generar números aleatorios
    srand(time(NULL));
    // Generar un número aleatorio entre 0 y 9
    numeroAleatorio = rand() % 10;
    // Convertir el número en un carácter ASCII correspondiente
    letraAleatoria = static_cast<char>(numeroAleatorio + '0');
    // Agregar el carácter al resultado
    resultado += letraAleatoria;
    letraAleatoria = static_cast<char>(rand() % 26 + 'A'); // Generar una letra aleatoria entre A y Z
    resultado += letraAleatoria;                           // Agregar la letra al resultado
    return resultado;
}
ListaReproduccion *menuOperaPlaylist(ListaReproduccion *&ListaReproducciones, Cancion *storeSong){

    int numero;

    do
    {

        cout << " __________________________________\n";
        cout << "|      OPERACION DE PLAYLIST       |\n";
        cout << "|  -------  MUSIC-PLAYER --------  |\n";
        cout << "|1. CREAR                          | \n";
        cout << "|2. ELIMINAR                       |\n";
        cout << "|3. ACTUALIZAR                     | \n";
        cout << "|4. LISTAR                         | \n";
        cout << "|5. AGREGAR CANCIONES              |\n";
        cout << "|6. ELIMINAR CANCIONES             |\n";
        cout << "|7. REGRESAR                       |\n";
        cout << "|Digite la opciones que desee hacer|\n";
        cout << " __________________________________\n ->";
        cin >> numero;
        
        string nombre;
        string descripcion;
        switch (numero)
        {
        case 1:
            cout << "Ingrese el nombre de la lista-\n";
            cin >> nombre;
            cout << "Ingrese la descripcion de a lista\n";
            cin >> descripcion;
            crearLista(ListaReproducciones,nombre, descripcion,storeSong);
            break;
        case 2:
            eliminarLista(ListaReproducciones);
            break;
        case 3:
            actualizarDatos(ListaReproducciones);
            break;
        case 4:
        imprimirLista(ListaReproducciones);
            break;
        case 5:
            agregarCancioneAlista(ListaReproducciones, storeSong,1);
            break;
        case 6:
            eliminarCancionLista(ListaReproducciones);
            break;
        case 7:
            cout << "CARGANDO\n";
            break;
        default:
            cout << "Esa opcion no esta dentro del sistema";
            break;
        }
    } while (numero != 7);

    return ListaReproducciones;
}
void crearLista(ListaReproduccion *&listado, string nombre, string descripcion, Cancion *primero) {
    ListaReproduccion *nuevaLista = new ListaReproduccion;

    nuevaLista->nombre = nombre;
    nuevaLista->descripcion = descripcion;
    nuevaLista->siguiente = NULL;
    nuevaLista->primera = NULL;

    if (listado == NULL){
        listado = nuevaLista;
    }else{
        ListaReproduccion *actual = listado;
        while (actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevaLista;
    }

    int op=0;
    cout << "Deseas ingresar las canciones en este momento o mas tarde?" << endl;
    cout << "1. SI" << endl;
    cout << "2. NO" << endl;
    cin >> op;

    if (op == 1) {
        cancionesLista(nuevaLista,primero);
    }
}


void cancionesLista(ListaReproduccion *listaRepro, Cancion *lista){

    ListaReproduccion *cambio = listaRepro;
    // Verificar si la lista de reproducción está vacía
    if (cambio == NULL){
        cout << "La lista de reproduccion esta vacia." << endl;
        return;
    }
    agregarCancioneAlista(cambio, lista, 3);

}
void eleccionLista(ListaReproduccion *nodoActual, ListaReproduccion *nodoAnterior, int indice){
        while (nodoActual != NULL && nodoActual->indice != indice){
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
        }
    
        if (nodoActual == NULL)
        {
            cout << "La playlist no se encuentra en la lista" << endl;
            return;
        }
}
// función para imprimir una lista de reproducción
void imprimirLista(ListaReproduccion *lista) {
    int contador = 0;

    if (lista == NULL)
    {
        cout << "La lista de Reproduccion esta vacia." << endl;
    }
    else
    {
        cout << "Lista de Reproduccion:" << endl;
        ListaReproduccion *actual = lista;
        while (actual != NULL)
        {
            contador++;
            actual->indice = contador;
            cout << actual->indice <<"-"<< actual->nombre << ": " << actual->descripcion << endl;
            imprimirCanciones(actual->primera);
            actual = actual->siguiente;
            
        }
        
    }

}

// función para eliminar una lista de reproducción
void eliminarLista(ListaReproduccion *&lista) {
    ListaReproduccion *nodoActual = lista;
    ListaReproduccion *nodoAnterior = NULL;
    int indice;
    cout << "Ingrese el ID de la playlist: ";
    cin >> indice;
    eleccionLista(nodoActual, nodoAnterior, indice);
    if (nodoAnterior == NULL)
    {
        lista = nodoActual->siguiente;
    }
        else
        {
            nodoAnterior->siguiente = nodoActual->siguiente;
        }
        delete nodoActual;
        cout << "la lista fue eliminada eliminada de la lista" << endl;
    
}
void actualizarDatos(ListaReproduccion *listado){
        ListaReproduccion *nodoActual = listado;
        ListaReproduccion *nodoAnterior = NULL;
        string nombre;
        string descrip;
        int indice;
        cout << "Ingrese el ID de la playlist: ";
        cin >> indice;
        eleccionLista(nodoActual, nodoAnterior, indice);
        
        cout << "Ingresa el nuevo nombre de la lista"<<endl;
        cin >> nombre;
        cout << "Ingresa la nueva descripion"<<endl;
        cin >> descrip;
        if (!nombre.empty()){
            nodoActual->nombre = nombre;
        } 
        if (!descrip.empty()){
            nodoActual->descripcion = descrip;
        }
}

void agregarCancioneAlista(ListaReproduccion *listaRepro, Cancion *lista, int indicador){
        ListaReproduccion *nodoActualLista = listaRepro;
        ListaReproduccion *nodoAnteriorLista = NULL;
        int opcion;
        int id = 0;
        if (indicador == 1){
            int indice;
            cout << "Ingrese el ID de la playlist: ";
            cin >> indice;
            eleccionLista(nodoActualLista, nodoAnteriorLista, indice);
        }
        
        // Imprimir la lista de canciones
        cout << "Cuantas canciones quieres agregar?" << endl;
        cin >> opcion;
        for (int i = 0; i < opcion; i++)
        {
            imprimirCanciones(lista);
            cout << "Ingrese el ID de la cancion que desea agregar: ";
            cin >> id;
            Cancion *nodoActual = lista;
            Cancion *nodoAnterior = NULL;

            // Buscar la canción en la lista de canciones
            while (nodoActual != NULL && nodoActual->ID != id)
            {
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
            }

            if (nodoActual == NULL)
            {
            cout << "No se encontro la cancion con ID " << id << endl;
            continue;
            }

            agregarCancion(nodoActualLista->primera, nodoActual->titulo, nodoActual->path, nodoActual->ID);
            cout << "Se agrego la cancion \"" << nodoActual->titulo << "\" a la lista de reproduccion." << endl;
            imprimirCanciones(nodoActualLista->primera);
        }
}
void eliminarCancionLista(ListaReproduccion *listaRepro){
        ListaReproduccion *nodoActualLista = listaRepro;
        ListaReproduccion *nodoAnteriorLista = NULL;
        int id = 0;
        int opcion;
        int indice;
        cout << "Ingrese el ID de la playlist: ";
        cin >> indice;
        eleccionLista(nodoActualLista, nodoAnteriorLista, indice);
        // Imprimir la lista de canciones
        cout << "Cuantas canciones quieres eliminar?" << endl;
        cin >> opcion;
        for (int i = 0; i < opcion; i++)
        {
            eliminarCancion(nodoActualLista->primera,1);
            imprimirCanciones(nodoActualLista->primera);
        }
}
int main()
{
    Cancion *cabeza = NULL;
    ListaReproduccion *listados = NULL;
    agregarCancion(cabeza, "Tarzan boy", "5d4", 1);
    agregarCancion(cabeza, "Camisa Negra", "54df", 1);
    agregarCancion(cabeza, "Wake me up", "15fds", 1);   
    agregarCancion(cabeza, "Castle on the hill", "56ds", 1);
    crearLista(listados,"favoritos","las que mas me gustan",cabeza);
    crearLista(listados, "mi amor","para mi vida",cabeza);
    menuPrincipal(cabeza, listados);

    return 0;
}
