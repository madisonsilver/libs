#include <map>
#include <iostream>

class memMap{
  std::map<char*, char>* data;
  public:
  memMap(){
    this->data=new std::map<char*, char>;
  }

  ~memMap(){
    delete this->data;
  }

  template <typename T>
  T read(T* x){
    T* outpntr = (T*) malloc(sizeof(T));
    for (int i=0;i<sizeof(T);i++){
        char info=(*data)[((char*)x)+i];
        *(((char*)outpntr) + i)=info;
    }
    T outv=*outpntr;
    free(outpntr);
    return outv;
  }

  template <typename T>
  void write(T* x, T y){
    for (int i=0;i<sizeof(T);i++){
        (*data)[((char*)x)+i]=*(((char*)&y) + i);
    }
  }

  template <typename T>
  void forget(T* x){
    for (int i=0;i<sizeof(T);i++){
      data->erase(((char*)x)+i);
    }
  }
};

int main(){
  memMap test;
  test.write((int*)0,5);
  std::cout<<test.read((int*)0);
}
