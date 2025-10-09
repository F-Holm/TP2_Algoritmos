#!/usr/bin/env python3

# Compila, ejecuta y elimina los programas para convertir de .Txt a .Dat

from utils import cargar_env, compilar_src, ejecutar_ejecutable, base_name, eliminar_archivo, limpiar_cache_python

def main():
    env = cargar_env()
    separador = env.get("SEPARADOR")
    if not separador:
        print("Separador no encontrado")
        return
    archivos = env.get("NOMBRES_CONVERTIDORES")
    if not archivos:
        print("Archivos no encontrados")
        return
    archivos = [archivo.strip() for archivo in archivos.split(separador) if archivo.strip()]
    for archivo in archivos:
        archivo.strip()
        compilar_src(env, archivo)
        ejecutar_ejecutable(archivo)
        eliminar_archivo(base_name(archivo) + ".exe")
    limpiar_cache_python()

if __name__ == "__main__":
    main()
