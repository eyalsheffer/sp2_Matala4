#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../MyContainer.hpp"

using namespace MyContainerNamespace;

TEST_CASE("MyContainer basic operations") {
    MyContainer<int> c;
    CHECK(c.empty());
    c.add(1);
    c.add(2);
    c.add(3);
    CHECK(c.size() == 3);
    CHECK(c[0] == 1);
    CHECK(c[2] == 3);
    c.remove(2);
    CHECK(c.size() == 2);
    CHECK_THROWS_AS(c.remove(42), std::invalid_argument);
    CHECK_THROWS_AS(c[10], std::out_of_range);
}

TEST_CASE("AscendingOrder iterator - int") {
    MyContainer<int> c;
    c.add(5); c.add(1); c.add(3); c.add(2); c.add(4);
    std::vector<int> expected = {1,2,3,4,5};
    std::vector<int> result;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("DescendingOrder iterator - int") {
    MyContainer<int> c;
    c.add(5); c.add(1); c.add(3); c.add(2); c.add(4);
    std::vector<int> expected = {5,4,3,2,1};
    std::vector<int> result;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("SideCrossOrder iterator - int") {
    MyContainer<int> c;
    c.add(1); c.add(2); c.add(3); c.add(4); c.add(5);
    std::vector<int> expected = {1,5,2,4,3};
    std::vector<int> result;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("ReverseOrder iterator - int") {
    MyContainer<int> c;
    c.add(1); c.add(2); c.add(3);
    std::vector<int> expected = {3,2,1};
    std::vector<int> result;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("Order iterator - int (insertion order)") {
    MyContainer<int> c;
    c.add(10); c.add(20); c.add(30);
    std::vector<int> expected = {10,20,30};
    std::vector<int> result;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("MiddleOutOrder iterator - int") {
    MyContainer<int> c;
    c.add(1); c.add(2); c.add(3); c.add(4); c.add(5);
    std::vector<int> expected = {3,2,4,1,5};
    std::vector<int> result;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("Iterators on empty container") {
    MyContainer<int> c;
    CHECK(c.begin_ascending_order() == c.end_ascending_order());
    CHECK(c.begin_descending_order() == c.end_descending_order());
    CHECK(c.begin_side_cross_order() == c.end_side_cross_order());
    CHECK(c.begin_reverse_order() == c.end_reverse_order());
    CHECK(c.begin_order() == c.end_order());
    CHECK(c.begin_middle_out_order() == c.end_middle_out_order());
}

TEST_CASE("Iterators on single element container") {
    MyContainer<int> c;
    c.add(42);
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(*it == 42);
    }
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
        CHECK(*it == 42);
    }
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        CHECK(*it == 42);
    }
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
        CHECK(*it == 42);
    }
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        CHECK(*it == 42);
    }
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        CHECK(*it == 42);
    }
}

TEST_CASE("Iterators with duplicate values") {
    MyContainer<int> c;
    c.add(2); c.add(1); c.add(2); c.add(1);
    std::vector<int> asc, desc;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
        asc.push_back(*it);
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it)
        desc.push_back(*it);
    CHECK(asc.front() == 1);
    CHECK(asc.back() == 2);
    CHECK(desc.front() == 2);
    CHECK(desc.back() == 1);
}

TEST_CASE("Iterators on strings") {
    MyContainer<std::string> c;
    c.add("baboon"); c.add("arie"); c.add("pil");
    std::vector<std::string> expected_asc = {"arie", "baboon", "pil"};
    std::vector<std::string> expected_desc = {"pil", "baboon", "arie"};
    std::vector<std::string> asc, desc;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
        asc.push_back(*it);
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it)
        desc.push_back(*it);
    CHECK(asc == expected_asc);
    CHECK(desc == expected_desc);
}

TEST_CASE("Iterator throws on out of bounds") {
    MyContainer<int> c;
    c.add(1); c.add(2);
    auto it = c.begin_ascending_order();
    ++it; ++it;
    CHECK_THROWS_AS(*it, std::out_of_range);
    CHECK_THROWS_AS(++it, std::out_of_range);
    CHECK_THROWS_AS(it++, std::out_of_range);
}


TEST_CASE("AscendingOrder iterator - double") {
    MyContainer<double> c;
    c.add(3.1); c.add(2.2); c.add(5.5); c.add(-1.0);
    std::vector<double> expected = {-1.0, 2.2, 3.1, 5.5};
    std::vector<double> result;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("DescendingOrder iterator - double") {
    MyContainer<double> c;
    c.add(3.1); c.add(2.2); c.add(5.5); c.add(-1.0);
    std::vector<double> expected = {5.5, 3.1, 2.2, -1.0};
    std::vector<double> result;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("SideCrossOrder iterator - double") {
    MyContainer<double> c;
    c.add(1.1); c.add(2.2); c.add(3.3); c.add(4.4); c.add(5.5);
    std::vector<double> expected = {1.1, 5.5, 2.2, 4.4, 3.3};
    std::vector<double> result;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("ReverseOrder iterator - double") {
    MyContainer<double> c;
    c.add(1.1); c.add(2.2); c.add(3.3);
    std::vector<double> expected = {3.3, 2.2, 1.1};
    std::vector<double> result;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("Order iterator - double (insertion order)") {
    MyContainer<double> c;
    c.add(10.1); c.add(20.2); c.add(30.3);
    std::vector<double> expected = {10.1, 20.2, 30.3};
    std::vector<double> result;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("MiddleOutOrder iterator - double") {
    MyContainer<double> c;
    c.add(1.1); c.add(2.2); c.add(3.3); c.add(4.4); c.add(5.5);
    std::vector<double> expected = {3.3, 2.2, 4.4, 1.1, 5.5};
    std::vector<double> result;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("SideCrossOrder iterator - string") {
    MyContainer<std::string> c;
    c.add("b"); c.add("a"); c.add("c"); c.add("d");
    std::vector<std::string> expected = {"a", "d", "b", "c"};
    std::vector<std::string> result;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("ReverseOrder iterator - string") {
    MyContainer<std::string> c;
    c.add("first"); c.add("second"); c.add("third");
    std::vector<std::string> expected = {"third", "second", "first"};
    std::vector<std::string> result;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("Order iterator - string (insertion order)") {
    MyContainer<std::string> c;
    c.add("x"); c.add("y"); c.add("z");
    std::vector<std::string> expected = {"x", "y", "z"};
    std::vector<std::string> result;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}

TEST_CASE("MiddleOutOrder iterator - string") {
    MyContainer<std::string> c;
    c.add("a"); c.add("b"); c.add("c"); c.add("d"); c.add("e");
    std::vector<std::string> expected = {"c", "b", "d", "a", "e"};
    std::vector<std::string> result;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        result.push_back(*it);
    }
    CHECK(result == expected);
}