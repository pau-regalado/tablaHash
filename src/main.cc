#include <iostream>
#include <array>

#include "../include/tabla_hash.h"
#include "../include/sequence.h"
#include "../include/staticSquence.h"
#include "../include/dinamicSquence.h"
#include "../include/dispersionFunction.h"
#include "../include/explorationFunction.h"

template <class Key>
void probar_tabla(Tabla_hash_t<Key>* t){
  Key n;
  for (int i = 0; i < 20; ++i ){
    n = std::rand();
    t->Insertar(n);
  }
} 

void showmenu(void){
  std::cout << "i) Insertar elemento" << std::endl;
  std::cout << "b) Buscar elemento" << std::endl;
  std::cout << "m) mostrar tabla" << std::endl;
  std::cout << "l) Esta lleno?" << std::endl;
  std::cout << "q) Salir" << std::endl;
  std::cout << "Introduzca una opcion: ";
}

void pedir_exp(char& op){
  std::cout << "Tipo de funcion de exploracion? " << std::endl;
  std::cout << "l) lineal " << std::endl;
  std::cout << "c) cuadratica " << std::endl;
  std::cout << "d) doble dispersion " << std::endl;
  std::cout << "r) redispersion " << std::endl;
  std::cout << "s) sin exploracion (disp. abierta) " << std::endl;

  std::cout << "Introduzca una opcion: ";
  std::cin >> op;
  std::cout << std::endl;
}


int main (int argc, char* argv[]){

  int tamano, tamcelda;
  char tipo;

// ---------------------- PIDE F DISPERSION ---------------

  std::cout << "Bienvenido, introduzca el tamaño de la tabla:" << std::endl;
  std::cout << "Tamaño de la tabla: ";
  std::cin >> tamano;

  std::cout << "Tamaño de la celda: ";
  std::cin >> tamcelda;

  std::cout << std::endl;

  std::cout << "Tipo de funcion de dispersion? " << std::endl;
  std::cout << "m) modulo " << std::endl;
  std::cout << "s) suma " << std::endl;
  std::cout << "r) random " << std::endl;
  std::cout << "Introduzca una opcion: ";
  std::cin >> tipo;
  std::cout << std::endl;

  DispersionFunction<int>* fd;

  switch (tipo){
    case 'm': fd = new fdModulo<int>(tamano);
      break;
    case 'r': fd = new fdrandom<int>(tamano);
      break;
    case 's': fd = new fdSuma<int>(tamano);
      break;
    default:
     std::cout << "Error" << std::endl;
  }

// ---------------------- PIDE F EXPLORACION ---------------

    ExplorationFunction<int>* fe;
    DispersionFunction<int>* fdp;
    pedir_exp(tipo);

    switch (tipo){
      case 'l': fe = new feLineal<int>;
        break;
      case 'c': fe = new feCuadratica<int>;
        break;
      case 'd': fe = new feDobleDispersion<int>(fd);
        break;
      case 'r': 
        fdp = new fdrandom<int> (tamano);
        fe = new feRedispersion<int>(fdp);
        break;
      case 's': fe = nullptr;
        break;
      default: 
        std::cout << "Error" << std::endl;
    }

  // ---------------------- CREA TABLA ---------------

    Tabla_hash_t<int> tabla(tamano,tamcelda,fd, fe);

    bool quit = false;
    while(!quit){

      showmenu();
      std::cin >> tipo;
      std::cout << std::endl;
      switch (tipo){
        case 'i':
          std::cout << "Numero a insertar: ";
          std::cin >> tamano;
          std::cout << "insertando " << tamano << " ..." << std::endl;
          if (tabla.Insertar(tamano)){
            std::cout << "Se almaceno " << tamano << " correctamente" << std::endl;
          }else{
            std::cout << "No se pudo insertar. " << tamano << std::endl;
          }
          break;
        
        case 'b': 
          std::cout << "Numero a buscar: ";
          std::cin >> tamano;
          if (tabla.Buscar(tamano)){
            std::cout << tamano << " esta almacenado" << std::endl;
          }else{
            std::cout << tamano << " no esta almacenado" << std::endl;
          }
          break;

        case 'm': 
          tabla.showTabla();
          break;

        case 'l': 

          /*std::cout << "fila vacia?: ";
          std::cin >> tamano;
          if (tabla.get_v()[tamano]->isFull()){
            std::cout << "Esta llena" << std::endl;
          }else{
            std::cout << "No esta llena" << std::endl;
          }*/
          break;

        case 'q':
          std::cout << "Adios" << std::endl;
          quit = true;
          break;

        default: std::cout << "Error. Vuelva a introducir la opcion" << std::endl;
      }
    }
 
  return 0;
}