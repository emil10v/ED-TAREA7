#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;


template <typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}
	void insert(E element) {
		current->next = current->next->previous =
			new DNode<E>(element, current->next, current);
	}
	void append(E element) {
		tail->previous = tail->previous->next =
			new DNode<E>(element, tail, tail->previous);
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		DNode<E>* temp = current->next;
		E result = temp->element;
		current->next = temp->next;
		temp->next->previous = current;
		delete temp;
		size--;
		return result;

	}
	void clear() {
		current = head->next;
		while (current != tail) {
			head->next = current->next;
			delete current;
			current = head->next;
		}
		size = 0;
		current = head;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail->previous;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds. ");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head)
			current = current->previous;
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current == tail;
	}
	int getPos() {
		DNode<E>* temp = head;
		int res = 0;
		while (temp != current) {
			res++;
			temp = temp->next;
		}
		return res;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[";
		DNode<E>* temp = head->next;
		while (temp != tail) {
			cout << temp->element;
			if (temp->next != tail)
				cout << ", ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};