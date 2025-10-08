#!/usr/bin/env python3

# Script para darle formato estándar al código

from utils import cargar_env, limpiar_cache_python, formatear_codigo

def main():
    env = cargar_env()
    src = env.get("SRC")
    formatear_codigo(src)
    limpiar_cache_python()

if __name__ == "__main__":
    main()
