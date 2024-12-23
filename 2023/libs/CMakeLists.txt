
file(GLOB COMMON_SRC_FILES CONFIGURE_DEPENDS "common/*.cpp")
add_library(Common ${COMMON_SRC_FILES})
