add_executable(server_main 
${CMAKE_SOURCE_DIR}/server/src/main.cpp
${CMAKE_SOURCE_DIR}/server/src/server.cpp
)
target_include_directories(server_main PRIVATE ${CMAKE_SOURCE_DIR}/server/include)
