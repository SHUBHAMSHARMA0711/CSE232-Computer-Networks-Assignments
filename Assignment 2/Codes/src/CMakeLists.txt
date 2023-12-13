file (GLOB LIB_SOURCES "*.cc" "util/*.cc" "tcp_helpers/*.cc")
add_library (tcp_reciever STATIC ${LIB_SOURCES})
