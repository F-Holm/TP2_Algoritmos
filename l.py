#!/usr/bin/env python3

# Script de limpieza del proyecto.

from utils import git_clean, limpiar_cache_python

def main() -> None:
    git_clean()
    limpiar_cache_python()

if __name__ == "__main__":
    main()
