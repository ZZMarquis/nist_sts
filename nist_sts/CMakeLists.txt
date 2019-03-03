file(GLOB HTTPCLIENT_SRC *.c *.h include/*.h)

add_library(nist_sts STATIC ${HTTPCLIENT_SRC})

set_target_properties(nist_sts PROPERTIES FOLDER "Public")

add_subdirectory(test)
