file(GLOB SRC_LIST *.c *.h include/*.h)

set(DEPENDS m)

add_library(nist_sts STATIC ${SRC_LIST})
target_link_libraries(nist_sts ${DEPENDS})