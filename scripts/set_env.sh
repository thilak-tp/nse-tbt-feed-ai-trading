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
alias nroot="cd $APP_ROOT"
alias nsrc="cd $SRC_DIR"
alias ninc="cd $INC_DIR"
alias nscript="cd $SCRIPT_DIR"
alias ncfg="cd $CFG_DIR"
alias nbin="cd $BIN_DIR"
alias nlog="cd $LOG_DIR"

