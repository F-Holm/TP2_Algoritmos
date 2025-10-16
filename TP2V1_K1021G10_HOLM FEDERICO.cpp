/*
 - Nombre  del  programa: TP2V1_K1021G10_HOLM FEDERICO.cpp
 - fecha  entrega: 03/09/2025
 - Nro. versión: 1
 - Breve comentario del objetivo del programa:
   Este programa gestiona un sistema de ventas de artículos, permitiendo
   registrar artículos, rubros, descripciones y compras. Genera tickets
   de compra y listados de artículos por rubro, aplicando descuentos según
   promociones. Utiliza archivos para almacenar y recuperar datos.


 - Curso: Algoritmos y Estructuras de Datos
 - Comision: K1021
 - Turno: Mañana
 - Docente: Lic. Hugo A. Cuello

 Integrantes (Apellido, Nombre):
    Holm, Federico

 - Nombre del compilador: Borland C++ V.5.5
 */

#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Declaraciones de Structs

struct sAerop;
struct sVue;
struct tInfo;
struct sNodo;
struct sTblAerop;

// Constantes, Macros y Typedef

const short CANT_AEROP = 57;
#define ARCHIVOS ifstream &Aerops, ifstream &Vues, ifstream &Conslts
typedef char str3[4];
typedef char str4[5];
typedef char str8[9];
typedef char str9[10];
typedef char str11[12];
typedef char str20[21];
typedef char str25[26];
typedef char str30[31];
typedef sTblAerop tvrAerop[CANT_AEROP];
typedef struct sNodo *tLista;
typedef unsigned short ushort;

// Definiciones de Structs
struct sAerop {  // Size: 82 B
  str20 provin;
  str25 ciudad;
  str30 nomAeropto;
  str4 codOACI;
  str3 codIATA;
};  // Sin orden - 57 registros

struct sVue {        // Size: 40 B
  str9 nroVuelo;     // IATA-3 - NUM-VUELO-3 - IATA-3
  short distKm;      // 4 digitos
  short velCrucero;  // 4 digitos
  short cantPsj;
  str8 empresa;
  str11 marcaAeronv;
  int fechaSale;   // aaaammdd
  short horaSale;  // hhmm
};  // Sin orden - ? registros

struct tInfo {
  str9 nroVuelo;
  ushort pos;
};

struct sNodo {
  tInfo info;
  tLista sgte;
};

struct sTblAerop {
  str3 codIATA;
  ushort pos;
};  // Ordenado por codIATA - 57 registros

// Declaraciones de Funciones

long GetDate(int &year, int &mes, int &dia, int &ds);
long GetTime(int &hh, int &mm, int &ss);
void Abrir(ARCHIVOS);
void ProcAeropuertos(ifstream &Aerops, tvrAerop &vrAerop);
void ProcVuelos(ifstream &Vues, tLista &lVues);
void ConsultasVuelos(ifstream &Conslts, ifstream &Vues, ifstream &Aerops,
                     tLista &lVues, tvrAerop &vrAerop);
void ListVueAeropSld(ifstream &Aerops, ifstream &Vues, tvrAerop &vrAerop,
                     tLista &lVues);
void Cerrar(ARCHIVOS);
void OrdxBur(tvrAerop &vrAerop);
void IntCmb(sTblAerop &sElem1, sTblAerop &sElem2);
void InsertaNodo(tLista &lista, tInfo valor);
void InsertaInicio(tLista &lista, tInfo valor);
void InsertaEnMedio(tLista &lista, tInfo valor);
void SacarPrimerNodo(tLista &lista);
int BusBinVec(tvrAerop &vrAerop, str3 codIATA);
void FormatoHoraMin(short hora, short &hh, short &mm);
void HoraLlega(short distKm, short velCrucero, short hhSa, short mmSa,
               short &hhVi, short &mmVi, short &hhLl, short &mmLl);
string Replicate(char car, ushort n);
// void SubCad();
// void InsertarEnOrden();
// void VerifEstado();
// void InsertaEnLugar();
// void BuscarClvNodo();
// void SacarPrimerNodo();

