//
// Created by egor on 11/4/22.
//

#pragma once

#include <coroutine>
#include <utility>
#include <iostream>
#include <memory>




template <typename T>
class Generator {
public:
    class promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
public:
    explicit Generator(handle_type h): m_handle(new handle_type(h), [](auto p) {
        p->destroy();
    }) {}
    Generator(Generator& generator): m_handle(generator.m_handle), m_value(generator.m_value) {}
    Generator(Generator&& generator) noexcept: m_handle(std::move(generator.m_handle)), m_value(generator.m_value) {
    }
    ~Generator() = default;

public:
    class promise_type {
    public:
        std::suspend_always initial_suspend() { return {};}
        std::suspend_never final_suspend() noexcept { return {};}
        Generator get_return_object() {return Generator(handle_type::from_promise(*this));}
        void unhandled_exception() {}
        std::suspend_always yield_value(T const newValue) { value = newValue; return{};}
        void return_value(T v) {
            value = v;}
    public:
        T value;
    };

public:
    bool next();
    T getValue();


private:
    T m_value;
    std::shared_ptr<handle_type> m_handle;
};

template <typename T>
bool Generator<T>::next() {
    m_handle->resume();
    return not(m_handle->done());
}

template<typename T>
T Generator<T>::getValue() {
    return m_handle->promise().value;
}
