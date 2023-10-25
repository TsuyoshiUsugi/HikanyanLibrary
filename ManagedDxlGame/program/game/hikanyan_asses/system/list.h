#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
//MyListは、双方向リストの実装です。


template<typename T>
class my_list
{
private:
	//Nodeは、双方向リストのノードです。
	struct Node {
		T data;
		//次のノードへのポインタ
		Node* next;
		//前のノードへのポインタ
		Node* prev;
		//コンストラクタ
		Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
	};
	//先頭ノードへのポインタ
	Node* head = nullptr;
	//末尾ノードへのポインタ
	Node* tail = nullptr;

public:
	//イテレータとは、コンテナの要素に順番にアクセスするためのものです。
	my_list() : head(nullptr), tail(nullptr) {}
	//コンストラクタ
	~my_list() {
		clear();
	}

	// begin メソッドはリストの先頭を指すイテレータを返します。
	Node* begin() {
		return head;
	}

	// end メソッドはリストの末尾の次を指すイテレータを返します。
	Node* end() {
		return tail->next;
	}
	
	// push_backは、末尾に要素を追加します。
	void push_back(T element) {
		//新しいノードを作成します。
		Node* node = new Node(element);
		//先頭ノードがない場合
		if (head == nullptr) {
			head = node;
			tail = node;
		}
		//先頭ノードがある場合
		else {
			tail->next = node;
			node->prev = tail;
			tail = node;
		}
	}
	// pop_backは、末尾の要素を削除します。
	void push_front(T element) {
		//新しいノードを作成します。
		Node* node = new Node(element);
		//先頭ノードがない場合
		if (head == nullptr) {
			head = node;
			tail = node;
		}
		//先頭ノードがある場合
		else {
			node->next = head;
			head->prev = node;
			head = node;
		}
	}
	//eraseは、指定したインデックスの要素を削除します。
	void erase(int index) {
		//先頭ノードがない場合
		if (head == nullptr) return;
		//先頭ノードがある場合
		else if (index == 0) {
			//先頭ノードを削除します。
			Node* temp = head;
			//次のノードを先頭ノードにします。
			head = head->next;
			//次のノードがある場合
			if (head != nullptr) {
				head->prev = nullptr;
			}
			//次のノードがない場合
			else {
				tail = nullptr;
			}
			//ノードを削除します。
			delete temp;
		}
		//先頭ノードがある場合
		else {
			Node* current = head;
			int count = 0;
			//指定したインデックスのノードを検索します。
			while (current != nullptr && count < index) {
				current = current->next;
				count++;
			}
			//指定したインデックスのノードがある場合
			if (current != nullptr) {
				current->prev->next = current->next;
				//次のノードがある場合
				if (current->next != nullptr) {
					current->next->prev = current->prev;
				}
				//次のノードがない場合
				else {
					tail = current->prev;
				}
				delete current;
			}
		}
	}
	// clearは、全ての要素を削除します。
	void clear() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}
	// sortは、要素を昇順に並び替えます。
	void sort() {
		if (head == nullptr || head == tail)
			return; // リストが空または要素が1つの場合は何もしない

		bool swapped;
		Node* ptr1;
		Node* lptr = nullptr;

		do {
			swapped = false;
			ptr1 = head;

			while (ptr1->next != lptr) {
				if (ptr1->data > ptr1->next->data) {
					std::swap(ptr1->data, ptr1->next->data);
					swapped = true;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1;
		} while (swapped);
	}

	// size() メソッドはリスト内の要素数を返します。
	size_t size() const {
		size_t count = 0;
		Node* current = head;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	// operator[] をオーバーロードして、指定したインデックスの要素を取得します。
	T operator[](int index) const {
		if (index < 0 || index >= size()) {
			throw std::out_of_range("Index out of range");
		}

		Node* current = head;
		int count = 0;
		while (current != nullptr) {
			if (count == index) {
				return current->data;
			}
			current = current->next;
			count++;
		}

		// 通常ここには到達しないはずですが、念のため例外をスローします。
		throw std::out_of_range("Index out of range");
	}

	//displayListは、要素を表示します。
	void displayList() const {
		Node* current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
};
