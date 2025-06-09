#pragma once
//#include "MyContainer.hpp"
#include <vector>

namespace MyContainerNamespace {
    template<typename T>
    class MyContainer;
    
    template<typename T>
    class Order {
    private:
        const MyContainer<T>& container;
        size_t current_index;

    public:
        explicit Order(const MyContainer<T>& cont, size_t pos = 0)
            : container(cont), current_index(pos) {}

        const T& operator*() const {
            if (current_index >= container.size()) {
                throw std::out_of_range("Iterator out of bounds");
            }
            return container.getData()[current_index];
        }

        Order& operator++() {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            ++current_index;
            return *this;
        }

        Order operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            Order temp = *this;
            ++current_index;
            return temp;
        }

        bool operator==(const Order& other) const {
            return current_index == other.current_index && &container == &other.container;
        }

        bool operator!=(const Order& other) const {
            return !(*this == other);
    }
    };

}