#pragma once
#include <stdexcept>
#include "DlinkedList.h"
#include "BSTNode.h"

using std::runtime_error;

template<typename E>
class BSTree {
private:
	BSTNode<E>* root;
	int size;

	BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return new BSTNode<E>(element);
		if (current->element == element)
			throw runtime_error("Elemento duplicado");
		if (element < current->element)
			current->left = insertAux(current->left, element);
		else
			current->right = insertAux(current->right, element);
		return current;
	}
	E findAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			throw runtime_error("Elemento no encontrado.");
		if (current->element == element)
			return current->element;
		if (element < current->element)
			return findAux(current->left, element);
		else
			return findAux(current->right, element);
	}
	BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Elemento no encontrado.");
		if (element < current->element) {
			current->left = removeAux(current->left, element, result);
			return current;
		}
		if (element > current->element) {
			current->right = removeAux(current->right, element, result);
			return current;
		}
		*result = current->element;
		if (current->childrenCount() == 0) {
			delete current;
			return nullptr;
		}
		if (current->childrenCount() == 1) {
			BSTNode<E>* child = current->onlyChild();
			delete current;
			return child;
		}
		BSTNode<E>* succesor = getSuccesor(current);
		swap(succesor, current);
		current->right = removeAux(current->right, element, result);
		return current;
	}
	BSTNode<E>* getSuccesor(BSTNode<E>* current) {
		BSTNode<E>* succesor = current->right;
		while (succesor->left != nullptr) {
			succesor = succesor->left;
		}
		return succesor;
	}

	void swap(BSTNode<E>* n1, BSTNode<E>* n2) {
		E temp = n1->element;
		n1->element = n2->element;
		n2->element = temp;
	}
	void clearAux(BSTNode<E>* current) {
		if (current == nullptr)
			return;
		clearAux(current->left);
		clearAux(current->right);
		delete current;
	}
	void getElementsAux(BSTNode<E>* current, List<E>* elements) {
		if (current == nullptr)
			return;
		getElementsAux(current->left, elements);
		elements->append(current->element);
		getElementsAux(current->right, elements);
	}
	void printAux(BSTNode<E>* current) {
		if (current == nullptr)
			return;
		cout << "[" << current > element << ", ";
		printAux(current->left);
		cout << ", "
			printAux(current->right);
		cout << "]";
	}

public:
	BSTree() {
		root = nullptr;
		size = 0;
	}
	~BSTree() {
		clear();
	}
	void insert(E element) {
		root = insertAux(root, element);
		size++;
	}
	E find(E element) {
		BSTNode<E>* current = root;
		while (current != nullptr) {
			if (current->element == element)
				return current->element;
			if (current->element > element)
				current = current->left;
			else
				current = current->right;
		}
		throw runtime_error("Elemento no encontrado.");
	}
	E remove(E element) {
		E result;
		root = removeAux(root, element, &result);
		size--;
		return result;
	}
	bool contains(E element) {
		BSTNode<E>* current = root;
		while (current != nullptr) {
			if (current->element == element)
				return true;
			if (current->element > element)
				current = current->left;
			else
				current = current->right;
		}
		return false;
	}
	void clear() {
		clearAux(root);
		root = nullptr;
		size = 0;
	}
	List<E>* getElements() {
		List<E>* elements = new DLinkedList<E>;
		getElementsAux(root, elements);
		return elements;
	}
	int getSize() {
		return size;
	}
	bool isEmpty() {
		return (size == 0);
	}
	void print() {
		printAux(root);
	}



};
