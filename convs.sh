#!/usr/bin/env bash

x86_64-w64-mingw32-clang++ -static -O0 -Wall -Wextra -Wpedantic -std=c++23 "datos/ConvAeropuertos.cpp" -o "datos/ConvAeropuertos.exe"
wine datos/ConvAeropuertos.exe
rm datos/ConvAeropuertos.exe
x86_64-w64-mingw32-clang++ -static -O0 -Wall -Wextra -Wpedantic -std=c++23 "datos/ConvVuelos.cpp" -o "datos/ConvVuelos.exe"
wine datos/ConvVuelos.exe
rm datos/ConvVuelos.exe
x86_64-w64-mingw32-clang++ -static -O0 -Wall -Wextra -Wpedantic -std=c++23 "datos/ConvConsultas.cpp" -o "datos/ConvConsultas.exe"
wine datos/ConvConsultas.exe
rm datos/ConvConsultas.exe