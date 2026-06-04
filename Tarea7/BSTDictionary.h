#pragma once
#include <stdexcept>
#include <iostream>
#include "Dictionary.h"
#include "BSTree.h"
#include "Pair.h"
#include "List.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename K, typename V>
class BSTDictionary : public Dictionary <K, V> {
private:
	BSTree <Pair<K, V>>* pairs;

public:
	BSTDictionary() {
		pairs = new BSTree <Pair<K, V>>();
	}
	~BSTDictionary() {
		delete pairs;
	}

	void insert(K key, V value) {
		Pair <K, V> p(key, value);
		pairs->insert(p);
	}
	V remove(K key) {
		Pair<K, V> p(key, V());
		Pair<K, V> result = pairs->remove(p);
		return result.value;
	}
	V getValue(K key) {
		Pair<K, V> search(key, V());
		Pair<K, V> result = pairs->find(search);
		return result.value;
	}
	void setValue(K key, V value) {
		remove(key);
		insert(key, value);
	}

	bool contains(K key) {
		Pair<K, V> p(key, V());
		return pairs->contains(p);
	}

	bool isEmpty() {
		return pairs->isEmpty();
	}

	void clear() {
		pairs->clear();
	}
	List<K>* getKeys() {
		List<Pair<K, V>>* elements = pairs->getElements();
		List<K>* keys = new ArrayList<K>(elements->getSize());
		for (elements->goToStart(); !elements->atEnd(); elements->next()) {
			keys->append(elements->getElement().key);
		}
		delete elements;
		return keys;
	}
	List<V>* getValues() {
		List<Pair<K, V>>* elements = pairs->getElements();
		List<V>* values = new ArrayList<V>(elements->getSize());
		for (elements->goToStart(); !elements->atEnd(); elements->next()) {
			values->append(elements->getElement().value);
		}
		delete elements
		return values;
	}

	int getSize() {
		return pairs->getSize();
	}

	void update(Dictionary<K, V>* D) {
		List<K>* keys = D->getKeys();
			for (keys->goToStart(); !keys->atEnd(); keys->next()) {
				K key = keys->getElement();
				V value = D->getValue(key);
				if (contains(key))
					setValue(key, value);
				else
					insert(key, value);
			}
		delete keys;
	}
	

	void zip(List<K>*keys, List<V>*values) {
		keys->goToStart();
		values->goToStart();
		while (!keys->atEnd() && !values->atEnd()) {
			K key = keys->getElement();
			V value = values->getElement();
			if (contains(key))
				setValue(key, value);
			else
				insert(key, value);
			keys->next();
			values->next();
		}
	}

	void print() {
		pairs->print();
	}
};


