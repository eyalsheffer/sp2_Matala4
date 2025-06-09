#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace MyContainerNamespace {

    template<typename T>
    class MyContainer;

    template<typename T>
    class AscendingOrder {
    private:
        const MyContainer<T>& container; // Reference to the container being iterated
        std::vector<size_t> indices; // Indices of elements in ascending order
        size_t current_index; 

    public:
        /**
         * @brief Constructor for the AscendingOrder.
         * @param cont Reference to the container.
         * @param pos The starting position (default is 0).
         */
        explicit AscendingOrder(const MyContainer<T>& cont, size_t pos = 0)
            : container(cont), current_index(pos) {
            indices.resize(container.size());
            for (size_t i = 0; i < container.size(); ++i) {
                indices[i] = i;
            }
            std::sort(indices.begin(), indices.end(),
                [this](size_t a, size_t b) {
                    return container.getData()[a] < container.getData()[b];
                });
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
         * @brief Advance to next position.
         * @return Reference after increment.
         * @throw std::out_of_range If incrementing past end
         */
        AscendingOrder& operator++() {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            ++current_index;
            return *this;
        }

        /**
         * @brief Advance to next position.
         * @return Copy before increment.
         * @throw std::out_of_range If incrementing past end
         */
        AscendingOrder operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            AscendingOrder temp = *this;
            ++current_index;
            return temp;
        }

        /**
         * @brief Compare equality.
         * @param other Another iterator.
         * @return True if same position and container.
         */
        bool operator==(const AscendingOrder& other) const {
            return current_index == other.current_index && &container == &other.container;
        }

        /**
         * @brief Compare inequality.
         * @param other Another iterator.
         * @return True if different position or container.
         */
        bool operator!=(const AscendingOrder& other) const {
            return !(*this == other);
        }
    };
}