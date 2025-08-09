find_package(OpenSSL REQUIRED)
target_link_libraries(myvcs_core PRIVATE OpenSSL::Crypto)