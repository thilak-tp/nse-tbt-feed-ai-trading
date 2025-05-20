# This script is used to set all the require environment variables for the applicaiton

# Get the application root directory
export CAPP_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Get all other subfolder paths 
export CLOG_DIR="$CAPP_ROOT/log"
export CINC_DIR="$CAPP_ROOT/inc"
export CSRC_DIR="$CAPP_ROOT/src"
export CCFG_DIR="$CAPP_ROOT/config"
export CBIN_DIR="$CAPP_ROOT/bin"
export CSCRIPT_DIR="$CAPP_ROOT/scripts"

# Adding some aliases for easier movement in the application
alias croot="cd $CAPP_ROOT"
alias csrc="cd $CSRC_DIR"
alias cinc="cd $CINC_DIR"
alias cscript="cd $CSCRIPT_DIR"
alias ccfg="cd $CCFG_DIR"
alias cbin="cd $CBIN_DIR"
alias clog="cd $CLOG_DIR"

