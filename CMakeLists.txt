cmake_minimum_required (VERSION 3.0)
project (versionslib)
enable_language (CXX)

list (APPEND includes_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
list (APPEND cxx_features cxx_auto_type cxx_decltype cxx_defaulted_functions
  cxx_deleted_functions cxx_nullptr cxx_nonstatic_member_init
  cxx_rvalue_references)
list (APPEND cxx_options "-std=c++11")

add_executable (test0 test.cxx)
target_include_directories (test0 PUBLIC ${includes_dir})
#
#target_compile_features(test0 PUBLIC ${cxx_features})
target_compile_options(test0 PUBLIC ${cxx_options})

add_test (TestTest test0)
