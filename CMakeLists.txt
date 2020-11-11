project(thread-examples-cpp)
cmake_minimum_required(VERSION 3.18.2)

set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
  -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
  -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept \
  -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow \
  -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
  -Wswitch-default -Wundef -Werror -Wunused")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "9.0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpessimizing-move -Wredundant-move")
  endif()
endif()
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(simple_thread src/simple_thread.cpp)
target_link_libraries(simple_thread -pthread)

add_executable(simple_thread_promise src/simple_thread_promise.cpp)
target_link_libraries(simple_thread_promise -pthread)

add_executable(mutex src/mutex.cpp)
target_link_libraries(mutex -pthread)