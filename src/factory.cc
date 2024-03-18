#include "nif.h"

  bool tsCheck, bsCheck = false;
  bool typeCheck = false;
  aux = 0;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-ts") == 0 && i + 1 < argc) {
      aux = std::stoi(argv[i + 1]);
      if (aux > 0) {
        //
      } else {
        throw ParsingException();
      }
    } else if (strcmp(argv[i], "-fd") == 0 && i + 1 < argc) {
      char* fdType = argv[++i];
      if (strcmp(fdType, "modulo") == 0) {
        fd = new fdModulo<Nif, Container>(aux);
        typeCheck = true;
      } else if (strcmp(fdType, "random") == 0) {
        fd = new fdrandom<int, Container>(aux);
        typeCheck = true;
      } else if (strcmp(fdType, "suma") == 0) {
        new fdSuma<int, Container>(aux);
        typeCheck = true;
      } 

    } else if (strcmp(argv[i], "-fe") == 0 && i + 1 < argc) {
      ExplorationFunction<int>* fe;
      DispersionFunction<int>* fdp;
      char* feType = argv[++i];
      if (strcmp(feType, "lineal") == 0) {
        fe = new feLineal<int>;
      } else if (strcmp(feType, "cuadratica") == 0) {
        fe = new feCuadratica<int>;
      } else if (strcmp(feType, "doble_dispersion") == 0) {
        fe = new feDobleDispersion<int>(fd);
      } else if (strcmp(feType, "random") == 0) {
        fdp = new fdrandom<int> (tamano);
        fe = new feRedispersion<int>(fdp);
      }
    }
  }

  return lattice;