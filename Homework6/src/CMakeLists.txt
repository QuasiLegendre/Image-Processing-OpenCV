add_executable(Eye Eye.cpp)
target_link_libraries(Eye ${OpenCV_LIBS} -lpthread)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
install(TARGETS Eye RUNTIME DESTINATION bin)
