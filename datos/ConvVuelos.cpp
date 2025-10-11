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

bool LeerLinea(ifstream &Vuelos, sVue &rVue);
void EscribirBloque(ofstream &Vuelos, sVue rVue);

int main() {
  ifstream VuelosTxt("datos/Vuelos.Txt");
  ofstream VuelosDat("Vuelos.Dat");
  sVue rVue;
  while (LeerLinea(VuelosTxt, rVue))
    EscribirBloque(VuelosDat, rVue);
  VuelosTxt.close();
  VuelosDat.close();
  return 0;
}

bool LeerLinea(ifstream &Vuelos, sVue &rVue) {
}  // LeerLinea

void EscribirBloque(ofstream &Vuelos, sVue rVue) {
}  // EscribirBloque