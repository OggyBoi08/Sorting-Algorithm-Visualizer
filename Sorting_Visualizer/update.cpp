#include "update.h"
#include <iostream>

void insertion_sort_step(SortState& state)
{
    int n = static_cast<int>(state.arr.size());

    if (state.i>=n)
    {
        state.finished = true;
        return;
    }

    if (state.j >= 0 && state.arr[state.j] > state.key)
    {
        state.arr[state.j + 1] = state.arr[state.j];
        state.j--;
    }
    else
    {
        state.arr[state.j + 1] = state.key;
        state.i++;

        if (state.i<n)
        {
            state.key = state.arr[state.i];
            state.j = state.i-1;
        }
        else
        {
            state.finished = true;
        }
    }

    state.sorted[std::min(n-1,state.i)]=true;
}

SortState CreateInsertionSortState(const std::vector<int>& arr)
{
    SortState state;

    state.arr = arr;
    state.i = 1;
    state.j = 0;
    state.key = arr[1];
    state.finished = false;
    state.sorted = std::vector<bool>(arr.size(), false);
    state.sorted[0]=true;
    state.sorted[1]=true;

    return state;
}

void bubble_sort_step(SortState& state)
{
    int n = static_cast<int>(state.arr.size());
    if (state.i>=n-1)
    {
        state.finished = true;
        return;
    }

    if (state.j<n-1-state.i)
    {
        if  (state.arr[state.j]>state.arr[state.j+1])
        {
            std::swap(state.arr[state.j], state.arr[state.j+1]);
            state.swapped = true;
        }
        state.j++;
    }
    else
    {
        if (!state.swapped)
        {
            state.finished = true;
        }
        state.i++;
        state.j=0;
    }

    state.sorted[std::min(n-1,n-state.i)] = true;
}

SortState CreateBubbleSortState(const std::vector<int>& arr)
{
    SortState state;

    state.arr = arr;
    state.i = 0;
    state.j = 0;
    state.finished = false;
    state.swapped = false;
    state.sorted = std::vector<bool>(arr.size(), false);

    return state;
}

void heap_sort_step(SortState& state)
{
    int n = static_cast<int>(state.arr.size());
    if (n <= 1) return; // Already sorted

    // ==========================================
    // Phase 1: Build Max Heap
    // ==========================================
    if (state.i >= 0)
    {
        int left = 2 * state.heap_index + 1;
        int right = 2 * state.heap_index + 2;
        int largest = state.heap_index;

        if (left < n && state.arr[left] > state.arr[largest])
            largest = left;
        if (right < n && state.arr[right] > state.arr[largest])
            largest = right;

        if (largest != state.heap_index)
        {
            std::swap(state.arr[state.heap_index], state.arr[largest]);
            state.heap_index = largest; // Continue sifting down on the next tick
        }
        else
        {
            state.i--; // Done sifting this node, move to the next
            state.heap_index = state.i; // When i becomes -1, heap_index becomes -1
        }
        return;
    }

    // ==========================================
    // Phase 2: Extract Max and Sort
    // ==========================================
    if (state.j > 0)
    {
        // A heap_index of -1 acts as a flag telling us it's time to swap
        // the max element (root) to its sorted position at the end.
        if (state.heap_index == -1)
        {
            std::swap(state.arr[0], state.arr[state.j]);
            state.heap_index = 0; // Set up to sift down the new root on the next tick
            return;
        }

        // Sift down the new root within the remaining unsorted heap
        int left = 2 * state.heap_index + 1;
        int right = 2 * state.heap_index + 2;
        int largest = state.heap_index;

        // Notice the boundary is 'state.j' now, not 'n', because everything
        // from index 'j' onwards is already sorted.
        if (left < state.j && state.arr[left] > state.arr[largest])
            largest = left;
        if (right < state.j && state.arr[right] > state.arr[largest])
            largest = right;

        if (largest != state.heap_index)
        {
            std::swap(state.arr[state.heap_index], state.arr[largest]);
            state.heap_index = largest; // Continue sifting down
        }
        else
        {
            state.j--; // Root is in the right place, shrink the active heap
            state.heap_index = -1; // Flag for a root-to-end swap next tick
        }
    }

    if (state.i<0 && state.j<=0)
    {
        state.finished = true;
    }

    state.sorted[std::min(n-1,state.j)]=true;
}

SortState CreateHeapSortState(const std::vector<int>& arr)
{
    SortState state;

    state.arr = arr;
    state.heap_index = (arr.size()/2)-1;
    state.i = (arr.size()/2)-1;
    state.j = arr.size()-1;
    state.finished = false;
    state.swapped = false;
    state.sorted = std::vector<bool>(arr.size(), false);

    return state;
}

void shell_sort_step(SortState& state)
{
    int n = static_cast<int>(state.arr.size());

    // Continue shifting elements backwards
    if (state.j >= 0 && state.arr[state.j] > state.key)
    {
        state.arr[state.j + state.gap] = state.arr[state.j];
        state.j -= state.gap;
    }
    else
    {
        // Put key into its correct position
        state.arr[state.j + state.gap] = state.key;

        // Move to the next element
        state.i += state.gap;

        if (state.i < n)
        {
            // Start insertion of the next element
            state.key = state.arr[state.i];
            state.j = state.i - state.gap;
        }
        else
        {
            // Current gap is completely sorted
            state.gap /= 2;

            if (state.gap > 0)
            {
                // Start a new gapped insertion sort
                state.i = state.gap;
                state.key = state.arr[state.i];
                state.j = state.i - state.gap;
            }
            else
            {
                state.finished = true;
            }
        }
    }

    if (state.gap==1)
        state.sorted[std::min(n-1,state.i)]=true;
}

SortState CreateShellSortState(const std::vector<int>& arr)
{
    SortState state;

    state.arr = arr;
    state.gap = static_cast<int>(arr.size())/2;
    state.i = state.gap;
    state.j = state.i - state.gap;
    state.key = state.arr[state.i];
    state.finished = false;
    state.sorted = std::vector<bool>(arr.size(), false);

    return state;
}

