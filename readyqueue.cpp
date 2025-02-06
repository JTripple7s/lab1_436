#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code

/**
 * @brief Constructor for the ReadyQueue class.
 */
ReadyQueue::ReadyQueue() {
    count = 0;
    capacity = 100; // keep the heap small so that runtime increases, resize for more space
    PCBheap = new PCB * [capacity];
}

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    for(int i = 0; i < count; i++){
        delete PCBheap[i];
    }
    delete[] PCBheap;
}

void ReadyQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (PCBheap[parent]->priority >= PCBheap[index]->priority)
            break;
        swap(PCBheap[parent], PCBheap[index]);
        index = parent;
    }
}

void ReadyQueue::heapifyDown(int index) {
    while (2 * index + 1 < count) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = left;
        if (right < count && PCBheap[right]->priority > PCBheap[left]->priority)
            largest = right;
        if (PCBheap[index]->priority >= PCBheap[largest]->priority)
            break;
        swap(PCBheap[index], PCBheap[largest]);
        index = largest;
    }
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB* pcbPtr) {
    if (pcbPtr == nullptr) {
        cout << "error: PCB pointer null" << endl;
        return;
    }
    if(count >= capacity){
        resize();
    }

    pcbPtr->setState(ProcState::READY);
    PCBheap[count] = pcbPtr;
    heapifyUp(count);
    count++;
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    if (count == 0) {
        cout << "error: readyQueue is empty" << endl;
        return nullptr;
    }

    PCB* highest = PCBheap[0];
    if (highest == nullptr) {
        cout << "Error: The PCB at index 0 is null!" << endl;
        return nullptr;
    }

    highest->setState(ProcState::RUNNING);
    PCBheap[0] = PCBheap[--count];
    heapifyDown(0);
    return highest;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return this->count;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    for (int i = 0; i < count; i++) {
        PCBheap[i]->display();
    }
}

void ReadyQueue::resize(){
    capacity *= 2; // double the size of heap if needed
    PCB** newHeap = new PCB * [capacity];

    for (int i = 0; i < count; i++) {
        newHeap[i] = PCBheap[i];
    }
    delete[] PCBheap;
    PCBheap = newHeap;
}