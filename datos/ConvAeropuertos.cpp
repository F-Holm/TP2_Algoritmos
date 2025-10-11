#include <fstream>
#include <iostream>

using namespace std;

typedef char str3[4];
typedef char str4[5];
typedef char str20[21];
typedef char str25[26];
typedef char str30[31];

struct sAerop {
  str20 provin;
  str25 ciudad;
  str30 nomAeropto;
  str4 codOACI;
  str3 codIATA;
};

void LeerLinea(ifstream& Aerop, sAerop& rAerop);
void EscribirBloque(ofstream& Aerop, sAerop rAerop);

int main() {
  ifstream AeropTxt("datos/Aeropuertos.Txt");
  ofstream AeropDat("Aeropuertos.Dat");
  AeropTxt.close();
  AeropDat.close();
  return 0;
}

void LeerLinea(ifstream& Aerop, sAerop& rAerop) {
}  // LeerLinea

void EscribirBloque(ofstream& Aerop, sAerop rAerop) {
}  // EscribirBloque