add_library(myvcs_core
    core/repository.cpp
)

target_include_directories(myvcs_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(myvcs_client client/main.cpp)
target_link_libraries(myvcs_client PRIVATE myvcs_core)

add_executable(myvcs_server server/main.cpp)
target_link_libraries(myvcs_server PRIVATE myvcs_core)
