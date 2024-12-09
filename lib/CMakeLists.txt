aux_source_directory(. LIB_SRC)
aux_source_directory(./math LIB_SRC)
file(GLOB_RECURSE LIB_HEADERS ./*.hpp)

add_library(physics_engine STATIC)
target_sources(physics_engine PRIVATE ${LIB_SRC} ${LIB_HEADERS})
target_include_directories(physics_engine PUBLIC .)
target_compile_features(physics_engine PUBLIC cxx_std_20)
