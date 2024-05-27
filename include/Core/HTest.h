#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <stdexcept>
#include <map>

// Macro to define a test case
#define HT_TEST_CASE(name) static void name(); \
    static bool _##name##_registered = HTest::instance().addTest(#name, name); \
    static void name()

// Macro to check equality
#define HT_CHECK_EQUAL(actual, expected) do { if ((actual) != (expected)) { \
    std::cerr << "Test failed: " << __FILE__ << ":" << __LINE__ << ": " << #actual << " == " << #expected << std::endl; \
    throw std::runtime_error("Test failed: " + std::string(#actual) + " == " + std::string(#expected)); } } while (0)

// Macro to check a condition
#define HT_CHECK(condition) do { if (!(condition)) { \
    std::cerr << "Test failed: " << __FILE__ << ":" << __LINE__ << ": " << #condition << std::endl; \
    throw std::runtime_error("Test failed: " + std::string(#condition)); } } while (0)

class HTest {
public:
    static HTest& instance() {
        static HTest instance;
        return instance;
    }

    bool addTest(const std::string& name, std::function<void()> test) {
        tests_[name] = test;
        return true;
    }

    void run() {
        for (const auto& [name, test] : tests_) {
            std::cout << "Running test: " << name << std::endl;
            try {
                test();
                std::cout << "Test passed: " << name << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Test failed: " << name << " - " << e.what() << std::endl;
            }
        }
    }

private:
    std::map<std::string, std::function<void()>> tests_;
};

