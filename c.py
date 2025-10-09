#!/usr/bin/env python3

# Compilar el código

from utils import cargar_env, compilar_src, limpiar_cache_python

def main():
    env = cargar_env()
    compilar_src(env, env.get("SRC"))
    limpiar_cache_python()

if __name__ == "__main__":
    main()
