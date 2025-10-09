# Funciones comunes para los scripts

import os
import subprocess
import shutil
import sys
from enum import Enum, auto
import glob

class SistemaOperativo(Enum):
    WINDOWS = auto()
    LINUX = auto()
    MACOS = auto()
    OTRO = auto()

def detectar_sistema() -> SistemaOperativo:
    plataforma = sys.platform
    if plataforma.startswith("win"):
        return SistemaOperativo.WINDOWS
    elif plataforma.startswith("linux"):
        return SistemaOperativo.LINUX
    elif plataforma.startswith("darwin"):
        return SistemaOperativo.MACOS
    else:
        return SistemaOperativo.OTRO

def exist_file(ruta: str) -> bool:
    return os.path.isfile(ruta)

def exist_dir(ruta: str) -> bool:
    return os.path.isdir(ruta)

def base_name(src: str) -> str:
    return os.path.splitext(os.path.basename(src))[0]

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
    
def formatear_codigo() -> None:
    archivos = glob.glob("./*.cpp")
    if not archivos:
        print("No se encontraron archivos .cpp para formatear.")
        return
    comando = ["clang-format", "--style=file", "-i", *archivos]
    try:
        ejecutar_comando(comando)
    except:
        pass

def detectar_compilador(env):
    SO = detectar_sistema()
    if SO == SistemaOperativo.WINDOWS:
        comp_var = env.get("COMPILADOR_WINDOWS")
    elif SO == SistemaOperativo.LINUX:
        comp_var = env.get("COMPILADOR_LINUX")
    else:
        print(f"Sistema operativo no soportado: {sys.platform}")
        return None

    if not comp_var:
        print("No se definió el compilador para este sistema operativo.")
        return None

    compilador = env.get(comp_var)
    if not compilador:
        print(f"No se encontró la variable de compilador: {comp_var}")
        return None

    return compilador.split()


def compilar_src(env, src):
    if not src or not exist_file(src):
        print(f"Archivo SRC no encontrado: {src}")
        return
    formatear_codigo()
    compilador = detectar_compilador(env)
    if not compilador:
        return

    output_file = base_name(src) + ".exe"

    flags = []
    flags += env.get("INFO_FLAGS", "").split()
    flags += env.get("ESTANDAR", "").split()
    flags += env.get("EXTRA", "").split()

    modo = env.get("MODO")
    if not modo:
        print(f"Configuración 'MODO' no encontrada")
        return
    if modo.upper() == "R":
        flags += env.get("RELEASE_FLAGS", "").split()
    else:
        flags += env.get("DEBUG_FLAGS", "").split()

    comando = compilador + [src, "-o", output_file] + flags
    if ejecutar_comando(comando):
        print(f"✅ Compilación completada: {output_file}")