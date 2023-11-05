# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(threadingTests LANGUAGES CXX)

# ---- Tests ----

add_executable(threading_test source/threading_test.cpp)
target_link_libraries(threading_test PRIVATE threading_lib)
target_compile_features(threading_test PRIVATE cxx_std_20)

add_test(NAME threading_test COMMAND threading_test)

# ---- End-of-file commands ----

add_folders(Test)
