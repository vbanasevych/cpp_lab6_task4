#include <iostream>
#include <queue>
#include "NumberGenerator.h"

int main() {
    std::queue<int> myQueue;

    NumberGenerator generator = create_sequence(myQueue);

    std::cout << "[Main] Starting generator...\n";
    generator.resume();

    int attempts = 1;
    const int max_attempts = 5;

    while (attempts <= max_attempts && !generator.done()) {

        if (!myQueue.empty()) {
            int last = myQueue.back();
            std::cout << "[Main] Paused. Last value: " << last;

            if (last % 2 != 0) {
                std::cout << " (ODD. Correct Suspension)\n";
            } else {
                std::cout << " (EVEN. Error!)\n";
            }
        }

        std::cout << "[Main] Resuming (Step " << attempts << ")...\n";
        generator.resume();
        attempts++;
    }

    std::cout << "Done. Total elements: " << myQueue.size() << "\n";

    return 0;
}