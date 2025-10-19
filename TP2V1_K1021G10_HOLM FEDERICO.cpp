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
typedef struct sNodo *tLista;
typedef unsigned short ushort;

// Definiciones de Structs
struct sAerop {
  str20 provin;
  str25 ciudad;
  str30 nomAeropto;
  str4 codOACI;
  str3 codIATA;
};

struct sVue {
  str9 nroVuelo;
  short distKm;
  short velCrucero;
  short cantPsj;
  str8 empresa;
  str11 marcaAeronv;
  int fechaSale;
  short horaSale;
};

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
};

// Typedef
typedef sTblAerop tvrAerop[CANT_AEROP];

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
  for (ushort i = 0; Aerops.read((char *)&rAerop, sizeof(sAerop)); i++) {
    strcpy(vrAerop[i].codIATA, rAerop.codIATA);
    vrAerop[i].pos = i;
  }
  OrdxBur(vrAerop);
}  // ProcAeropuertos

void ProcVuelos(ifstream &Vues, tLista &lVues) {
  sVue rVue;
  tInfo info;
  ushort i = 0;
  while (Vues.read((char *)&rVue, sizeof(sVue))) {
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
  const char *meses[] = {"Enero",      "Febrero", "Marzo",     "Abril",
                         "Mayo",       "Junio",   "Julio",     "Agosto",
                         "Septiembre", "Octubre", "Noviembre", "Diciembre"};

  GetTime(hh, mm, ss);
  GetDate(anio, mes, dia, ds);
  cout << Replicate(' ', 168 / 2 - 48) << "Consultas de vuelos del " << dia
       << " de " << meses[mes] << " de " << anio
       << "\nNroVuelo  Ciudad de origen Nom.Aerop.Orig.  Empresa  Marca     "
          "  Ciudad Destino   Nom.Aerop.Dest.  Estado          dia hhAct hhSa "
          "t.V.  hhLl \n\n";

  while (Conslts.read(nroVuelo, sizeof(str9))) {
    if (strcmp(aux->info.nroVuelo, nroVuelo) > 0)
      aux = lVues;
    while (strcmp(aux->info.nroVuelo, nroVuelo) != 0)
      aux = aux->sgte;

    Vues.clear();
    Vues.seekg(aux->info.pos * sizeof(sVue));
    Vues.read((char *)&rVue, sizeof(sVue));

    sAerop origen, destino;

    Aerops.clear();
    Aerops.seekg(vrAerop[BusBinVec(vrAerop, nroVuelo)].pos * sizeof(sAerop));
    Aerops.read((char *)&origen, sizeof(sAerop));

    Aerops.clear();
    Aerops.seekg(vrAerop[BusBinVec(vrAerop, nroVuelo + 6)].pos *
                 sizeof(sAerop));
    Aerops.read((char *)&destino, sizeof(sAerop));

    short hhSa, mmSa, hhVi, mmVi, hhLl, mmLl, diaSa = rVue.fechaSale % 100;
    FormatoHoraMin(rVue.horaSale, hhSa, mmSa);
    HoraLlega(rVue.distKm, rVue.velCrucero, hhSa, mmSa, hhVi, mmVi, hhLl, mmLl);

    origen.ciudad[16] = '\0';
    origen.nomAeropto[16] = '\0';
    destino.ciudad[16] = '\0';
    destino.nomAeropto[16] = '\0';
    destino.provin[15] = '\0';

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
       << Replicate('=', 141) << "\n\n"
       << Replicate(' ', 0)
       << "Listado Salidas Aerop. Origen a otros Aerop. Llegada, del dia "
       << dia << "\n";

  for (ushort i = 0; i < CANT_AEROP; i++) {
    Aerops.clear();
    Aerops.seekg(vrAerop[i].pos * sizeof(sAerop));
    Aerops.read((char *)&rAerop, sizeof(sAerop));

    if (lVues != NULL && strncmp(lVues->info.nroVuelo, rAerop.codIATA, 3) == 0)
      cout << "\nAerop. origen: " << rAerop.codIATA << "  " << rAerop.nomAeropto
           << "  Ciudad: " << rAerop.ciudad
           << "\nNroVue.   Empresa  Marca       Ciu.Dest.       "
              " Nom.Aerop.Dest.  Estado          dia hhAct hhSa t.V.  hhLl \n";

    while (lVues != NULL &&
           strncmp(lVues->info.nroVuelo, rAerop.codIATA, 3) == 0) {
      Vues.clear();
      Vues.seekg(lVues->info.pos * sizeof(sVue));
      Vues.read((char *)&rVue, sizeof(sVue));

      Aerops.clear();
      Aerops.seekg(vrAerop[BusBinVec(vrAerop, rVue.nroVuelo + 6)].pos *
                   sizeof(sAerop));
      Aerops.read((char *)&aeropDest, sizeof(sAerop));

      short hhSa, mmSa, hhVi, mmVi, hhLl, mmLl, diaSa = rVue.fechaSale % 100;
      FormatoHoraMin(rVue.horaSale, hhSa, mmSa);
      HoraLlega(rVue.distKm, rVue.velCrucero, hhSa, mmSa, hhVi, mmVi, hhLl,
                mmLl);

      aeropDest.ciudad[16] = '\0';
      aeropDest.nomAeropto[16] = '\0';
      aeropDest.provin[15] = '\0';

      cout << setw(9) << rVue.nroVuelo << ' ' << setw(8) << rVue.empresa << ' '
           << setw(11) << rVue.marcaAeronv << ' ' << setw(16)
           << aeropDest.ciudad << ' ' << setw(16) << aeropDest.nomAeropto << ' '
           << setw(15) << aeropDest.provin << ' ' << setw(2) << diaSa << ' '
           << setfill('0') << setw(2) << hh << ':' << setw(2) << mm << ' '
           << setw(2) << hhSa << ':' << setw(2) << mmSa << ' ' << setw(2)
           << hhVi << ':' << setw(2) << mmVi << ' ' << setw(2) << hhLl << ':'
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
  if (lista == NULL || strcmp(valor.nroVuelo, lista->info.nroVuelo) < 0)
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
  int li = 0, ls = CANT_AEROP - 1, pm;

  while (li <= ls) {
    pm = (li + ls) / 2;

    int cmp = strncmp(codIATA, vrAerop[pm].codIATA, 3);

    if (cmp == 0)
      return pm;
    else if (cmp < 0)
      ls = pm - 1;
    else
      li = pm + 1;
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
