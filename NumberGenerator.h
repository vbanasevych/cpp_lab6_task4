#pragma once
#include <coroutine>
#include <queue>
#include <exception>

struct NumberGenerator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    handle_type coro_handle;

    NumberGenerator(handle_type h) : coro_handle(h) {}

    ~NumberGenerator() {
        if (coro_handle) coro_handle.destroy();
    }

    NumberGenerator(const NumberGenerator&) = delete;
    NumberGenerator& operator=(const NumberGenerator&) = delete;

    NumberGenerator(NumberGenerator&& other) noexcept : coro_handle(other.coro_handle) {
        other.coro_handle = nullptr;
    }

    void resume() {
        if (coro_handle && !coro_handle.done()) {
            coro_handle.resume();
        }
    }

    bool done() const {
        return !coro_handle || coro_handle.done();
    }

    struct SuspendIfOdd {
        int value;

        bool await_ready() const noexcept {
            return (value % 2 == 0);
        }

        void await_suspend(std::coroutine_handle<>) const noexcept {}
        void await_resume() const noexcept {}
    };

    struct promise_type {
        NumberGenerator get_return_object() {
            return NumberGenerator{handle_type::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void return_void() {}
        void unhandled_exception() { std::terminate(); }

        SuspendIfOdd await_transform(int value) {
            return SuspendIfOdd{value};
        }
    };
};

NumberGenerator create_sequence(std::queue<int>& target_queue);