# Funciones comunes para los scripts

import os
import subprocess
import shutil

def exist_file(ruta: str) -> bool:
    return os.path.isfile(ruta)

def exist_dir(ruta: str) -> bool:
    return os.path.isdir(ruta)

def cargar_env(ruta="scripts_conf.env"):
    env_vars = {}
    if not exist_file(ruta):
        return env_vars
    with open(ruta, "r") as f:
        for linea in f:
            linea = linea.strip()
            if not linea or linea.startswith("#"):
                continue
            if "=" in linea:
                clave, valor = linea.split("=", 1)
                env_vars[clave.strip()] = valor.strip().strip('"').strip("'")
    return env_vars

def ejecutar_comando(comando: list[str]) -> bool:
    try:
        # print(f"→ Ejecutando: {' '.join(comando)}")
        subprocess.run(comando, check=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"❌ Error al ejecutar {' '.join(comando)}: {e}")
    except FileNotFoundError:
        print(f"⚠️ Comando no encontrado: {comando[0]}")
    return False

def eliminar_directorio(ruta: str) -> bool:
    if os.path.isdir(ruta):
        try:
            shutil.rmtree(ruta)
            # print(f"🗑️  Eliminado: {ruta}")
            return True
        except Exception as e:
            pass # print(f"❌ No se pudo eliminar {ruta}: {e}")
    return False

def limpiar_cache_python() -> None:
    eliminar_directorio("./__pycache__/")