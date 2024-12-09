find_package(SDL2 REQUIRED CONFIG)

file(GLOB_RECURSE SANDBOX_HEADERS ./*.hpp)
aux_source_directory(. SANDBOX_SRC)
aux_source_directory(./input SANDBOX_SRC)
aux_source_directory(./scene SANDBOX_SRC)

add_executable(sandbox ${SANDBOX_SRC} ${SANDBOX_HEADERS})
target_link_libraries(sandbox PRIVATE physics_engine)
target_compile_features(sandbox PRIVATE cxx_std_17)
target_link_libraries(sandbox
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_include_directories(sandbox PRIVATE .)