// Main

int main() {
  ifstream Aerops, Vues, Conslts;
  tvrAerop vrAerop;
  tLista lVues = NULL;

  Abrir(Aerops, Vues, Conslts);
  ProcAeropuertos(Aerops, vrAerop);
  ProcVuelos(Vues, lVues);
  ConsultasVuelos(Conslts, Vues, Aerops, lVues, vrAerop);
  ListVueAeropSld(Aerops, Vues, vrAerop, lVues);
  Cerrar(Aerops, Vues, Conslts);
  return 0;
}

// Definiciones de funciones

long GetDate(int &year, int &mes, int &dia, int &ds) {
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  year = 1900 + timeinfo->tm_year;
  mes = 1 + timeinfo->tm_mon;
  dia = timeinfo->tm_mday;
  ds = 1 + timeinfo->tm_wday;
  return (1900 + timeinfo->tm_year) * 10000 + (1 + timeinfo->tm_mon) * 100 +
         timeinfo->tm_mday;
}  // GetDate

long GetTime(int &hh, int &mm, int &ss) {
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  hh = timeinfo->tm_hour;
  mm = timeinfo->tm_min;
  ss = timeinfo->tm_sec;
  return timeinfo->tm_hour * 10000 + timeinfo->tm_min * 100 + timeinfo->tm_sec;
}  // GetTime

void Abrir(ARCHIVOS) {
  Aerops.open("Aeropuertos.Dat", ios::binary | ios::in);
  Vues.open("Vuelos.Dat", ios::binary | ios::in);
  Conslts.open("Consultas.Dat", ios::binary | ios::in);
}  // Abrir

void ProcAeropuertos(ifstream &Aerops, tvrAerop &vrAerop) {
  sAerop rAerop;
  ushort i = 0;
  while (Aerops.read((char *)&rAerop, sizeof(rAerop))) {
    strcpy(vrAerop[i].codIATA, rAerop.codIATA);
    vrAerop[i].pos = i;
    i++;
  }
  OrdxBur(vrAerop);
}  // ProcAeropuertos

void ProcVuelos(ifstream &Vues, tLista &lVues) {
  sVue rVue;
  tInfo info;
  ushort i = 0;
  while (Vues.read((char *)&rVue, sizeof(rVue))) {
    strcpy(info.nroVuelo, rVue.nroVuelo);
    info.pos = i;
    i++;
    InsertaNodo(lVues, info);
  }
}  // ProcVuelos

