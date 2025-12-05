add_library(KyraWindow STATIC Window.hpp
                              Window.cpp
                              WindowImplementation.hpp
			      WindowImplementation.cpp
                              WindowImplementationWinAPI.hpp
                              WindowImplementationWinAPI.cpp)
target_include_directories(KyraWindow PRIVATE ${KYRA_SOURCE_DIRECTORY})
target_link_libraries(KyraWindow PRIVATE KyraLog)