add_executable(GSharp GSharp.cpp)
add_executable(HomoFilt HomoFilt.cpp)
add_executable(HomoFilters HomoFilters.cpp)
target_link_libraries(GSharp ${OpenCV_LIBS} -lpthread)
target_link_libraries(HomoFilt ${OpenCV_LIBS} -lpthread)
target_link_libraries(HomoFilters ${OpenCV_LIBS} -lpthread)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
install(TARGETS GSharp RUNTIME DESTINATION bin)
install(TARGETS HomoFilt RUNTIME DESTINATION bin)
install(TARGETS HomoFilters RUNTIME DESTINATION bin)
