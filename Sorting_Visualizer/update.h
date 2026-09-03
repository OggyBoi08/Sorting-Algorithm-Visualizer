#ifndef UPDATE_H
#define UPDATE_H

#include <vector>
#include "render.h"
#include "string.h"

struct SortState
{
    std::vector<int> arr;
    int i;
    int j;
    int heap_index;
    int key;
    int gap;
    bool swapped;
    std::vector<bool> sorted;
    bool finished;
};

void insertion_sort_step(SortState& state);
SortState CreateInsertionSortState(const std::vector<int>& arr);

void bubble_sort_step(SortState& state);
SortState CreateBubbleSortState(const std::vector<int>& arr);

void heap_sort_step(SortState& state);
SortState CreateHeapSortState(const std::vector<int>& arr);

void shell_sort_step(SortState& state);
SortState CreateShellSortState(const std::vector<int>& arr);

#endif // UPDATE_H
