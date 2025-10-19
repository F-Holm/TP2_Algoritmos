#include <fstream>

using namespace std;

typedef char str9[10];
typedef str9 tNroVuelo;

bool LeerLinea(ifstream &Aerop, tNroVuelo &consulta);
void EscribirBloque(ofstream &Aerop, tNroVuelo consulta);

int main() {
  ifstream ConsltTxt("datos/Consultas.Txt");
  ofstream ConsltDat("Consultas.Dat", ios::binary | ios::out);
  str9 consulta;

  while (LeerLinea(ConsltTxt, consulta))
    EscribirBloque(ConsltDat, consulta);

  ConsltTxt.close();
  ConsltDat.close();
  return 0;
}

bool LeerLinea(ifstream &Conslt, tNroVuelo &consulta) {
  Conslt.get(consulta, 10);
  Conslt.ignore(2, '\n');
  return Conslt.good();
}  // LeerLinea

void EscribirBloque(ofstream &Conslt, tNroVuelo consulta) {
  Conslt.write(consulta, sizeof(tNroVuelo));
}  // EscribirBloque