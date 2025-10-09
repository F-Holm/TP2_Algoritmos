#!/usr/bin/env python3

# Ejecuta el programa compilado

from utils import cargar_env, ejecutar_ejecutable, limpiar_cache_python

def main():
    env = cargar_env()
    ejecutar_ejecutable(env, env.get("SRC"))
    limpiar_cache_python()

if __name__ == "__main__":
    main()
