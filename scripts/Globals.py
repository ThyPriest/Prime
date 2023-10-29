
import os

SCRIPTS_DIR = "scrpts"
CONFIG = "Debug"
SYSTEM = "windows"

SOURCE_DIR = os.path.join(os.path.split(os.getcwd())[
                          0], "bin", CONFIG, SYSTEM, "Prime")

DEST_DIR = os.path.join(os.path.split(os.getcwd())[
    0], "bin", CONFIG, SYSTEM, "Terra")
