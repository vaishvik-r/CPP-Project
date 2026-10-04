cmake_minimum_required(VERSION 3.16)

project(DigitalCircuitDesigner
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(digital_circuit
    src/core/CircuitElement.cpp
    src/core/Gate.cpp
    src/core/Connection.cpp
    src/core/Circuit.cpp

    src/gates/NANDGate.cpp
    src/gates/NORGate.cpp
    src/gates/NOTGate.cpp
    src/gates/ANDGate.cpp
    src/gates/ORGate.cpp
    src/gates/XORGate.cpp
    src/gates/XNORGate.cpp

    src/circuits/HalfAdder.cpp
    src/circuits/FullAdder.cpp
    src/circuits/RippleCarryAdder.cpp

    src/simulation/Simulator.cpp
    src/simulation/SimulationResult.cpp

    src/output/ConsoleOutput.cpp
    src/output/CSVOutput.cpp

    src/analysis/TruthTableGenerator.cpp
)

target_include_directories(digital_circuit PUBLIC include)

target_compile_options(digital_circuit PRIVATE
    -Wall -Wextra -Wpedantic
)

add_executable(digital_circuit_designer main.cpp)
target_link_libraries(digital_circuit_designer PRIVATE digital_circuit)
target_compile_options(digital_circuit_designer PRIVATE
    -Wall -Wextra -Wpedantic
)

add_executable(digital_circuit_tests tests/test_main.cpp)
target_link_libraries(digital_circuit_tests PRIVATE digital_circuit)
target_compile_options(digital_circuit_tests PRIVATE
    -Wall -Wextra -Wpedantic
)

enable_testing()
add_test(NAME DigitalCircuitTests COMMAND digital_circuit_tests)
