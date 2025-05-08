# Get the application root directory
export APP_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Get all other subfolder paths 
export LOG_DIR="$APP_ROOT/log"
export INC_DIR="$APP_ROOT/inc"
export SRC_DIR="$APP_ROOT/src"
export CFG_DIR="$APP_ROOT/config"
export BIN_DIR="$APP_ROOT/bin"
export SCRIPT_DIR="$APP_ROOT/scripts"


