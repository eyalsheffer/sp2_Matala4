#pragma once
//#include "MyContainer.hpp"
#include <vector>
#include <algorithm>

namespace MyContainerNamespace {
    template<typename T>
    class MyContainer;

    template<typename T>
    class SideCrossOrder {
    private:
        const MyContainer<T>& container;
        std::vector<size_t> indices;
        size_t current_index;

    public:
        /**
         * @brief Constructor for the SideCrossOrder iterator.
         * @param cont Reference to the container.
         * @param pos The starting position (default is 0).
         */
        explicit SideCrossOrder(const MyContainer<T>& cont, size_t pos = 0)
            : container(cont), current_index(pos) {
            if (container.empty()) {
                return;
            }
            std::vector<size_t> sorted_indices(container.size());
            for (size_t i = 0; i < container.size(); ++i) {
                sorted_indices[i] = i;
            }
            
            std::sort(sorted_indices.begin(), sorted_indices.end(),
                [this](size_t a, size_t b) {
                    return container.getData()[a] < container.getData()[b];
                });

            size_t left = 0;
            size_t right = sorted_indices.size() - 1;
            bool take_left = true;

            while (left <= right) {
                if (take_left) {
                    indices.push_back(sorted_indices[left]);
                    ++left;
                } else {
                    indices.push_back(sorted_indices[right]);
                    if (right == 0) break;
                    --right;
                }
                take_left = !take_left;
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
        SideCrossOrder& operator++() {
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
        SideCrossOrder operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            SideCrossOrder temp = *this;
            ++current_index;
            return temp;
        }
        /**
         * @brief Equality operator.
         * @param other The other SideCrossOrder to compare with.
         * @return True if both iterators are equal, false otherwise.
         */
        bool operator==(const SideCrossOrder& other) const {
            return current_index == other.current_index && &container == &other.container;
        }
        /**
         * @brief Inequality operator.
         * @param other The other SideCrossOrder to compare with.
         * @return True if both iterators are not equal, false otherwise.
         */
        bool operator!=(const SideCrossOrder& other) const {
            return !(*this == other);
        }
    };

}