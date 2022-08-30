project(ArithmeticExpr)

cmake_minimum_required (VERSION 3.14)
set (CMAKE_CXX_STANDARD 17)


# Bring in the required packages

set(antlr4-runtime_DIR /Users/maokang/CLionProjects/bean/antlr4_cpp/resources/thirdparty/antlr/antlr4-cpp-runtime-4.10.1-source/run/usr/local/lib/cmake/antlr4-runtime)
set(antlr4-generator_DIR /Users/maokang/CLionProjects/bean/antlr4_cpp/resources/thirdparty/antlr/antlr4-cpp-runtime-4.10.1-source/run/usr/local/lib/cmake/antlr4-generator)


find_package(antlr4-runtime REQUIRED)
find_package(antlr4-generator REQUIRED)

# Set path to generator
set(ANTLR4_JAR_LOCATION ${PROJECT_SOURCE_DIR}/../resources/thirdparty/antlr/antlr-4.10.1-complete.jar)

# generate lexer and parser
antlr4_generate(
     expr                                  # Unique target name. It is used to generate CMake Variables to reference the various outputs of the generation
     ${CMAKE_CURRENT_SOURCE_DIR}/Expr.g4   # Input file containing the lexer/parser definition
     BOTH                                       # Type of Rules contained in the input: LEXER, PARSER or BOTH
     TRUE                                       # Boolean to indicate if a listener interface should be generated
     TRUE                                      # Boolean to indicate if a visitor interface should be generated
     "expr"                             # C++ namespace in which the generated classes should be placed
#     none                                   # Additional files on which the input depends
#     none                                   # Library path to use during generation
)

# add directories for generated include files
include_directories( ${PROJECT_BINARY_DIR} ${ANTLR4_INCLUDE_DIR} ${ANTLR4_INCLUDE_DIR_expr} )
message(${ANTLR4_INCLUDE_DIR_expr} ${ANTLR4_INCLUDE_DIR})

# add generated source files
add_executable( ArithmeticExpr ${ANTLR4_SRC_FILES_expr} ${ANTLR4_SRC_FILES_expr} main.cpp)

# add required runtime library
add_dependencies( ArithmeticExpr antlr4_shared )

target_link_libraries( ArithmeticExpr PRIVATE antlr4_shared )
