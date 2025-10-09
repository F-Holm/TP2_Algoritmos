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

#include <fstream>

using namespace std;

// Declaraciones de Structs
struct sAerop;
struct sVue;
struct tInfo;
struct sNodo;
struct sTblAerop;

// Constantes, Macros y Typedef
const short CANT_AEROP = 57;
#define ARCHIVOS ifstream &Aerops, ifstream &Vues, ifstream &Consultas
typedef char str3[4];
typedef char str4[5];
typedef char str8[9];
typedef char str9[10];
typedef char str11[12];
typedef char str20[21];
typedef char str25[26];
typedef char str30[31];
typedef sAerop tvrAerop[CANT_AEROP];
typedef struct sNodo* tLista;

// Definiciones de Structs
struct sAerop {
  str20 provin;
  str25 ciudad;
  str30 nomAeropto;
  str4 codOACI;
  str3 codIATA;
};  // Sin orden - 57 registros

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

struct Consulta {
  str9 numVuelo;
  str25 ciudad;
  str30 nomAeropto;
  str4 codOACI;
  str3 codIATA;
};  // Sin orden

// Declaraciones de Funciones
#define NO_SE_EL_TIPO void
long GetDate(int &year, int &mes, int &dia, int &ds);
long GetTime(int &hh, int &mm, int &ss);
void Abrir(ARCHIVOS);
NO_SE_EL_TIPO ProcAeropuertos();
NO_SE_EL_TIPO ProcVuelos();
NO_SE_EL_TIPO ConsultasVuelos();
NO_SE_EL_TIPO ListVueAeropSld();
void Cerrar(ARCHIVOS);
NO_SE_EL_TIPO replicate();
NO_SE_EL_TIPO SubCad();
NO_SE_EL_TIPO OrdxBur();
NO_SE_EL_TIPO IntCmb();
NO_SE_EL_TIPO InsertarEnOrden();
NO_SE_EL_TIPO BusBinVec();
NO_SE_EL_TIPO HoraLlega();
NO_SE_EL_TIPO FormatoHoraMin();
NO_SE_EL_TIPO VerifEstado();
NO_SE_EL_TIPO InsertaNodo();
NO_SE_EL_TIPO InsertaInicio();
NO_SE_EL_TIPO InsertaEnMedio();
NO_SE_EL_TIPO InsertaEnLugar();
NO_SE_EL_TIPO BuscarClvNodo();
NO_SE_EL_TIPO SacarPrimerNodo();

// Main

int main() {
  ifstream Aerops, Vues, Consultas;

  Abrir(Aerops, Vues, Consultas);
  ProcAeropuertos();
  ProcVuelos();
  ConsultasVuelos();
  ListVueAeropSld();
  Cerrar(Aerops, Vues, Consultas);
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
  Consultas.open("Consultas.Dat", ios::binary | ios::in);
}  // Abrir

NO_SE_EL_TIPO ProcAeropuertos();
NO_SE_EL_TIPO ProcVuelos();
NO_SE_EL_TIPO ConsultasVuelos();
NO_SE_EL_TIPO ListVueAeropSld();

void Cerrar(ARCHIVOS) {
  Aerops.close();
  Vues.close();
  Consultas.close();
}  // Cerrar

NO_SE_EL_TIPO replicate();
NO_SE_EL_TIPO SubCad();
NO_SE_EL_TIPO OrdxBur();
NO_SE_EL_TIPO IntCmb();
NO_SE_EL_TIPO InsertarEnOrden();
NO_SE_EL_TIPO BusBinVec();
NO_SE_EL_TIPO HoraLlega();
NO_SE_EL_TIPO FormatoHoraMin();
NO_SE_EL_TIPO VerifEstado();
NO_SE_EL_TIPO InsertaNodo();
NO_SE_EL_TIPO InsertaInicio();
NO_SE_EL_TIPO InsertaEnMedio();
NO_SE_EL_TIPO InsertaEnLugar();
NO_SE_EL_TIPO BuscarClvNodo();
NO_SE_EL_TIPO SacarPrimerNodo();