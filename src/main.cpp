//Sorting Algorithms Demonstration Program, by Ethan Guttman.

#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <random>
#include <string>
#include <cctype>

using std::cout, std::cin, std::vector, std::map, std::size_t, std::string;

map<string, int> bubble_sort(vector<int>& dataset);
map<string, int> efficient_bubble_sort(vector<int>& dataset);
map<string, int> cocktail_shaker_sort(vector<int>& dataset);
map<string, int> cocktail_shaker_sort_improved(vector<int>& dataset);
map<string, int> insertion_sort(vector<int>& dataset);
map<string, int> selection_sort(vector<int>& dataset);
map<string, int> shell_sort(vector<int>& dataset);
void merge(vector<int> &dataset, int start, int mid, int end, int& comparisons, int& writes);
void mergeSort(vector<int> &dataset, int start, int end, int& merges, int& comparisons, int& writes);

void printSorts();
void printDatasets();
void printDataset(const vector<int>& dataset);
char getChar(const vector<char>&& options);
int getPosInt(const int upper);
int getInt();
void gen_rand_set(vector<int>& vec, int lower, int upper);



int main() {
    bool running = true;
    cout << "Welcome to the Sorting Algorithms Demonstration Program, by Ethan Guttman!" << "\n\n";
    vector<int> dataset{};
    do {
        printDatasets();
        if (!dataset.empty())
            cout << "4 - Resuse last dataset\n";

        char data_option = getChar({'1', '2', '3', '4'});
        cin.ignore(1000, '\n');

        if (data_option != '4') {
            cout << "Now, enter what you would like your dataset size to be.\n";
            int seq_size = getPosInt(100'000);
            dataset.resize(seq_size);
        }

        switch(data_option) {
            //Random
            case '1':
            {
            bool valid = false;
            int lower;
            int upper;
            cout << "Enter the range of integers you wish to generate:\n";
            do {
                lower = getInt();
                upper = getInt();
                if (lower <= upper) 
                    valid = true;
                else
                    cout << "Range is not valid.\n";
            } while(!valid);
            gen_rand_set(dataset, lower, upper);
            break;
            }
            case '2':
            std::generate(dataset.begin(), dataset.end(), [n=0]() mutable {return ++n;});
            break;

            case  '3':
            std::generate(dataset.begin(), dataset.end(), [n=dataset.size()]() mutable {return --n;});
            break;

            case '4':
            if (dataset.empty()) {
                cout << "Invalid option. \n\n";
            }
            break;

            default:
            throw std::runtime_error("Invalid DataOption.\n");
        }

        cout << "Sequence to be sorted: " << '\n';
        printDataset(dataset);
        printSorts();
        char sort_option = getChar({'1', '2', '3', '4', '5', '6', '7', '8', '9', 'x', 'a'});
        cout << '\n';
        
        vector<int> sorted_set = dataset;
        vector<map<string, int>> sort_stats;


        switch(sort_option) {
            case 'x':
            running = false;
            break;

            case 'a':
            sort_stats.push_back(bubble_sort(sorted_set));
            sorted_set = dataset;
            sort_stats.push_back(efficient_bubble_sort(sorted_set));
            sorted_set = dataset;
            sort_stats.push_back(cocktail_shaker_sort(sorted_set));
            sorted_set = dataset;
            sort_stats.push_back(cocktail_shaker_sort_improved(sorted_set));
            sorted_set = dataset;
            sort_stats.push_back(insertion_sort(sorted_set));
            sorted_set = dataset;
            sort_stats.push_back(selection_sort(sorted_set));
            sorted_set = dataset;
            sort_stats.push_back(shell_sort(sorted_set));
            sorted_set = dataset;
            {
                map<string, int> merge_sort_stats = {{"Merges", 0}, {"Comparisons", 0}, {"Writes", 0}};
                mergeSort(sorted_set, 0, sorted_set.size()-1, merge_sort_stats["Merges"], merge_sort_stats["Comparisons"], merge_sort_stats["Writes"]);
                sort_stats.push_back(merge_sort_stats);
            }
            break;

            case '1':
            sort_stats.push_back(bubble_sort(sorted_set));
            break;

            case '2':
            sort_stats.push_back(efficient_bubble_sort(sorted_set));
            break; 

            case '3':
            sort_stats.push_back(cocktail_shaker_sort(sorted_set));
            break;

            case '4':
            sort_stats.push_back(cocktail_shaker_sort_improved(sorted_set));
            break;

            case '5':
            sort_stats.push_back(insertion_sort(sorted_set));
            break;

            case '6':
            sort_stats.push_back(selection_sort(sorted_set));
            break;

            case '7':
            sort_stats.push_back(shell_sort(sorted_set));
            break;
            case '8':
            {
            map<string, int> merge_sort_stats = {{"Merges", 0}, {"Comparisons", 0}, {"Writes", 0}};
            mergeSort(sorted_set, 0, sorted_set.size()-1, merge_sort_stats["Merges"], merge_sort_stats["Comparisons"], merge_sort_stats["Writes"]);
            sort_stats.push_back(merge_sort_stats);
            }
        }

        if (sort_option != 'x' && sort_option != 'c') {
            for (auto stat_set : sort_stats) {
                for (auto stat_pair : stat_set) {
                    cout << stat_pair.first << ": " << stat_pair.second << '\n';
                }
                cout << '\n';
            }
        }

        printDataset(sorted_set);

    } while (running);
}

map<string, int> bubble_sort(vector<int>& dataset) {
    cout << "Performing Bubble sort..." << '\n';
    size_t size = dataset.size();

    //Counters for information.
    int swaps = 0;
    int comparisons= 0;
    int passes = 0;

    for(size_t i = 0; i<size-1; ++i) {
        for(size_t j = 0; j<size-i-1; ++j) {
            if (dataset[j]>dataset[j+1]) {
                std::swap(dataset[j], dataset[j+1]);
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
    }
    cout << "Sorted!\n";
    return {{"Comparisons", comparisons}, {"Swaps", swaps}, {"Passes", passes}} ;
}

map<string, int> efficient_bubble_sort(vector<int>& dataset) {
    cout << "Performing Bubble sort (improved)..." << '\n';
    size_t size = dataset.size();

    //Counters for information.
    int swaps = 0;
    int comparisons= 0;
    int passes = 0;

    for(size_t i = 0; i<size-1; ++i) {
        bool swap_performed = false;
        for(size_t j = 0; j<size-i-1; ++j) {
            if (dataset[j]>dataset[j+1]) {
                std::swap(dataset[j], dataset[j+1]);
                swap_performed = true;
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        if (!swap_performed)
            break;
    }
    cout << "Sorted!\n";
    return {{"Comparisons", comparisons}, {"Swaps", swaps}, {"Passes", passes}} ;

}

map<string, int> cocktail_shaker_sort(vector<int>& dataset) {
    cout << "Performing Cocktail-Shaker sort..." << '\n';
    size_t size = dataset.size();
    bool swap_performed = true;

    //Counters for information.
    int swaps = 0;
    int comparisons= 0;
    int passes = 0;

    int start = 0;
    int end = size - 1;

    while (start!=end) {
        for(int i = start; i != end; ++i) {
            if (dataset[i] > dataset[i+1]) {
                std::swap(dataset[i], dataset[i+1]);
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        --end;
        if (start == end)
            break;
            
        for(int j = end; j != start; --j) {
            if (dataset[j] < dataset[j-1]) {
                std::swap(dataset[j], dataset[j-1]);
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        ++start;
    }
    cout << "Sorted!\n";
    return {{"Comparisons", comparisons}, {"Swaps", swaps}, {"Passes", passes}};
}

map<string, int> cocktail_shaker_sort_improved(vector<int>& dataset) {
    cout << "Performing Cocktail-Shaker sort..." << '\n';
    size_t size = dataset.size();
    bool swap_performed = true;

    //Counters for information.
    int swaps = 0;
    int comparisons= 0;
    int passes = 0;

    int start = 0;
    int end = size - 1;

    while (start!=end || swap_performed) {
        swap_performed = false;
        for(int i = start; i != end; ++i) {
            if (dataset[i] > dataset[i+1]) {
                std::swap(dataset[i], dataset[i+1]);
                swap_performed = true;
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        --end;
        if (!swap_performed || start == end)
            break;
        swap_performed = false;
        for(int j = end; j != start; --j) {
            if (dataset[j] < dataset[j-1]) {
                std::swap(dataset[j], dataset[j-1]);
                swap_performed = true;
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        ++start;
    }
    cout << "Sorted!\n";
    return {{"Comparisons", comparisons}, {"Swaps", swaps}, {"Passes", passes}};
}


map<string, int> insertion_sort(vector<int>& dataset) {
    cout << "Performing Insertion Sort..." << '\n';
    size_t size = dataset.size();

    //Counters for information.
    int swaps = 0;
    int comparisons = 0;
    int passes = 0;
    for(int i = 1; i<size; ++i) {
        for(int j = i-1; j>=0; j--) {
            ++comparisons;
            if(dataset[j+1] < dataset[j]) {
                std::swap(dataset[j], dataset[j+1]);
                ++swaps;
            }
            else 
                break;
            
        }
        ++passes;
    }
    cout << "Sorted!\n";
    return {{"Comparisons", comparisons}, {"Swaps", swaps}, {"Passes", passes}};
}

map<string, int> selection_sort(vector<int>& dataset) {
    cout << "Performing Selection Sort...";
    size_t size = dataset.size();

    //Counters for information.
    int swaps = 0;
    int comparisons = 0;
    int passes = 0;

    for(int i = 0; i<size-1; ++i) {
        int min_idx = i;
        int min_val = dataset[i];
        for(int j = i+1; j<size; ++j) {
            int current_val = dataset[j];
            if(current_val < min_val) {
                min_val = current_val;
                min_idx = j;
            }
            ++comparisons;
        }
        if (min_idx != i) {
            std::swap(dataset[i], dataset[min_idx]);
            ++swaps;
        }
        ++passes;
    }
    cout << "Sorted!\n";
    return {{"Comparisons", comparisons}, {"Swaps", swaps}, {"Passes", passes}};
}

map<string, int> shell_sort(vector<int>& dataset) {
    cout << "Performing Insertion Sort..." << '\n';
    int size = dataset.size();
    int swaps = 0;
    int comparisons = 0;
    int passes = 0;

    for(int gap_size = size/2; gap_size > 0; gap_size /= 2) {
        for(int i = gap_size; i < size; ++i) {
            for(int j = i; j >= gap_size; j -= gap_size) {
                ++comparisons;
                if (dataset[j-gap_size] > dataset[j]) {
                    std::swap(dataset[j], dataset[j-gap_size]);
                    ++swaps;
                }
                else
                    break;
            }
            ++passes;
        }
    }
    cout << "Sorted!" << '\n';
    return {{"Comparisons", comparisons}, {"Swaps", swaps}, {"Passes", passes}};
}

#include <iostream>
#include <vector>

//CREDIT TO: big-o.io/examples/merge-sort/c++/
void merge(vector<int> &dataset, int start, int mid, int end, int& comparisons, int& writes) {
    vector<int> left(mid - start + 1);
    vector<int> right(end - mid);

    int i = 0, j = 0;
    int k = start;
    
    // fill in left array
    for (int i = 0; i < left.size(); ++i)
        left[i] = dataset[start + i];

    // fill in right array
    for (int i = 0; i < right.size(); ++i)
        right[i] = dataset[mid + 1 + i];

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            dataset[k] = left[i];
            i++;
        } else {
            dataset[k] = right[j];
            j++;
        }
        ++comparisons;
        ++writes;
        k++;
    }
    while (i < left.size()) {
        dataset[k++] = left[i++];
        ++writes;
    }
    while (j < right.size()) {
        dataset[k++] = right[j++];
        ++writes;
    }
}

void mergeSort(vector<int> &dataset, int start, int end, int& merges, int& comparisons, int& writes) {
    if (start < end) {
        int mid = start + (end - start) / 2;

        mergeSort(dataset, start, mid, merges, comparisons, writes);
        mergeSort(dataset, mid + 1, end, merges, comparisons, writes);
        merge(dataset, start, mid, end, comparisons, writes);
        ++merges;
    }
}

void printDataset(const vector<int>& dataset) {
    for (int val : dataset) {
        cout <<  val << ' ';
    }
    cout << '\n';
}

void printSorts() {
    cout << "Select a Sort:\n\n";
    cout << "1 - Bubble Sort\n";
    cout << "2 - Bubble Sort (improved)\n";
    cout << "3 - Cocktail Shaker Sort\n";
    cout << "4 - Cocktail Shaker Sort (improved)\n";
    cout << "5 - Insertion Sort\n";
    cout << "6 - Selection Sort\n";
    cout << "7 - Shell Short\n";
    cout << "8 - Merge Sort\n";
    cout << "a - Run all.\n";
    cout << "x - Exit Program\n";
}

void printDatasets() {
    cout << "Select the type of data you want:\n\n";
    cout << "1 - Random Data\n";
    cout << "2 - Best Case (already sorted)\n";
    cout << "3 - Worst Case (reversed sequence)\n";
}

char getChar(const vector<char>&& options) {
    
    char input;
    bool valid = false;
    do {
        cout << "Select an option listed: ";
        cin >> input;
        for (char c : options) {
            if (input == c) {
                valid = true;
            };
        }
        if (!valid)
            cout << "Invalid option selected.\n";
    }
    while (!valid);
    return input;
}

int getPosInt(const int upper) {
    string input;
    bool valid;
    int ret_val;
    do {
        valid = true;
        cout << "Enter a natural number up to " << upper << ": ";
        getline(cin, input);
        ret_val = std::stoi(input);
        if(ret_val > upper || ret_val < 1) {
            valid = false;
            cout << "You entered an invald integer." << '\n';
        }
    }
    while (!valid);
    return ret_val;
}

int getInt() {
    string input;
    cout << "Enter an integer: ";
    getline(cin, input);
    return std::stoi(input);
}

void gen_rand_set(vector<int>& vec, int lower, int upper) {
    //Create and generate seed for the rng generator (When first running function).
    static std::random_device rand_dev{};
    static std::mt19937 gen{rand_dev()};

    //Create distribution based on user set upper and lower.
    std::uniform_int_distribution int_distrib(lower, upper);

    //Fill vector with random numbers.
    std::generate(vec.begin(), vec.end(), [&]() {return int_distrib(gen);});
}
