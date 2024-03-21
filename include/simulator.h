#ifndef __SIMULATOR__ 
#define __SIMULATOR__

#include <iostream>
#include <fstream>
#include <string.h>

#include "nif.h"
#include "tabla_hash.h"

typedef Nif Key;

void showmenu(void){
  std::cout << "i) Insertar elemento" << std::endl;
  std::cout << "b) Buscar elemento" << std::endl;
  std::cout << "m) mostrar tabla" << std::endl;
  std::cout << "l) Esta lleno?" << std::endl;
  std::cout << "q) Salir" << std::endl;
}

template <class Table>
void displayMenu(Table* table) {
  bool quit = false;
  char tipo;
  Key data;
  while(!quit){
    showmenu();
    std::cin >> tipo;
    std::cout << std::endl;
    switch (tipo) {
      case 'i':
        std::cout << "Insert number> ";
        std::cin >> data;
        if (table->Insertar(data)){
          std::cout << "Se almaceno " << data << " correctamente" << std::endl;
        }else{
          std::cout << "No se pudo insertar. " << data << std::endl;
        }
        break;

      case 'b':
        std::cout << "Numero a buscar> ";
        std::cin >> data;
        if (table->Buscar(data)){
          std::cout << data << " esta almacenado" << std::endl;
        }else{
          std::cout << data << " no esta almacenado" << std::endl;
        }
        break;

      case 'm': 
        table->showTabla();
        break;

      case 'q':
        std::cout << "Adios" << std::endl;
        quit = true;
        break;

      default: std::cout << "Error. Vuelva a introducir la opcion" << std::endl;
    }
  }
}

class Simulator {
  public:
    void run(int argc, char* argv[]);
};

void Simulator::run(int argc, char* argv[]) {
  bool tsCheck, bsCheck = false;
  bool fdCheck = false;
  bool feCheck = false;
  int ts, bs;
  bool openTable = true;

  DispersionFunction<Key>* fd;
  ExplorationFunction<Key>* fe;
  DispersionFunction<Key>* fdp;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-ts") == 0 && i + 1 < argc) {
      ts = std::stoi(argv[i + 1]);
      tsCheck = true;
    } else if (strcmp(argv[i], "-fd") == 0 && i + 1 < argc) {
      char* fdType = argv[++i];
      if (strcmp(fdType, "modulo") == 0) {
        fd = new fdModulo<Key>(ts);
        fdCheck = true;
      } else if (strcmp(fdType, "random") == 0) {
        fd = new fdrandom<Key>(ts);
        fdCheck = true;
      } else if (strcmp(fdType, "suma") == 0) {
        fd = new fdSuma<Key>(ts);
        fdCheck = true;
      } else {
        fd = new fdModulo<Key>(ts);
        fdCheck = true;
      }

    } else if (strcmp(argv[i], "-bs") == 0 && i + 1 < argc) {
      bs = std::stoi(argv[i + 1]);
      bsCheck = true;
    } else if (strcmp(argv[i], "-hash") == 0 && i + 1 < argc) {
      char* hashType = argv[++i];
      if (strcmp(hashType, "open") == 0) {      
        openTable = true;
      } else if (strcmp(hashType, "close") == 0) {
        openTable = false;
      }
    } else if (strcmp(argv[i], "-fe") == 0 && i + 1 < argc) {
      char* feType = argv[++i];
      if (strcmp(feType, "lineal") == 0) {
        fe = new feLineal<Key>;
        feCheck = true;
      } else if (strcmp(feType, "cuadratica") == 0) {
        fe = new feCuadratica<Key>;
        feCheck = true;
      } else if (strcmp(feType, "doble_dispersion") == 0) {
        fe = new feDobleDispersion<Key>(fd);
        feCheck = true;
      } else if (strcmp(feType, "random") == 0) {
        fe = new feRedispersion<Key>(fdp);
        feCheck = true;
      }
    }
  }
  
  if (tsCheck && fdCheck && openTable) {
    Tabla_hash_t<Key, DinamicSquence<Key>> table(ts, fd);
    displayMenu<Tabla_hash_t<Key, DinamicSquence<Key>>>(&table);
  } else if (tsCheck && fdCheck && feCheck && bsCheck && !openTable) {
    Tabla_hash_t<Key, StaticSequence<Key>> table(ts, bs, fd, fe);
    displayMenu<Tabla_hash_t<Key, StaticSequence<Key>>>(&table);
  } else {
    Tabla_hash_t<Key> table(10, 3, new fdModulo<Key>(10), new feLineal<Key>);
    displayMenu<Tabla_hash_t<Key, StaticSequence<Key>>>(&table);
  }
}

#endif