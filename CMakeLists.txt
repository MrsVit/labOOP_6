cmake_minimum_required(VERSION 3.14)

# Название проекта (можно оставить lab6 или изменить)
project(Dungeon LANGUAGES CXX)

# Требуем C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# === Компиляторные флаги ===
if(MSVC)
    # Включаем максимальные предупреждения и treat-as-errors
    add_compile_options(/W4 /WX)
    # Отключаем secure warnings от MSVC (если используете fopen, strcpy и т.д.)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Werror -Wno-unused-parameter)
    # Опционально: ваш флаг — но работает не во всех GCC/clang одинаково
    # add_compile_options(-Werror=maybe-uninitialized)
endif()

# === Загрузка GoogleTest ===
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.0  # стабильная, поддерживает C++17+, совместима с C++20
)
# Для Windows: используем shared CRT (чтобы не было конфликтов с библиотеками)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# === Явное перечисление исходников ===
# Заголовки (из head/)
set(HEADERS
    head/BattleVisitor.h
    head/ConsoleObserver.h
    head/Druid.h
    head/Dungeon.h
    head/Elf.h
    head/FileObserver.h
    head/Knight.h
    head/NPC.h
    head/NPCFactory.h
    head/Observer.h
    head/Visitor.h
)

# Исходники (из body/)
set(SOURCES
    body/ButtleVisitor.cpp
    body/ConsolObserver.cpp
    body/Dungeon.cpp
    body/FileObserver.cpp
    body/NCP.cpp
    body/NPCFactory.cpp
)

# === Статическая библиотека (ядро логики) ===
add_library(dungeon_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(dungeon_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/head
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/body
)

add_executable(f body/main.cpp)
target_link_libraries(f PRIVATE dungeon_lib)
set_target_properties(f PROPERTIES OUTPUT_NAME "f" SUFFIX ".exe")

enable_testing()

set(TEST_SOURCES
    tests/test_one.cpp
)

add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests PRIVATE dungeon_lib gtest_main)

# Регистрация в ctest
add_test(NAME dungeon_tests COMMAND run_tests)