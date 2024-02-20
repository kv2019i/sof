# Xtensa CMake toolchain file. Apply it using CMAKE_TOOLCHAIN_FILE variable.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_TRY_COMPILE_PLATFORM_VARIABLES XTENSA_TOOLCHAIN_PATH)

if(NOT XTENSA_TOOLCHAIN_PATH)
	set(XTENSA_TOOLCHAIN_PATH $ENV{XTENSA_TOOLCHAIN_PATH})
endif()

if(NOT XTENSA_TOOLCHAIN_PATH)
	message(FATAL_ERROR "Failed to find Xtensa toolchain: XTENSA_TOOLCHAIN_PATH (env or CMake) variable not defined.")
endif()

cmake_path(CONVERT ${XTENSA_TOOLCHAIN_PATH} TO_CMAKE_PATH_LIST XTENSA_TOOLCHAIN_PATH)
cmake_path(APPEND XTENSA_TOOLCHAIN_PATH "XtensaTools" OUTPUT_VARIABLE TOOLCHAIN_BASE)
set(CROSS_COMPILE xt-)

# clang or xcc
find_program(CMAKE_C_COMPILER NAMES ${CROSS_COMPILE}clang
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)
# clang++ or xc++
find_program(CMAKE_CXX_COMPILER NAMES ${CROSS_COMPILE}clang++
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)
find_program(CMAKE_LD NAMES ${CROSS_COMPILE}ld
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)
find_program(CMAKE_AR NAMES ${CROSS_COMPILE}ar
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)
find_program(CMAKE_RANLIB NAMES ${CROSS_COMPILE}ranlib
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)
find_program(CMAKE_OBJCOPY NAMES ${CROSS_COMPILE}objcopy
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)
find_program(CMAKE_OBJDUMP NAMES ${CROSS_COMPILE}objdump
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)
find_program(CMAKE_NM NAMES ${CROSS_COMPILE}nm
	PATHS ${TOOLCHAIN_BASE} PATH_SUFFIXES "bin" REQUIRED NO_DEFAULT_PATH
)

cmake_path(APPEND TOOLCHAIN_BASE "xtensa-elf" OUTPUT_VARIABLE XTENSA_ELF_ROOT)
set(CMAKE_FIND_ROOT_PATH ${XTENSA_ELF_ROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)