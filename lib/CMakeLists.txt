file(GLOB LIBBRAINC_SRC *.c)

add_library(libbrainc SHARED ${LIBBRAINC_SRC})

set_property(TARGET libbrainc PROPERTY C_STANDARD 99)
set_property(TARGET libbrainc PROPERTY C_STANDARD_REQUIRED ON)
