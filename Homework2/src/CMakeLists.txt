add_executable(HW2_1 hw2_1.cpp)
add_executable(HW2_2 hw2_2.cpp)
target_link_libraries(HW2_1 ${OpenCV_LIBS} -lpthread)
target_link_libraries(HW2_2 ${OpenCV_LIBS} -lpthread)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
install(TARGETS HW2_1 RUNTIME DESTINATION bin)
install(TARGETS HW2_2 RUNTIME DESTINATION bin)
