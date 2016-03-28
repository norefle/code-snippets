#include "stack_queue.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <queue>

namespace {

template<typename T>
class Stack {
public:
    Stack();
    T pop();
    void push(T&& value);
    void push(const T& value);
    size_t size() const;
    bool empty() const;

private:
    bool useLeft_;
    std::queue<T> left_;
    std::queue<T> right_;
};

template<typename T>
Stack<T>::Stack() : useLeft_(true) {
}

template<typename T>
T Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Pop on empty stack");
    }
    auto& source = useLeft_ ? left_ : right_;
    auto& destination = useLeft_ ? right_ : left_;
    auto size = (source.size() - 1); // keep last element to pop
    for (decltype(size) i = 0; i < size; ++i) {
        destination.push(source.front());
        source.pop();
    }

    T result = source.front();

    source.pop();
    useLeft_ = !useLeft_;

    return std::move(result);
}

template<typename T>
void Stack<T>::push(T&& value) {
    auto& destination = useLeft_ ? left_ : right_;
    destination.push(std::forward<T>(value));
}

template<typename T>
void Stack<T>::push(const T& value) {
    auto& destination = useLeft_ ? left_ : right_;
    destination.push(value);
}

template<typename T>
size_t Stack<T>::size() const {
    return left_.size() + right_.size();
}

template<typename T>
bool Stack<T>::empty() const {
    return left_.empty() && right_.empty();
}

template<typename T>
class Queue {
public:
    Queue();
    T pop();
    void push(T&& value);
    void push(const T& value);
    bool empty() const;
    size_t size() const;
private:
    void reverse();
private:
    bool useLeft_;
    bool pushing_;
    std::stack<T> left_;
    std::stack<T> right_;
};

template<typename T>
Queue<T>::Queue()
    : useLeft_(true)
    , pushing_(true)
{
}

template<typename T>
void Queue<T>::reverse() {
    auto& source = useLeft_ ? left_ : right_;
    auto& destination = useLeft_ ? right_ : left_;
    while (!source.empty()) {
        destination.push(source.top());
        source.pop();
    }

    useLeft_ = !useLeft_;
    pushing_ = !pushing_;
}

template<typename T>
T Queue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Popping empty queue.");
    }

    if (pushing_) {
        reverse();
    }

    auto& source = useLeft_ ? left_ : right_;
    T result = source.top();
    source.pop();

    return result;
}

template<typename T>
void Queue<T>::push(const T &value) {
    if (!pushing_) {
        reverse();
    }

    auto& destination = useLeft_ ? left_ : right_;
    destination.push(value);
}

template<typename T>
void Queue<T>::push(T &&value) {
    if (!pushing_) {
        reverse();
    }

    auto& destination = useLeft_ ? left_ : right_;
    destination.push(std::forward<T>(value));
}

template<typename T>
bool Queue<T>::empty() const {
    return left_.empty() && right_.empty();
}

template<typename T>
size_t Queue<T>::size() const {
    return left_.size() + right_.size();
}

} // anonymous namesapce

namespace module {

std::string solveQueueAsStacks() {
    typedef std::queue<int> TOrigin;
    typedef Queue<int> TCustom;

    TOrigin origin;
    TCustom custom;

    std::stringstream out;

    auto checkPop = [&out, &origin, &custom](const std::string& msg) {
        out << msg
            << origin.front() << ", "
            << custom.pop() << std::endl;
        origin.pop();
    };

    out << "Inital origin == custom is "
        << std::boolalpha << (origin.size() == custom.size())
        << std::endl;

    for (auto& value: {1, 2, 3, 4, 5, 6, 7, 8, 9}) {
        origin.push(value);
        custom.push(value);
    }

    out << "Full origin == cursom is "
        << std::boolalpha << (origin.size() == custom.size())
        << std::endl;

    checkPop("Pop (origin, custom) = ");
    checkPop("Pop (origin, custom) = ");
    checkPop("Pop (origin, custom) = ");

    origin.push(10);
    custom.push(10);

    while(!origin.empty() && !custom.empty()) {
        checkPop("Pop (origin, custom) = ");
    }

    return out.str();
}

std::string solveStackAsQueues() {
    typedef std::stack<int> TOrigin;
    typedef Stack<int> TCustom;

    TOrigin origin;
    TCustom custom;

    std::stringstream out;

    auto checkPop = [&out, &origin, &custom](const std::string& msg) {
        out << msg
            << origin.top() << ", "
            << custom.pop() << std::endl;
        origin.pop();
    };

    out << "Inital origin == custom is "
        << std::boolalpha << (origin.size() == custom.size())
        << std::endl;

    for (auto& value: {1, 2, 3, 4, 5, 6, 8, 9, 10}) {
        origin.push(value);
        custom.push(value);
    }

    out << "Full origin == cursom is "
        << std::boolalpha << (origin.size() == custom.size())
        << std::endl;

    checkPop("Pop (origin, custom) = ");
    checkPop("Pop (origin, custom) = ");
    checkPop("Pop (origin, custom) = ");

    origin.push(7);
    custom.push(7);

    while(!origin.empty() && !custom.empty()) {
        checkPop("Pop (origin, custom) = ");
    }

    return out.str();
}

} // namespace module
