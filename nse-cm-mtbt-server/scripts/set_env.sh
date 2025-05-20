# This script is used to set all the require environment variables for the applicaiton

# Get the application root directory
export APP_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Get all other subfolder paths 
export LOG_DIR="$APP_ROOT/log"
export INC_DIR="$APP_ROOT/inc"
export SRC_DIR="$APP_ROOT/src"
export CFG_DIR="$APP_ROOT/config"
export BIN_DIR="$APP_ROOT/bin"
export SCRIPT_DIR="$APP_ROOT/scripts"

# Adding some aliases for easier movement in the application
alias root="cd $APP_ROOT"
alias src="cd $SRC_DIR"
alias inc="cd $INC_DIR"
alias script="cd $SCRIPT_DIR"
alias cfg="cd $CFG_DIR"
alias bin="cd $BIN_DIR"
alias log="cd $LOG_DIR"

