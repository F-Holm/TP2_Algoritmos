#include <fstream>
#include <iostream>

using namespace std;

typedef char str8[9];
typedef char str9[10];
typedef char str11[12];

struct sVue {
  str9 numVuelo;
  short distKm;      // 4 digitos
  short velCrucero;  // 4 digitos
  short cantPsj;
  str8 empresa;
  str11 marcaAeronv;
  int fechaSale;   // aaaammdd
  short horaSale;  // hhmm
};  // Sin orden - ? registros

int main() {
  cout << "Hola" << endl;
  return 0;
}