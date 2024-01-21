project(thread-examples-cpp)
cmake_minimum_required(VERSION 3.18.2)

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
target_compile_options(simple_thread PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>)

add_executable(simple_thread_promise src/simple_thread_promise.cpp)
target_link_libraries(simple_thread_promise -pthread)
target_compile_options(simple_thread_promise PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>)

add_executable(mutex src/mutex.cpp)
target_link_libraries(mutex -pthread)
target_compile_options(mutex PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>)

add_executable(producer_consumer_queue src/producer_consumer_queue.cpp)
target_link_libraries(producer_consumer_queue -pthread)
target_compile_options(producer_consumer_queue PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>)

add_executable(thread_safe_queue src/thread_safe_queue.cpp)
target_link_libraries(thread_safe_queue -pthread)
target_compile_options(thread_safe_queue PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>)