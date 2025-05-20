#!/bin/bash

BINARY="$BIN_DIR/nse_sim"

# Check if the binary exists
if [ ! -f "$BINARY" ]; then
  echo "Error: Binary '$BINARY' not found."
  exit 1
fi

# Set capability for real-time scheduling (does not require full sudo afterwards)
echo "Granting CAP_SYS_NICE to allow real-time scheduling..."
sudo setcap cap_sys_nice+ep "$BINARY"

# Optional: Show capabilities
echo "Capabilities for $BINARY:"
getcap "$BINARY"

# Now run the binary (no sudo required for SCHED_FIFO if cap is set)
echo "Running the binary with real-time scheduling..."
exec "$BINARY"

