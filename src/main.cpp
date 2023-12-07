#include "sorts.h"
#include <vector>
#include <iostream>

using std::cout, std::vector;

void swap(std::vector<int>& vec, size_t pos1, size_t pos2) {
    int temp = vec[pos1];
    vec[pos1] = vec[pos2];
    vec[pos2] =  temp;
}

vector<int> bubble_sort(const vector<int>& dataset) {
    cout << "Performing Bubble sort (w/o redundant passes)..." << '\n';
    vector<int> sorted_vec(dataset);
    size_t size = sorted_vec.size();

    //Counters for information.
    int swaps = 0;
    int comparisons = 0;
    int passes = 0;
    for(size_t i{0}; i<size-1; ++i) {
        bool swap_performed = false;
        for(size_t j{0}; j<size-i-1; ++j) {
            if (sorted_vec[j]>sorted_vec[j+1]) {
                swap(sorted_vec, j, j+1);
                swap_performed = true;
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        if (!swap_performed)
            break;
    }
    return sorted_vec;
}

vector<int> insertion_sort(const vector<int>& dataset) {
    vector<int> sorted_vec(dataset);
    size_t size = sorted_vec.size();

    int swaps = 0;
    int comparisons = 0;
    int passes = 0;

    for(int i{1}; i<size; ++i) {
        for(int j{i-1}; j>=0; j--) {
            if(sorted_vec[j+1] < sorted_vec[j]) {
                swap(sorted_vec, j+1, j);
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
    }
    return sorted_vec;
}

vector<int> selection_sort(const vector<int>& dataset) {
    vector<int> sorted_vec(dataset);
    size_t size = sorted_vec.size();

    int swaps = 0;
    int comparisons = 0;
    int passes = 0;

    for(int i{0}; i<size; ++i) {
        int min_idx = i;
        int min_val = sorted_vec[i];
        for(int j{i+1}; j<size; ++j) {
            int current_val = sorted_vec[j];
            if(current_val < min_val) {
                min_val = current_val;
                min_idx = j;
            }
            ++comparisons;
        }
        if (min_idx != i) {
            swap(sorted_vec, i, min_idx);
        }
        ++passes;
    }
    return sorted_vec;
}

void printSeq(const vector<int>& seq) {
    for (int val : seq) {
        cout <<  val << ' ';
    }
    cout << '\n';
}
int main() {
    //Performing a bubble sort
    vector<int> array_of_nums = {6,5,4,3,2,1};
    vector<int> b_sorted_array = bubble_sort(array_of_nums);
    printSeq(b_sorted_array);
    vector<int> i_sorted_array = insertion_sort(array_of_nums);
    printSeq(i_sorted_array);
    vector<int> s_sorted_array = selection_sort(array_of_nums);
    printSeq(s_sorted_array);
    return 0;
}