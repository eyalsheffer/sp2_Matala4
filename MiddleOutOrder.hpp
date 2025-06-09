#pragma once
//#include "MyContainer.hpp"
#include <vector>

namespace MyContainerNamespace {
    template<typename T>
    class MyContainer;
    template<typename T>
class MiddleOutOrder {
    private:
        const MyContainer<T>& container;
        std::vector<size_t> indices;
        size_t current_index;

    public:
        /**
         * @brief Constructor for the MiddleOutOrder iterator.
         * @param cont Reference to the container.
         * @param pos The starting position (default is 0).
         */
        explicit MiddleOutOrder(const MyContainer<T>& cont, size_t pos = 0)
            : container(cont), current_index(pos) {
                
            if (container.empty()) {
                return;
            }

            size_t size = container.size();
            size_t middle = size / 2;
            indices.push_back(middle);

            size_t left = middle;
            size_t right = middle + 1;
            bool take_left = true;

            while (left > 0 || right < size) {
                if (take_left && left > 0) {
                    --left;
                    indices.push_back(left);
                } else if (!take_left && right < size) {
                    indices.push_back(right);
                    ++right;
                }

                if (left == 0) {
                    take_left = false;
                } else if (right >= size) {
                    take_left = true;
                } else {
                    take_left = !take_left;
                }
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
        MiddleOutOrder& operator++() {
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
        MiddleOutOrder operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            MiddleOutOrder temp = *this;
            ++current_index;
            return temp;
        }
        /**
         * @brief Equality operator.
         * @param other The other iterator to compare with.
         * @return True if both iterators are equal, false otherwise.
         */
        bool operator==(const MiddleOutOrder& other) const {
            return current_index == other.current_index && &container == &other.container;
        }
        /**
         * @brief Inequality operator.
         * @param other The other iterator to compare with.
         * @return True if both iterators are not equal, false otherwise.
         */
        bool operator!=(const MiddleOutOrder& other) const {
            return !(*this == other);
        }
    };

}