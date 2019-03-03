include_directories(${CMAKE_SOURCE_DIR}/nist_sts/include
                    ${OPENSSL_HOME_PATH}/include)

link_directories(${OPENSSL_HOME_PATH}/lib)

set(TESTT_DEPENDS nist_sts)

if (WIN32)
	set(TESTT_DEPENDS ${TESTT_DEPENDS} libeay32)
elseif (UNIX)
	set(TESTT_DEPENDS ${TESTT_DEPENDS} libcrypto)
endif ()

file(GLOB TEST_SRC_LIST main.c)
add_executable(nist_sts_test ${TEST_SRC_LIST})
target_link_libraries(nist_sts_test ${TESTT_DEPENDS})
set_target_properties(nist_sts_test PROPERTIES FOLDER "test")