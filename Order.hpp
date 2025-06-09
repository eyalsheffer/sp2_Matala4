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
        /**
         * @brief Constructor for the Order iterator.
         * @param cont Reference to the container.
         * @param pos The starting position (default is 0).
         */
        explicit Order(const MyContainer<T>& cont, size_t pos = 0)
            : container(cont), current_index(pos) {}

        /**
         * @brief Dereference operator. Access current element.
         * @return Reference to the current element.
         * @throw std::out_of_range If out of bounds.
         */
        const T& operator*() const {
            if (current_index >= container.size()) {
                throw std::out_of_range("Iterator out of bounds");
            }
            return container.getData()[current_index];
        }
        /**
         * @brief Pre-increment operator. Advance to next position.
         * @return Reference after increment.
         * @throw std::out_of_range If incrementing past end.
         */
        Order& operator++() {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            ++current_index;
            return *this;
        }
        /**
         * @brief Post-increment operator. Advance to next position.
         * @return Copy before increment.
         * @throw std::out_of_range If incrementing past end.
         */
        Order operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            Order temp = *this;
            ++current_index;
            return temp;
        }
         /**
         * @brief Equality comparison operator.
         * @param other Another iterator.
         * @return True if same position and container.
         */
        bool operator==(const Order& other) const {
            return current_index == other.current_index && &container == &other.container;
        }
        /**
         * @brief Inequality comparison operator.
         * @param other Another iterator.
         * @return True if different position or container.
         */
        bool operator!=(const Order& other) const {
            return !(*this == other);
    }
    };

}