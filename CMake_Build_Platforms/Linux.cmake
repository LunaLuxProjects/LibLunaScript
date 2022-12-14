set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CXX_EXTENSIONS O)

set_property ( TARGET libos PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libs/binarys/liblibos.so )

set( compiler_source ${compiler_source}
${PROJECT_SOURCE_DIR}/src/lib/back/IRCodeGen.cpp)


add_library ( liblunascript SHARED ${compiler_source} )
target_include_directories ( liblunascript PRIVATE /usr/lib/llvm-15/include STATIC )
target_compile_options ( liblunascript PRIVATE -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS )
target_link_options ( liblunascript PRIVATE -L/usr/lib/llvm-15/lib -lLLVM-15 )
set_property ( TARGET liblunascript PROPERTY CXX_STANDARD 20 )
target_include_directories (liblunascript PRIVATE  ${PROJECT_SOURCE_DIR}/libs/include STATIC )
target_include_directories ( liblunascript PRIVATE ${PROJECT_SOURCE_DIR}/src/share/rapidjson/include STATIC )
target_include_directories (liblunascript PRIVATE  ${PROJECT_SOURCE_DIR}/src/share STATIC )
target_compile_options ( liblunascript PRIVATE -Wall -Wextra -Werror )
if ( ${DEBUG_MODE} )
    if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
            target_compile_options ( liblunascript PRIVATE -static-libgcc -static-libstdc++ -g3 -O0 )
    else ()
        if ( ${FUZZING} )
            target_compile_options ( liblunascript PRIVATE -fsanitize=fuzzer,undefined )
            target_link_options ( liblunascript PRIVATE -fsanitize=fuzzer,undefined )
        else ()
                target_compile_options ( liblunascript PRIVATE -g3 -O0 )
        endif ()
    endif ()
else ()
    target_compile_options ( liblunascript PRIVATE -O3 -g0 )
endif ()