void ConsultasVuelos(ifstream &Conslts, ifstream &Vues, ifstream &Aerops,
                     tLista &lVues, tvrAerop &vrAerop) {
  freopen("Listado Consulta Vuelos.Txt", "w", stdout);
  str9 nroVuelo;
  tLista aux = lVues;
  sVue rVue;

  int anio, mes, dia, ds, hh, mm, ss;
  GetTime(hh, mm, ss);
  GetDate(anio, mes, dia, ds);
  const char *meses[] = {"Enero",      "Febrero", "Marzo",     "Abril",
                         "Mayo",       "Junio",   "Julio",     "Agosto",
                         "Septiembre", "Octubre", "Noviembre", "Diciembre"};
  cout << Replicate(' ', 168 / 2 - 48) << "Consultas de vuelos del " << dia
       << " de " << meses[mes] << " de " << anio
       << "\nNroVuelo Ciudad de origen Nom.Aerop.Orig.  Empresa     Marca     "
          "Ciudad Destino  Nom.Aerop.Dest.      Estado     dia hhAct hhSa  "
          "t.V.  hhLl \n";

  while (Conslts.read(nroVuelo, 9)) {
    if (strcmp(aux->info.nroVuelo, lVues->info.nroVuelo) > 0)
      aux = lVues;
    while (strcmp(aux->info.nroVuelo, lVues->info.nroVuelo) < 0)
      aux = aux->sgte;

    Vues.clear();
    Vues.seekg(aux->info.pos * sizeof(sVue));
    Vues.read((char *)&rVue, sizeof(rVue));

    sAerop origen, destino;
    Aerops.clear();
    Aerops.seekg(BusBinVec(vrAerop, nroVuelo) * sizeof(sAerop));
    Aerops.read((char *)&origen, sizeof(origen));
    Aerops.clear();
    Aerops.seekg(BusBinVec(vrAerop, nroVuelo + 6) * sizeof(sAerop));
    Aerops.read((char *)&destino, sizeof(destino));

    short hhSa, mmSa, hhVi, mmVi, hhLl, mmLl,
        diaSa = rVue.fechaSale - (rVue.fechaSale / 1000000 * 1000000);
    FormatoHoraMin(rVue.horaSale, hhSa, mmSa);
    HoraLlega(rVue.distKm, rVue.velCrucero, hhSa, mmSa, hhVi, mmVi, hhLl, mmLl);

    cout << setw(9) << rVue.nroVuelo << ' ' << setw(16) << origen.ciudad << ' '
         << setw(16) << origen.nomAeropto << ' ' << setw(8) << rVue.empresa
         << ' ' << setw(11) << rVue.marcaAeronv << ' ' << setw(16)
         << destino.ciudad << ' ' << setw(16) << destino.nomAeropto << ' '
         << setw(15) << destino.provin << ' ' << setw(2) << diaSa << ' '
         << setfill('0') << setw(2) << hh << ':' << setw(2) << mm << ' '
         << setw(2) << hhSa << ':' << setw(2) << mmSa << ' ' << setw(2) << hhVi
         << ':' << setw(2) << mmVi << ' ' << setw(2) << hhLl << ':' << setw(2)
         << mmLl << setfill(' ') << '\n';
  }
}  // ConsultasVuelos

void ListVueAeropSld(ifstream &Aerops, ifstream &Vues, tvrAerop &vrAerop,
                     tLista &lVues) {
  int anio, mes, dia, ds, hh, mm, ss;
  GetTime(hh, mm, ss);
  GetDate(anio, mes, dia, ds);

  sAerop rAerop;
  sVue rVue;
  sAerop aeropDest;

  cout << '\n'
       << Replicate('=', 200) << "\n\n"
       << Replicate(' ', 0)
       << "Listado Salidas Aerop. Origen a otros Aerop. Llegada, del dia "
       << dia << "\n";

  for (ushort i = 0; i < CANT_AEROP; i++) {
    Aerops.clear();
    Aerops.seekg(i * sizeof(sAerop));
    Aerops.read((char *)&rAerop, sizeof(rAerop));

    cout << "\nAerop. origen: " << rAerop.codIATA << "  " << rAerop.nomAeropto
         << "  Ciudad: " << rAerop.ciudad << "\n";
    cout << "NroVue.   Empresa   Marca        Ciu.Dest.       Nom.Aerop.Dest.  "
            " Estado   dia  hhAct  hhSa  t.V.  hhLl\n";

    while (lVues && strncmp(lVues->info.nroVuelo, rAerop.codIATA, 3) == 0) {
      Vues.clear();
      Vues.seekg(lVues->info.pos * sizeof(rVue));
      Vues.read((char *)&rVue, sizeof(rVue));

      str3 codDest;
      strncpy(codDest, rVue.nroVuelo + 6, 3);
      codDest[3] = '\0';

      Aerops.clear();
      Aerops.seekg(BusBinVec(vrAerop, codDest) * sizeof(sAerop));
      Aerops.read((char *)&aeropDest, sizeof(sAerop));

      short hhSa, mmSa, hhVi, mmVi, hhLl, mmLl,
          diaSa = rVue.fechaSale - (rVue.fechaSale / 1000000 * 1000000);
      FormatoHoraMin(rVue.horaSale, hhSa, mmSa);
      HoraLlega(rVue.distKm, rVue.velCrucero, hhSa, mmSa, hhVi, mmVi, hhLl,
                mmLl);

      cout << setw(9) << rVue.nroVuelo << ' ' << setw(8) << rVue.empresa << ' '
           << setw(11) << rVue.marcaAeronv << ' ' << setw(16)
           << aeropDest.ciudad << ' ' << setw(16) << aeropDest.nomAeropto << ' '
           << setw(15) << aeropDest.provin << ' ' << setw(2) << diaSa << ' '
           << setw(2) << setfill('0') << hh << ':' << setw(2) << mm << "   "
           << setw(2) << hhSa << ':' << setw(2) << mmSa << "   " << setw(2)
           << hhVi << ':' << setw(2) << mmVi << "   " << setw(2) << hhLl << ':'
           << setw(2) << mmLl << setfill(' ') << '\n';

      SacarPrimerNodo(lVues);
    }
  }
  fclose(stdout);
}  // ListVueAeropSld

