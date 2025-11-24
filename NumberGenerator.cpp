#include "NumberGenerator.h"
#include <random>
#include <iostream>

NumberGenerator create_sequence(std::queue<int>& target_queue) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 256);

    std::cout << "[Generator] Coroutine started.\n";

    while (true) {
        int number = dist(gen);

        target_queue.push(number);
        std::cout << " Generated: " << number << "\n";

        co_await number;
    }
}