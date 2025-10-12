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
  Vuelos.get(rVue.numVuelo, 10);
  Vuelos >> rVue.distKm >> rVue.velCrucero >> rVue.cantPsj;
  Vuelos.ignore();
  Vuelos.get(rVue.empresa, 9);
  Vuelos.ignore();
  Vuelos.get(rVue.marcaAeronv, 12);
  Vuelos >> rVue.fechaSale >> rVue.horaSale;
  Vuelos.ignore('\n');
  return Vuelos.good();
}  // LeerLinea

void EscribirBloque(ofstream &Vuelos, sVue rVue) {
  Vuelos.write(rVue.numVuelo, 9);
  Vuelos.write((const char *)&rVue.distKm, sizeof(rVue.distKm));
  Vuelos.write((const char *)&rVue.velCrucero, sizeof(rVue.velCrucero));
  Vuelos.write((const char *)&rVue.cantPsj, sizeof(rVue.cantPsj));
  Vuelos.write(rVue.empresa, 8);
  Vuelos.write(rVue.marcaAeronv, 11);
  Vuelos.write((const char *)&rVue.fechaSale, sizeof(rVue.fechaSale));
  Vuelos.write((const char *)&rVue.horaSale, sizeof(rVue.horaSale));
}  // EscribirBloque