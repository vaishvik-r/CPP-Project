# Digital Circuit Designer

A C++17 digital logic circuit simulator built using object-oriented design.

## Scope

The project focuses on the core requirements of the digital electronics circuit designer:

- NAND and NOR as primitive gates
- NOT, AND, OR, XOR and XNOR built using gate composition
- Explicit connections between circuit elements
- Reusable `Circuit` abstraction
- Half Adder, Full Adder and configurable Ripple Carry Adder
- Circuit simulation
- `SimulationResult` abstraction
- Console and CSV output
- Automatic truth-table generation
- Automated tests

Multithreading, GUI support, Boolean-expression parsing, circuit serialization and other large extensions are intentionally outside the core implementation. This keeps the design small enough for a three-person course project while still demonstrating inheritance, composition, abstraction and reusable circuit construction.

## Build

```bash
cmake -S . -B build
cmake --build build
```

Run the application:

```bash
./build/digital_circuit_designer
```

Run tests:

```bash
ctest --test-dir build --output-on-failure
```

## Project structure

```text
DigitalCircuitDesigner/
├── include/
│   ├── core/          # CircuitElement, Gate, Connection, Circuit
│   ├── gates/         # NAND, NOR and derived gates
│   ├── circuits/      # Adders
│   ├── simulation/    # Simulator and SimulationResult
│   ├── output/        # Console and CSV output
│   └── analysis/      # Truth-table generation
├── src/               # Implementations
├── tests/              # Automated tests
├── data/outputs/       # Generated CSV files
├── docs/               # Report and UML
├── main.cpp            # Command-line demonstration
└── CMakeLists.txt      # Build configuration
```

## Design idea

`CircuitElement` is the common abstraction for gates and complete circuits. A `Circuit` owns smaller circuit elements and connects them using `Connection` objects. This allows a circuit to be built from smaller circuits, for example:

```text
NAND/NOR
   ↓
Derived gates
   ↓
Half Adder
   ↓
Full Adder
   ↓
Ripple Carry Adder
```

The simulator operates on a circuit and produces a `SimulationResult`. Output classes consume that result, so simulation is independent of presentation or file format.
