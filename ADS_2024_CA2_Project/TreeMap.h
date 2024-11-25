#pragma once
#include "BinaryTree.h"
#include <stdexcept>
#include <iostream>

template <class K, class V>
struct KeyValuePair {
    K key;
    V value;

    bool operator<(const KeyValuePair& other) const {
        return key < other.key;
    }
    bool operator>(const KeyValuePair& other) const {
        return key > other.key;
    }
    bool operator==(const KeyValuePair& other) const {
        return key == other.key;
    }

    friend std::ostream& operator<<(std::ostream& os, const KeyValuePair& kvp) {
        os << "(" << kvp.key << ", " << kvp.value << ")";
        return os;
    }
};

template <class K, class V>
class TreeMap {
private:
    BinaryTree<KeyValuePair<K, V>> tree;
    void collectKeys(BSTNode<KeyValuePair<K, V>>* node, BinaryTree<K>& keysTree) const;
public:
    TreeMap();
    void clear();
    bool containsKey(const K& key) const;
    V& get(const K& key);
    V* getPointer(const K& key);
    void put(const K& key, const V& value);
    int size() const;
    bool removeKey(const K& key);
    V& operator[](const K& key);
    BinaryTree<K> keySet() const;
};

template <class K, class V>
TreeMap<K, V>::TreeMap() {
   
}

template <class K, class V>
void TreeMap<K, V>::clear() {
    tree.clear();
}

template <class K, class V>
bool TreeMap<K, V>::containsKey(const K& key) const {
    KeyValuePair<K, V> kvp;
    kvp.key = key;
    return tree.containsKey(kvp);
}

template <class K, class V>
V& TreeMap<K, V>::get(const K& key) {
    KeyValuePair<K, V> kvp;
    kvp.key = key;
    KeyValuePair<K, V>& found = tree.get(kvp);
    return found.value;
}

template <class K, class V>
V* TreeMap<K, V>::getPointer(const K& key) {
    KeyValuePair<K, V> kvp;
    kvp.key = key;
    try {
        KeyValuePair<K, V>& found = tree.get(kvp);
        return &(found.value);
    }
    catch (const std::logic_error&) {
        return nullptr;
    }
}

template <class K, class V>
void TreeMap<K, V>::put(const K& key, const V& value) {
    KeyValuePair<K, V> kvp;
    kvp.key = key;
    kvp.value = value;

    if (tree.containsKey(kvp)) {
        tree.remove(kvp);
    }
    tree.add(kvp);
}

template <class K, class V>
int TreeMap<K, V>::size() const {
    return tree.count();
}

template <class K, class V>
bool TreeMap<K, V>::removeKey(const K& key) {
    KeyValuePair<K, V> kvp;
    kvp.key = key;
    return tree.remove(kvp);
}

template <class K, class V>
V& TreeMap<K, V>::operator[](const K& key) {
    KeyValuePair<K, V> kvp;
    kvp.key = key;
    try {
        KeyValuePair<K, V>& found = tree.get(kvp);
        return found.value;
    }
    catch (const std::logic_error&) {
        kvp.value = V();
        tree.add(kvp);
        return tree.get(kvp).value;
    }
}

template <class K, class V>
void TreeMap<K, V>::collectKeys(BSTNode<KeyValuePair<K, V>>* node, BinaryTree<K>& keysTree) const {
    if (node != nullptr) {
        collectKeys(node->getLeft(), keysTree);
        keysTree.add(node->getItem().key);
        collectKeys(node->getRight(), keysTree);
    }
}

template <class K, class V>
BinaryTree<K> TreeMap<K, V>::keySet() const {
    BinaryTree<K> keysTree;
    collectKeys(tree.root, keysTree);
    return keysTree;
}