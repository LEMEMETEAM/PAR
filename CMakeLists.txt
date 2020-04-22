project(PAR)

set (CMAKE_C_FLAGS "-g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

add_executable(PAR test/test.c test/glad.c)

target_link_libraries(PAR gdi32 opengl32 ${PROJECT_SOURCE_DIR}/test/libglfw3.a)

target_include_directories(PAR PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/test)