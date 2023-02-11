add_library(sys sys.cpp)
target_include_directories(sys PUBLIC
                                ${OpenRAVE_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(sys PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(sys PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(sys ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} 
                            ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
install(TARGETS sys)
