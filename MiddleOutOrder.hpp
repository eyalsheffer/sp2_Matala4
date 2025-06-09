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

        const T& operator*() const {
            if (current_index >= container.size()) {
                throw std::out_of_range("Iterator out of bounds");
            }
            return container.getData()[indices[current_index]];
        }

        MiddleOutOrder& operator++() {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            ++current_index;
            return *this;
        }

        MiddleOutOrder operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            MiddleOutOrder temp = *this;
            ++current_index;
            return temp;
        }

        bool operator==(const MiddleOutOrder& other) const {
            return current_index == other.current_index && &container == &other.container;
        }

        bool operator!=(const MiddleOutOrder& other) const {
            return !(*this == other);
        }
    };

}