void Cerrar(ARCHIVOS) {
  Aerops.close();
  Vues.close();
  Conslts.close();
}  // Cerrar

void OrdxBur(tvrAerop &vrAerop) {
  bool hayCambios;
  ushort k = 0;

  do {
    hayCambios = false;
    k++;

    for (ushort i = 0; i < CANT_AEROP - k; i++) {
      if (strcmp(vrAerop[i].codIATA, vrAerop[i + 1].codIATA) > 0) {
        IntCmb(vrAerop[i], vrAerop[i + 1]);
        hayCambios = true;
      }
    }
  } while (hayCambios);
}  // OrdxBur

void IntCmb(sTblAerop &sElem1, sTblAerop &sElem2) {
  sTblAerop auxiliar = sElem1;
  sElem1 = sElem2;
  sElem2 = auxiliar;
}  // IntCmb

void InsertaNodo(tLista &lista, tInfo valor) {
  if (lista || strcmp(valor.nroVuelo, lista->info.nroVuelo) < 0)
    InsertaInicio(lista, valor);
  else
    InsertaEnMedio(lista, valor);
}  // InsertaNodo

void InsertaInicio(tLista &lista, tInfo valor) {
  tLista nodo = new sNodo;
  nodo->info = valor;
  nodo->sgte = lista;
  lista = nodo;
}  // InsertaInicio

void InsertaEnMedio(tLista &lista, tInfo valor) {
  tLista nodo = new sNodo;
  nodo->info = valor;

  tLista aux = lista;

  while (aux->sgte != NULL &&
         strcmp(aux->sgte->info.nroVuelo, valor.nroVuelo) < 0)
    aux = aux->sgte;

  nodo->sgte = aux->sgte;
  aux->sgte = nodo;
}  // InsertaEnMedio

void SacarPrimerNodo(tLista &lista) {
  if (lista != NULL) {
    tLista nodo = lista;
    lista = lista->sgte;
    delete nodo;
  }
}  // SacarPrimerNodo

int BusBinVec(tvrAerop &vrAerop, str3 codIATA) {
  int li = 0, ls = CANT_AEROP, pm;

  while (li <= ls) {
    pm = (li + ls) / 2;

    int cmp = strcmp(codIATA, vrAerop[pm].codIATA);

    if (cmp == 0) {
      return pm;
    } else if (cmp < 0) {
      ls = pm - 1;
    } else {
      li = pm + 1;
    }
  }

  return -1;  // No encontrado
}  // BusBinVec

void FormatoHoraMin(short hora, short &hh, short &mm) {
  hh = hora / 100;
  mm = hora - hh * 100;
}  // FormatoHoraMin

void HoraLlega(short distKm, short velCrucero, short hhSa, short mmSa,
               short &hhVi, short &mmVi, short &hhLl, short &mmLl) {
  float tV = (float)distKm / (float)velCrucero;
  hhVi = tV;
  mmVi = (tV - hhVi) * 60;  // + 0.5 para redondear
  mmLl = (mmSa + mmVi) % 60;
  hhLl = (hhSa + hhVi + (mmSa + mmVi) / 60) % 24;
}  // HoraLlega

string Replicate(char car, ushort n) {
  string resultado = "";
  for (ushort i = 0; i < n; i++)
    resultado += car;
  return resultado;
}  // Replicate

// void SubCad();
// void InsertarEnOrden();
// void VerifEstado();
// void InsertaEnLugar();
// void BuscarClvNodo();
