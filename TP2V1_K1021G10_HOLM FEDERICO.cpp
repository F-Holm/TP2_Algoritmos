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

#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

// Declaraciones de Structs

struct sAerop;
struct sVue;
struct tInfo;
struct sNodo;
struct sTblAerop;

// Constantes, Macros y Typedef

const short CANT_AEROP = 57;
#define ARCHIVOS fstream &Aerops, fstream &Vues, ifstream &Conslts
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
struct sAerop { // Size: 82 B
  str20 provin;
  str25 ciudad;
  str30 nomAeropto;
  str4 codOACI;
  str3 codIATA;
};  // Sin orden - 57 registros

struct sVue { // Size: 40 B
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
void ProcAeropuertos();
void ProcVuelos();
void ConsultasVuelos();
void ListVueAeropSld();
void Cerrar(ARCHIVOS);
void OrdxBur(tvrAerop &vrAerop);
void IntCmb(sTblAerop &sElem1, sTblAerop &sElem2);
// void replicate();
// void SubCad();
// void InsertarEnOrden();
// void BusBinVec();
// void HoraLlega();
// void FormatoHoraMin();
// void VerifEstado();
// void InsertaNodo();
// void InsertaInicio();
// void InsertaEnMedio();
// void InsertaEnLugar();
// void BuscarClvNodo();
// void SacarPrimerNodo();

// Main

int main() {
  fstream Aerops, Vues;
  ifstream Conslts;
  tvrAerop vrAerop;
  tLista lVues;

  Abrir(Aerops, Vues, Conslts);
  ProcAeropuertos();
  ProcVuelos();
  ConsultasVuelos();
  ListVueAeropSld();
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
  Aerops.open("Aeropuertos.Dat", ios::binary | ios::in | ios::out);
  Vues.open("Vuelos.Dat", ios::binary | ios::in | ios::out);
  Conslts.open("Consultas.Dat", ios::binary | ios::in);
}  // Abrir

void ProcAeropuertos(fstream &Aerops, tvrAerop &vrAerop) {
  sAerop rAerop;
  while(Aerops.read((char*)&rAerop, sizeof(rAerop))){
  }
  OrdxBur(vrAerop);
}  // ProcAeropuertos

void ProcVuelos();
void ConsultasVuelos();
void ListVueAeropSld();

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

// void replicate();
// void SubCad();
// void InsertarEnOrden();
// void BusBinVec();
// void HoraLlega();
// void FormatoHoraMin();
// void VerifEstado();
// void InsertaNodo();
// void InsertaInicio();
// void InsertaEnMedio();
// void InsertaEnLugar();
// void BuscarClvNodo();
// void SacarPrimerNodo();