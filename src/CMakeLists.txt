

add_subdirectory(console)
add_subdirectory(errors)
add_subdirectory(exchange)
add_subdirectory(fs)
add_subdirectory(logger)
add_subdirectory(order)
add_subdirectory(tests)
add_subdirectory(trade)
add_subdirectory(utils)

find_package(Threads)
add_executable(Exchange Exchange.cpp ${SOURCE})

target_link_libraries(Exchange ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS Exchange RUNTIME DESTINATION .)