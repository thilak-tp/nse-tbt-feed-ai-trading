# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.28
cmake_policy(SET CMP0009 NEW)

# SRCS at CMakeLists.txt:14 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/*.cpp")
set(OLD_GLOB
  "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/common.cpp"
  "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/config_parser.cpp"
  "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/latency_benchmark.cpp"
  "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/log.cpp"
  "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/multicast.cpp"
  "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/nse_feed_gen.cpp"
  "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/src/simulate_mtbt_values.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/ovrteq/learning/dev/nse-cm-mtbt-sim/nse-tbt-feed-ai-trading/nse-cm-mtbt-server/build/CMakeFiles/cmake.verify_globs")
endif()
