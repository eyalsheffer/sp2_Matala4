#pragma once
//#include "MyContainer.hpp"
#include <vector>

namespace MyContainerNamespace {
    template<typename T>
    class MyContainer;

    template<typename T>
    class ReverseOrder {
    private:
        const MyContainer<T>& container;
        std::vector<size_t> indices;
        size_t current_index;

    public:
        /**
         * @brief Constructor for the ReverseOrder iterator.
         * @param cont Reference to the container.
         * @param pos The starting position (default is 0).
         */
        explicit ReverseOrder(const MyContainer<T>& cont, size_t pos = 0)
            : container(cont), current_index(pos) {
            if (container.empty()) {
                return;
            }
            indices.resize(container.size());
            for (size_t i = 0; i < container.size(); ++i) {
                indices[i] = container.size() - 1 - i;
            }
        }
        /**
         * @brief Access current element.
         * @return Reference to the current element.
         * @throw std::out_of_range If out of bounds
         */
        const T& operator*() const {
            if (current_index >= container.size()) {
                throw std::out_of_range("Iterator out of bounds");
            }
            return container.getData()[indices[current_index]];
        }
        /**
         * @brief Pre-increment operator. Advance to next position.
         * @return Reference after increment.
         * @throw std::out_of_range If incrementing past end
         */
        ReverseOrder& operator++() {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            ++current_index;
            return *this;
        }
        /**
         * @brief Post-increment operator. Advance to next position.
         * @return Copy of the iterator before increment.
         * @throw std::out_of_range If incrementing past end
         */
        ReverseOrder operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            ReverseOrder temp = *this;
            ++current_index;
            return temp;
        }
        /**
         * @brief Equality operator.
         * @param other The other ReverseOrder to compare with.
         * @return True if both iterators are equal, false otherwise.
         */
        bool operator==(const ReverseOrder& other) const {
            return current_index == other.current_index && &container == &other.container;
        }
        /**
         * @brief Inequality operator.
         * @param other The other ReverseOrder to compare with.
         * @return True if both iterators are not equal, false otherwise.
         */
        bool operator!=(const ReverseOrder& other) const {
            return !(*this == other);
        }
    };

}