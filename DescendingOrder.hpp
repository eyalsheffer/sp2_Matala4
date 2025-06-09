#pragma once
//#include "MyContainer.hpp"
#include <vector>
#include <algorithm>

namespace MyContainerNamespace {

    template<typename T>
    class MyContainer;

   template<typename T>
class DescendingOrder {
    private:
        const MyContainer<T>& container;
        std::vector<size_t> indices;
        size_t current_index;

    public:
        explicit DescendingOrder(const MyContainer<T>& cont, size_t pos = 0)
            : container(cont), current_index(pos) {
            indices.resize(container.size());
            for (size_t i = 0; i < container.size(); ++i) {
                indices[i] = i;
            }
            std::sort(indices.begin(), indices.end(),
                [this](size_t a, size_t b) {
                    return container.getData()[a] > container.getData()[b];
                });
        }

        const T& operator*() const {
            if (current_index >= container.size()) {
                throw std::out_of_range("Iterator out of bounds");
            }
            return container.getData()[indices[current_index]];
        }

        DescendingOrder& operator++() {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            ++current_index;
            return *this;
        }

        DescendingOrder operator++(int) {
            if (current_index >= container.size()) {
                throw std::out_of_range("Cannot increment iterator past end");
            }
            DescendingOrder temp = *this;
            ++current_index;
            return temp;
        }

        bool operator==(const DescendingOrder& other) const {
            return current_index == other.current_index && &container == &other.container;
        }

        bool operator!=(const DescendingOrder& other) const {
            return !(*this == other);
        }

    };

}