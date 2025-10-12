#include <fstream>
#include <iostream>

using namespace std;

typedef char str9[10];
typedef str9 tNumVuelo;

bool LeerLinea(ifstream &Aerop, tNumVuelo &consulta);
void EscribirBloque(ofstream &Aerop, tNumVuelo consulta);

int main() {
  ifstream ConsltTxt("datos/Consultas.Txt");
  ofstream ConsltDat("Consultas.Dat");
  str9 consulta;
  while (LeerLinea(ConsltTxt, consulta))
    EscribirBloque(ConsltDat, consulta);
  ConsltTxt.close();
  ConsltDat.close();
  return 0;
}

bool LeerLinea(ifstream &Conslt, tNumVuelo &consulta) {
  Conslt.get(consulta, 9);
  Conslt.ignore('\n');
  return Conslt.good();
}  // LeerLinea

void EscribirBloque(ofstream &Conslt, tNumVuelo consulta) {
  Conslt.write(consulta, 9);
}  // EscribirBloque