file(GLOB SRC_LIST *.c *.h include/*.h)

add_library(nist_sts STATIC ${SRC_LIST})

if (UNIX)
set(DEPENDS m)
target_link_libraries(nist_sts ${DEPENDS})
endif ()
