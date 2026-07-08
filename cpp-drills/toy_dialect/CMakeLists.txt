cmake_minimum_required(VERSION 3.20)
project(toy_dialect LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── find MLIR + LLVM (their find_package pulls in everything) ──
find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# make MLIR/LLVM's CMake helper modules (TableGen, AddMLIR, ...) available
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

# ── include paths ──
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})   # ToyPatterns.h
include_directories(${CMAKE_CURRENT_BINARY_DIR})   # generated .inc files land here

add_definitions(${LLVM_DEFINITIONS})

# ── TableGen: toy_ops.td → generated .inc  (rung 32, now driven by CMake) ──
set(LLVM_TARGET_DEFINITIONS toy_ops.td)
mlir_tablegen(toy_ops.h.inc        -gen-op-decls)
mlir_tablegen(toy_ops.cpp.inc      -gen-op-defs)
mlir_tablegen(toy_dialect.h.inc    -gen-dialect-decls)
mlir_tablegen(toy_dialect.cpp.inc  -gen-dialect-defs)
add_public_tablegen_target(ToyIncGen)

# ── the driver executable ──
add_llvm_executable(toy-opt
  toy_opt.cpp
  ToyPatterns.cpp
  ToyDialect.cpp
)

# ensure .inc files are generated BEFORE the sources that #include them compile
add_dependencies(toy-opt ToyIncGen)

# ── link against the MLIR libraries this build actually needs ──
target_link_libraries(toy-opt PRIVATE
  MLIRIR
  MLIRParser
  MLIRPass
  MLIRTransforms
  MLIRTransformUtils
  MLIRFuncDialect
  MLIRSupport
  MLIRAnalysis
)

llvm_update_compile_flags(toy-opt)