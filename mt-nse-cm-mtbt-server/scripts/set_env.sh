# This script is used to set all the require environment variables for the applicaiton

# Get the application root directory
export TAPP_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Get all other subfolder paths 
export TLOG_DIR="$TAPP_ROOT/log"
export TINC_DIR="$TAPP_ROOT/inc"
export TSRC_DIR="$TAPP_ROOT/src"
export TCFG_DIR="$TAPP_ROOT/config"
export TBIN_DIR="$TAPP_ROOT/bin"
export TSCRIPT_DIR="$TAPP_ROOT/scripts"

# Adding some aliases for easier movement in the application
alias troot="cd $TAPP_ROOT"
alias tsrc="cd $SRC_DIR"
alias tinc="cd $INC_DIR"
alias tscript="cd $SCRIPT_DIR"
alias tcfg="cd $CFG_DIR"
alias tbin="cd $BIN_DIR"
alias tlog="cd $LOG_DIR"

