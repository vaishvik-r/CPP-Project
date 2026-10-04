#include "analysis/TruthTableGenerator.h"
#include "circuits/FullAdder.h"
#include "circuits/HalfAdder.h"
#include "circuits/RippleCarryAdder.h"
#include "output/CSVOutput.h"
#include "output/ConsoleOutput.h"
#include "simulation/Simulator.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace {

void printRippleSample(RippleCarryAdder& adder) {
    // Inputs are ordered as A bits, B bits, then carry-in.
    // Bit 0 is the least significant bit.
    const unsigned int a = 8;
    const unsigned int b = 4;

    for (std::size_t i = 0; i < adder.getBitWidth(); ++i) {
        adder.setInput(i, (a >> i) & 1U);
        adder.setInput(adder.getBitWidth() + i, (b >> i) & 1U);
    }
    adder.setInput(2 * adder.getBitWidth(), false);
    adder.evaluate();

    std::cout << "A = 1000, B = 0100, Cin = 0\n";
    std::cout << "Sum = ";
    for (std::size_t i = adder.getBitWidth(); i-- > 0;) {
        std::cout << adder.getOutput(i);
    }
    std::cout << ", Cout = " << adder.getOutput(adder.getBitWidth()) << "\n";
}

void exportResult(const SimulationResult& result) {
    std::filesystem::create_directories("data/outputs");

    CSVOutput output;
    const std::string path = "data/outputs/simulation.csv";
    output.write(result, path);

    std::cout << "CSV written to " << path << "\n";
}

void showResult(const SimulationResult& result) {
    ConsoleOutput output;
    output.write(result);
}

} // namespace

int main() {
    std::cout << "=== Digital Circuit Designer ===\n";
    std::cout << "NAND/NOR based digital circuit simulator\n";

    std::unique_ptr<Circuit> currentCircuit;
    SimulationResult currentResult;

    while (true) {
        std::cout << "\n1. Half Adder\n"
                  << "2. Full Adder\n"
                  << "3. 4-bit Ripple Carry Adder\n"
                  << "4. Simulate selected circuit\n"
                  << "5. Export simulation to CSV\n"
                  << "6. Exit\n"
                  << "> ";

        int choice;
        if (!(std::cin >> choice)) {
            return 0;
        }

        if (choice == 1) {
            currentCircuit = std::make_unique<HalfAdder>();
            std::cout << "Selected Half Adder.\n";
        } else if (choice == 2) {
            currentCircuit = std::make_unique<FullAdder>();
            std::cout << "Selected Full Adder.\n";
        } else if (choice == 3) {
            currentCircuit = std::make_unique<RippleCarryAdder>(4);
            std::cout << "Selected 4-bit Ripple Carry Adder.\n";
        } else if (choice == 4) {
            if (!currentCircuit) {
                std::cout << "Select a circuit first.\n";
                continue;
            }

            TruthTableGenerator generator;
            currentResult = generator.generate(*currentCircuit);

            if (currentCircuit->getInputCount() <= 3) {
                showResult(currentResult);
            } else {
                std::cout << "Generated " << currentResult.rowCount()
                          << " simulation rows.\n";

                auto* adder = dynamic_cast<RippleCarryAdder*>(currentCircuit.get());
                if (adder != nullptr) {
                    printRippleSample(*adder);
                }
            }
        } else if (choice == 5) {
            if (!currentCircuit || currentResult.rowCount() == 0) {
                std::cout << "Simulate a circuit first.\n";
                continue;
            }

            exportResult(currentResult);
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
