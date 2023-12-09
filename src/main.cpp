//Sorting Algorithms Demonstration Program, by Ethan Guttman.

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <cctype>

using std::cout, std::cin, std::vector, std::size_t, std::string;

void swap(std::vector<int>& vec, size_t pos1, size_t pos2);
vector<int> bubble_sort(vector<int>& dataset);
vector<int> efficient_bubble_sort(vector<int>& dataset);
vector<int> cocktail_shaker_sort(vector<int>& dataset);
vector<int> cocktail_shaker_sort_improved(vector<int>& dataset);
vector<int> insertion_sort(vector<int>& dataset);
vector<int> selection_sort(vector<int>& dataset);
void printSorts();
void printDatasets();
void printDataset(const vector<int>& dataset);
char getChar(const vector<char>&& options);
int getPosInt(const int upper);
int getInt();
void gen_rand_seq(vector<int>& vec, int lower, int upper);



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
            int seq_size = getPosInt(1'000'000);
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
            gen_rand_seq(dataset, lower, upper);
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
        char sort_option = getChar({'1', '2', '3', '4', '5', '6', '7', '8', '9', 'x'});
        cout << '\n';
        
        vector<int> sorted_seq = dataset;
        vector<int> sort_stats;


        switch(sort_option) {
            case 'x':
            running = false;
            break;
            case '1':
            sort_stats = bubble_sort(sorted_seq);
            break;

            case '2':
            sort_stats = efficient_bubble_sort(sorted_seq);
            break; 

            case '3':
            sort_stats = cocktail_shaker_sort(sorted_seq);
            break;

            case '4':
            sort_stats = cocktail_shaker_sort_improved(sorted_seq);
            break;

            case '5':
            sort_stats = insertion_sort(sorted_seq);
            break;

            case '6':
            sort_stats = selection_sort(sorted_seq);
            break;

            case '7':
            case '8':
            case '9':
            cout << "Option not implemented.\n";
        }

        if (sort_option != 'x' && int(sort_option - '0') < int('7'-'0')) {
            cout << "Comparisons: " << sort_stats[0] << '\n';
            cout << "Swaps: " << sort_stats[1] << '\n';
            cout << "Passes: " << sort_stats[2] << '\n';
        }

        printDataset(sorted_seq);

    } while (running);
}

void swap(std::vector<int>& vec, size_t pos1, size_t pos2) {
    int temp = vec[pos1];
    vec[pos1] = vec[pos2];
    vec[pos2] =  temp;
}

vector<int> bubble_sort(vector<int>& dataset) {
    cout << "Performing Bubble sort..." << '\n';
    size_t size = dataset.size();

    //Counters for information.
    int swaps = 0;
    int comparisons= 0;
    int passes = 0;

    for(size_t i = 0; i<size-1; ++i) {
        for(size_t j = 0; j<size-i-1; ++j) {
            if (dataset[j]>dataset[j+1]) {
                swap(dataset, j, j+1);
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
    }
    cout << "Sorted!\n";
    return {comparisons, swaps, passes};
}

vector<int> efficient_bubble_sort(vector<int>& dataset) {
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
                swap(dataset, j, j+1);
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
    return {comparisons, swaps, passes};

}

vector<int> cocktail_shaker_sort(vector<int>& dataset) {
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
                swap(dataset, i, i+1);
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
                swap(dataset, j, j-1);
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        ++start;
    }
    cout << "Sorted!\n";
    return {comparisons, swaps, passes};
}

vector<int> cocktail_shaker_sort_improved(vector<int>& dataset) {
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
                swap(dataset, i, i+1);
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
                swap(dataset, j, j-1);
                swap_performed = true;
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
        ++start;
    }
    cout << "Sorted!\n";
    return {comparisons, swaps, passes};
}


vector<int> insertion_sort(vector<int>& dataset) {
    cout << "Performing Insertion Sort..." << '\n';
    size_t size = dataset.size();

    //Counters for information.
    int swaps = 0;
    int comparisons = 0;
    int passes = 0;

    for(int i = 0; i<size; ++i) {
        for(int j = i-1; j>=0; j--) {
            if(dataset[j+1] < dataset[j]) {
                swap(dataset, j+1, j);
                ++swaps;
            }
            ++comparisons;
        }
        ++passes;
    }
    return {comparisons, swaps, passes};
}

vector<int> selection_sort(vector<int>& dataset) {
    cout << "Performing Selection Sort...";
    size_t size = dataset.size();

    //Counters for information.
    int swaps = 0;
    int comparisons = 0;
    int passes = 0;

    for(int i = 0; i<size; ++i) {
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
            swap(dataset, i, min_idx);
            ++swaps;
        }
        ++passes;
    }
    return {comparisons, swaps, passes};
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
    cout << "9 - Quick Sort\n";
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

void gen_rand_seq(vector<int>& vec, int lower, int upper) {
    //Create and generate seed for the rng generator (When first running function).
    static std::random_device rand_dev{};
    static std::mt19937 gen{rand_dev()};

    //Create distribution based on user set upper and lower.
    std::uniform_int_distribution int_distrib(lower, upper);

    //Fill vector with random numbers.
    std::generate(vec.begin(), vec.end(), [&]() {return int_distrib(gen);});

}
