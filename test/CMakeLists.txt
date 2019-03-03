include_directories(${CMAKE_SOURCE_DIR}/public/nist_sts/include
                    ${CMAKE_SOURCE_DIR}/public/libcryptohelper
					${CMAKE_SOURCE_DIR}/public/libcomnutils
                    ${OPENSSL_HOME_PATH}/include)

link_directories(${OPENSSL_HOME_PATH}/lib)

file(GLOB TEST_SRC_LIST main.c)
set(TESTT_DEPENDS nist_sts libcryptohelper)
add_executable(nist_sts_test ${TEST_SRC_LIST})
target_link_libraries(nist_sts_test ${TESTT_DEPENDS})
set_target_properties(nist_sts_test PROPERTIES FOLDER "test")