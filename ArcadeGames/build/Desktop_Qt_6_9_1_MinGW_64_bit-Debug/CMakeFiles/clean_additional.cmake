# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "ArcadeGames_autogen"
  "CMakeFiles\\ArcadeGames_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ArcadeGames_autogen.dir\\ParseCache.txt"
  )
endif()
