add_library (tcp_reciever_checks STATIC byte_stream_test_harness.cc )

macro (add_test_exec exec_name)
    add_executable ("${exec_name}" "${exec_name}.cc")
    target_link_libraries ("${exec_name}" tcp_reciever_checks ${ARGN})
    target_link_libraries ("${exec_name}" tcp_reciever ${ARGN})
    add_test(NAME "${exec_name}"
             COMMAND "${exec_name}")
endmacro (add_test_exec)

add_test_exec (wrapping_integers_cmp)
add_test_exec (wrapping_integers_unwrap)
add_test_exec (wrapping_integers_wrap)
add_test_exec (wrapping_integers_roundtrip)

add_test_exec (byte_stream_construction)
add_test_exec (byte_stream_one_write)
add_test_exec (byte_stream_two_writes)
add_test_exec (byte_stream_capacity)
add_test_exec (byte_stream_many_writes)

add_test_exec (recv_connect)
add_test_exec (recv_transmit)
add_test_exec (recv_window)
add_test_exec (recv_reorder)
add_test_exec (recv_close)
add_test_exec (recv_special)


add_test_exec (fsm_stream_reassembler_cap)
add_test_exec (fsm_stream_reassembler_single)
add_test_exec (fsm_stream_reassembler_seq)
add_test_exec (fsm_stream_reassembler_dup)
add_test_exec (fsm_stream_reassembler_holes)
add_test_exec (fsm_stream_reassembler_many)
add_test_exec (fsm_stream_reassembler_overlapping)
add_test_exec (fsm_stream_reassembler_win)

