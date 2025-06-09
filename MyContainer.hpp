#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <type_traits>
#include "AscendingOrder.hpp"
#include "DescendingOrder.hpp"
#include "SideCrossOrder.hpp"
#include "ReverseOrder.hpp"
#include "Order.hpp"
#include "MiddleOutOrder.hpp"


namespace MyContainerNamespace {

template<typename T = int>
class MyContainer {
private:
    std::vector<T> data;

public:
    MyContainer() = default;
    
    MyContainer(const MyContainer& other) : data(other.data) {}
    
    MyContainer& operator=(const MyContainer& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }
    
    ~MyContainer() = default;

    void add(const T& element) {
        data.push_back(element);
    }

    void remove(const T& element) {
        auto it = std::find(data.begin(), data.end(), element);
        if (it == data.end()) {
            throw std::invalid_argument("Element not found in container");
        }
        
        data.erase(std::remove(data.begin(), data.end(), element), data.end());
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const MyContainer& container) {
        os << "[";
        for (size_t i = 0; i < container.data.size(); ++i) {
            os << container.data[i];
            if (i < container.data.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    const std::vector<T>& getData() const {
        return data;
    }

    std::vector<T>& getData() {
        return data;
    }
        friend class AscendingOrder<T>;
        friend class DescendingOrder<T>;
        friend class SideCrossOrder<T>;
        friend class ReverseOrder<T>;
        friend class Order<T>;
        friend class MiddleOutOrder<T>;

        // Iterator accessors
        /**
         * @brief Returns an iterator to the beginning of the container in ascending order.
         * @return An iterator to the beginning of the container.
         */
        auto begin_ascending_order() const { 
            return AscendingOrder<T>(*this, 0); 
        }

        /**
         * @brief Returns an iterator to the end of the container in ascending order.
         * @return An iterator to the end of the container.
         */
        auto end_ascending_order() const { 
            return AscendingOrder<T>(*this, data.size()); 
        }

        /**
         * @brief Returns an iterator to the beginning of the container in descending order.
         * @return An iterator to the beginning of the container.
         */
        auto begin_descending_order() const { 
            return DescendingOrder<T>(*this, 0); 
        }

        /**
         * @brief Returns an iterator to the end of the container in descending order.
         * @return An iterator to the end of the container.
         */
        auto end_descending_order() const { 
            return DescendingOrder<T>(*this, data.size()); 
        }

        /**
         * @brief Returns an iterator to traverse the container in side-cross order.
         * @return An iterator for side-cross order traversal.
         */
        auto begin_side_cross_order() const { 
            return SideCrossOrder<T>(*this, 0); 
        }

        /**
         * @brief Returns an iterator to the end of the container in side-cross order.
         * @return An iterator to the end of the container.
         */
        auto end_side_cross_order() const { 
            return SideCrossOrder<T>(*this, data.size()); 
        }

        /**
         * @brief Returns an iterator to the beginning of the container in reverse order.
         * @return An iterator to the beginning of the container in reverse order.
         */
        auto begin_reverse_order() const { 
            return ReverseOrder<T>(*this, 0); 
        }

        /**
         * @brief Returns an iterator to the end of the container in reverse order.
         * @return An iterator to the end of the container in reverse order.
         */
        auto end_reverse_order() const { 
            return ReverseOrder<T>(*this, data.size()); 
        }

        /**
         * @brief Returns an iterator to the beginning of the container in insertion order.
         * @return An iterator to the beginning of the container in insertion order.
         */
        auto begin_order() const { 
            return Order<T>(*this, 0); 
        }

        /**
         * @brief Returns an iterator to the end of the container in insertion order.
         * @return An iterator to the end of the container in insertion order.
         */
        auto end_order() const { 
            return Order<T>(*this, data.size()); 
        }

        /**
         * @brief Returns an iterator to the beginning of the container in middle-out order.
         * @return An iterator to the beginning of the container in middle-out order.
         */
        auto begin_middle_out_order() const { 
            return MiddleOutOrder<T>(*this, 0); 
        }

        /**
         * @brief Returns an iterator to the end of the container in middle-out order.
         * @return An iterator to the end of the container in middle-out order.
         */
        auto end_middle_out_order() const { 
            return MiddleOutOrder<T>(*this, data.size()); 
        }
};

}