#include "../include/tabla_hash.h"

template <class Key, class Container>
Tabla_hash_t<Key, Container>::Tabla_hash_t(unsigned tableSize,
                                unsigned blockSize,
                                DispersionFunction<Key>* fd,
                                ExplorationFunction<Key>* fe){
  tableSize_ = tableSize;
  fd_ = fd;
  blockSize_ = blockSize;
  
  table_.resize(tableSize);

  if (fe == nullptr) {
    for (int i = 0; i < tableSize_; ++i){
      table_[i] = new List<Key>;
      table_[i]->Resize(1);
    }
  } else {
    fe_ = fe;
    for (int i = 0; i < tableSize_; ++i){
      table_[i] = new Block<Key>;
      table_[i]->Resize(blockSize);
    }
  }
}

template <class Key, class Container>
Tabla_hash_t<Key, Container>::~Tabla_hash_t(void){
  delete fd_;
  delete fe_;
}

template <class Key, class Container>
bool Tabla_hash_t<Key, Container>::Buscar(Key& X){

  bool encontrado = false;
  unsigned iter = 1;
  do{
    if(table_[fd_->operator()(X)]->Buscarc(X)){
      encontrado = true;
      sumar_intento();
    }else if(table_[fd_->operator()(X)]->EstaLleno()){
      encontrado = table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_]->Buscarc(X);
    }
    iter++;
    sumar_intento();
  }while(iter <= tableSize_ && !encontrado);

  return encontrado;
}

template <class Key, class Container>
bool Tabla_hash_t<Key, Container>::Insertar(Key& X){

  bool success = false;
  unsigned iter = 1;
  if(!Buscar(X) && !table_[fd_->operator()(X)]->EstaLleno()){
    success = table_[fd_->operator()(X)]->Insertarc(X);
    sumar_intento();
  }else if(table_[fd_->operator()(X)]->EstaLleno()){
    do{
      if(!table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_]->EstaLleno()){
        success = table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_]->Insertarc(X);
      } 
      iter++;
      sumar_intento();
    }while(iter <= tableSize_ && !success);
  }

  return success;
}

template <class Key, class Container>
void Tabla_hash_t<Key, Container>::showTabla(void){
  for (int i = 0; i < tableSize_; ++i){
    std::cout << "[" << i << "]: ";
    table_[i]->print();
    std::cout << std::endl;
  }
}

template <class Key, class Container>
void Tabla_hash_t<Key, Container>::change_fe(ExplorationFunction<Key>* newfe){
  delete fe_;
  fe_ = newfe;
  intentos_ = 0;
}

template <class Key, class Container>
int Tabla_hash_t<Key, Container>::get_intentos(void){
  return intentos_;
}

template <class Key, class Container>
void Tabla_hash_t<Key, Container>::sumar_intento(void){
  intentos_++;
}
