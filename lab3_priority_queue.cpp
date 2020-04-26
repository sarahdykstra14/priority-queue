#include "lab3_priority_queue.hpp"
#include <iostream>
#include <cmath>

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	capacity = n_capacity;
	heap = new TaskItem*[capacity+1]();
	size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for(int i = 0; i < capacity; i++){
		delete heap[i];
		heap[i] = NULL;
	}
	delete [] heap;
	size = 0;
	capacity = 0;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if(size == 0) return true;
	return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for(int i = 1; i <= size; i++){
		if(heap[i])
			cout << "Priority: " << heap[i]->priority << endl << "Description: " << heap[i]->description << endl;
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if(size == 0)
		return TaskItem(-1, "NULL");
	return *heap[1];
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if(size > capacity - 1)
		return false;
	++size;
	heap[size] = new TaskItem(val.priority, val.description);
	int final_index = PriorityQueue::addToQueue(size);
	if(final_index % 2 == 0 && heap[final_index] < heap[final_index + 1]){
		TaskItem *placeholder = heap[final_index];
		heap[final_index] = heap[final_index + 1];
		heap[final_index + 1] = placeholder;
	}
	else if(final_index != 1 && final_index % 2 == 1 && heap[final_index] > heap[final_index - 1]){
		TaskItem *placeholder = heap[final_index];
		heap[final_index] = heap[final_index - 1];
		heap[final_index - 1] = placeholder;
	}
	return true;
}

int PriorityQueue::addToQueue(int index){
	int parent = floor(index / 2);
	if(index == 1 || heap[index]->priority < heap[parent]->priority) return index;
	TaskItem *placeholder = heap[index];
	heap[index] = heap[parent];
	heap[parent] = placeholder;
	return PriorityQueue::addToQueue(parent);
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if(size == 0)
		return false;
	int empty = PriorityQueue::removeFromQueue(1);
	if(empty % 2 == 0 && size > empty){
		heap[empty] = heap[empty + 1];
	}
	--size;
	return true;
}

int PriorityQueue::removeFromQueue(int index){
	int lchild = index * 2;
	int rchild = index * 2 + 1;
	if(lchild > size) return index;
	if(lchild == size){
		heap[index] = heap[lchild];
		heap[lchild] = NULL;
		return lchild;
	}
	else if(heap[lchild]->priority > heap[rchild]->priority){
		heap[index] = heap[lchild];
		heap[lchild] = NULL;
		return removeFromQueue(lchild);
	}
	else{
		heap[index] = heap[rchild];
		heap[rchild] = NULL;
		return removeFromQueue(rchild);
	}
}
