#!/usr/bin/env python3

# Compilar el código

import sys

from utils import cargar_env, limpiar_cache_python, compilar_src

def main():
    env = cargar_env()
    compilar_src(env, env.get("SRC"))
    limpiar_cache_python()

if __name__ == "__main__":
    main()
