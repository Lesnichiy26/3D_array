add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE cube)
target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})