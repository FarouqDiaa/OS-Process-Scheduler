#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma once
#include "../Clock/headers.h"

typedef struct MemoryBlock {
    int start;
    int end;
    int size;
    int processId;
    bool isEmpty;
    int split;
    struct MemoryBlock* left;
    struct MemoryBlock* right;
    struct MemoryBlock* parent;
} MemoryBlock;

MemoryBlock* createMemoryBlock(int start, int size, MemoryBlock* myParent) {
    MemoryBlock* memBlock = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    memBlock->start = start;
    memBlock->end = start + size-1;
    memBlock->size = size;
    memBlock->split = 0;
    memBlock->processId = -1;
    memBlock->isEmpty = true;
    memBlock->left = NULL;
    memBlock->right = NULL;
    memBlock->parent = myParent;
    //printf("new memory block created - start : %d  end : %d\n", memBlock->start, memBlock->end);
    return memBlock;
}

bool addProcess(MemoryBlock* memBlock, process* process) {
    if (memBlock == NULL || memBlock->isEmpty == false || memBlock->size < process->memorySize) {
        return false;
    }
    if (memBlock->size == process->memorySize && memBlock->split == 0) {
        memBlock->processId = process->id;
        memBlock->isEmpty = false;
        MemoryBlock* temp = memBlock->parent;
        while (temp){
            temp->split += 1;
            temp = temp->parent;
        }
        int currentTime = getClk();
        printf("\nAt time %d allocated %d bytes for process %d from %d to %d\n",currentTime , process->memorySize, process->id, memBlock->start, memBlock->end);
        return true;
    }
    int newSize = memBlock->size / 2;
    if(process->memorySize > newSize && memBlock->split == 0){
        memBlock->processId = process->id;
        memBlock->isEmpty = false;
        MemoryBlock* temp = memBlock->parent;
        while (temp){
            temp->split += 1;
            temp = temp->parent;
        }
        int currentTime = getClk();
        printf("\nAt time %d allocated %d bytes for process %d from %d to %d\n",currentTime , process->memorySize, process->id, memBlock->start, memBlock->end);
        return true;
    }
    if (memBlock->left == NULL && memBlock->right == NULL) {
        memBlock->left = createMemoryBlock(memBlock->start, newSize, memBlock);
        memBlock->right = createMemoryBlock(memBlock->start + newSize, newSize, memBlock);
    }
    if(addProcess(memBlock->left, process)){
        return true;
    }else if(addProcess(memBlock->right, process)){
        return true;
    }
    return false;
}

void updateMemory(MemoryBlock* memBlock, process* process, int* flag) {
    if (memBlock == NULL || *flag == 1) return;
    if (memBlock->processId == process->id) {
        memBlock->processId = -1;
        memBlock->isEmpty = true;
        printf("\nAt time %d freed %d bytes from process %d from: %d to %d\n", getClk(), process->memorySize, process->id, memBlock->start, memBlock->end);
        *flag = 1;
        MemoryBlock* currentBlock = memBlock;
        while (currentBlock->parent != NULL) {
            currentBlock->parent->split -= 1;
            currentBlock = currentBlock->parent;
        }
        return;
    }
    updateMemory(memBlock->left, process, flag);
    updateMemory(memBlock->right, process, flag);
}

void freeAllMemory(MemoryBlock* memBlock) {
    if (memBlock == NULL) return;
    freeAllMemory(memBlock->left);
    freeAllMemory(memBlock->right);
    free(memBlock);
}
