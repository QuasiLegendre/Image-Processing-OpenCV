add_executable(HW1_1 hw1_1.cpp)
target_link_libraries(HW1_1 ${OpenCV_LIBS} -lpthread)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
install(TARGETS HW1_1 RUNTIME DESTINATION bin)
