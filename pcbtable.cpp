/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author ??? (Joel Burlingame)
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   // TODO: add your code here
   this->tableSize = size;
   tableMain.reserve(size);
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // TODO: add your code here
   // Delete all the PCBs in the table
    for(int i = 0; i < this->tableSize; i++){
        delete tableMain[i];
    }
    tableMain.clear();
   }

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    // TODO: add your code here
    if(idx < tableMain.size() && tableMain[idx] != nullptr){
        return tableMain[idx];
    }
    cout << "Nullptr out of bounds" << endl;
    return nullptr;
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // TODO: add your code here
    // Add a PCB pointer to the PCBTable at index idx.
    if(idx > static_cast<unsigned int>(tableSize)){
        cout << "cannot add at " + idx << endl;
        return;
    }
    if (idx < static_cast<unsigned int>(tableSize)) {
            // Make sure the vector is large enough to accommodate the index
            if (tableMain.size() <= idx) {
                tableMain.resize(idx + 1, nullptr);  // Resize the vector to hold the index
            }
            tableMain[idx] = pcb;  // Assign the PCB at the specified index
        }

}
