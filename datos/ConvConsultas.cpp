#include <fstream>
#include <iostream>

using namespace std;

typedef char str9[10];

bool LeerLinea(ifstream &Aerop, str9 &consulta);
void EscribirBloque(ofstream &Aerop, str9 consulta);

int main() {
  ifstream AeropTxt("datos/Consultas.Txt");
  ofstream AeropDat("Consultas.Dat");
  str9 consulta;
  while (LeerLinea(AeropTxt, consulta))
    EscribirBloque(AeropDat, consulta);
  AeropTxt.close();
  AeropDat.close();
  return 0;
}

bool LeerLinea(ifstream &Aerop, str9 &consulta) {
}  // LeerLinea

void EscribirBloque(ofstream &Aerop, str9 consulta) {
}  // EscribirBloque