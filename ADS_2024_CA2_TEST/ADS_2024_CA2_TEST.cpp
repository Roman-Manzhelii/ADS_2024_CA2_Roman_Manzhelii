#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2024_CA2_Project/TreeMap.h"
#include <string>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ADS2024CA2TEST
{
    TEST_CLASS(TreeMapTests)
    {
    public:

        TEST_METHOD(TestPutAndGet)
        {
            TreeMap<int, std::string> map;
            map.put(1, "one");
            map.put(2, "two");
            map.put(3, "three");

            Assert::AreEqual(std::string("one"), map.get(1));
            Assert::AreEqual(std::string("two"), map.get(2));
            Assert::AreEqual(std::string("three"), map.get(3));
        }

        TEST_METHOD(TestContainsKey)
        {
            TreeMap<int, std::string> map;
            map.put(1, "one");
            map.put(2, "two");

            Assert::IsTrue(map.containsKey(1));
            Assert::IsTrue(map.containsKey(2));
            Assert::IsFalse(map.containsKey(3));
        }

        TEST_METHOD(TestRemoveKey)
        {
            TreeMap<int, std::string> map;
            map.put(1, "one");
            map.put(2, "two");

            Assert::IsTrue(map.containsKey(1));
            map.removeKey(1);
            Assert::IsFalse(map.containsKey(1));
        }

        TEST_METHOD(TestSize)
        {
            TreeMap<int, std::string> map;
            Assert::AreEqual(0, map.size());

            map.put(1, "one");
            Assert::AreEqual(1, map.size());

            map.put(2, "two");
            Assert::AreEqual(2, map.size());

            map.removeKey(1);
            Assert::AreEqual(1, map.size());
        }

        TEST_METHOD(TestClear)
        {
            TreeMap<int, std::string> map;
            map.put(1, "one");
            map.put(2, "two");
            map.put(3, "three");

            map.clear();
            Assert::AreEqual(0, map.size());
            Assert::IsFalse(map.containsKey(1));
            Assert::IsFalse(map.containsKey(2));
            Assert::IsFalse(map.containsKey(3));
        }

        TEST_METHOD(TestOperatorIndex)
        {
            TreeMap<int, std::string> map;
            map[1] = "one";
            map[2] = "two";

            Assert::AreEqual(std::string("one"), map.get(1));
            Assert::AreEqual(std::string("two"), map.get(2));

            map[1] = "ONE";
            Assert::AreEqual(std::string("ONE"), map.get(1));
        }

        TEST_METHOD(TestGetNonExistentKey)
        {
            TreeMap<int, std::string> map;
            auto func = [&]() { map.get(99); };

            Assert::ExpectException<std::logic_error>(func, L"Expected std::logic_error to be thrown.");
        }

        TEST_METHOD(TestKeySet)
        {
            TreeMap<int, std::string> map;
            map.put(5, "five");
            map.put(3, "three");
            map.put(7, "seven");

            BinaryTree<int> keys = map.keySet();
            std::vector<int> keysVector;

            //https://stackoverflow.com/questions/72463355/what-exactly-is-stdfunctionvoidint-doing-in-this-code
            std::function<void(BSTNode<int>*)> collectKeys;

            // Define the lambda function
            collectKeys = [&](BSTNode<int>* node) {
                if (node != nullptr) {
                    collectKeys(node->getLeft());
                    keysVector.push_back(node->getItem());
                    collectKeys(node->getRight());
                }
                };

            collectKeys(keys.root);
            std::vector<int> expectedKeys = { 3, 5, 7 };

            Assert::AreEqual(expectedKeys.size(), keysVector.size(), L"Key count does not match.");

            for (size_t i = 0; i < expectedKeys.size(); ++i) {
                Assert::AreEqual(expectedKeys[i], keysVector[i], L"Keys do not match.");
            }
        }
    };
}