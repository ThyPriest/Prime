
import subprocess
import Globals

subprocess.call(["cmd.exe", "/c", "robocopy",
                Globals.SOURCE_DIR, Globals.DEST_DIR, "Prime.dll"])
