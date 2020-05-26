add_library(estrin
  estrin.c
  horner.c
  )
target_include_directories(estrin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
