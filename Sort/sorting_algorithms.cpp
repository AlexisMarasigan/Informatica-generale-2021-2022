#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <queue>
#include <chrono>

// Function that creates a vector of random double numbers.
std::vector<double> random_vector(int);
// Implementation of the selection sort algorithm.
std::vector<double> selection_sort(std::vector<double>);
// Implementation of the heap sort algorithm.
std::vector<double> heap_sort(std::vector<double>);
// Implementation of the quick sort algoritm
void quick_sort(std::vector<double>&,int,int);
// Partizione e posizione del pivot
int partition(std::vector<double>&,int,int);


int main() {
    int n;
    std::cout << "Inserire la dimensione del vettore N = ";
    std::cin >> n;
    std::vector<double> v = random_vector(n);
    auto start_selec = std::chrono::steady_clock::now();
    std::vector<double> v_ord_selec = selection_sort(v);
    auto end_selec = std::chrono::steady_clock::now();
    auto diff_selec = end_selec - start_selec;
    std::cout << "Running Time Selection Sort: " << std::chrono::duration <double, std::milli> (diff_selec).count() << std::endl;
    auto start_heap = std::chrono::steady_clock::now();
    std::vector<double> v_ord_heap = heap_sort(v);
    auto end_heap = std::chrono::steady_clock::now();
    auto diff_heap = end_heap - start_heap;
    std::cout << "Running Time Heap Sort: " << std::chrono::duration <double, std::milli> (diff_heap).count() << std::endl;
    std::vector<double> v_ord_quick;
    quick_sort(v_ord_quick,0,n-1);
    
    for (const auto& x: v_ord_selec)
        std::cout << x << ' ';
    std::cout << std::endl;
    for (const auto& x: v_ord_heap)
        std::cout << x << ' ';
    std::cout << std::endl;
    
    return 0;
}

/**
 * Generating a vector of double numbers sampled iid uar in [0,1].
 * 
 * @param n size of the vector to generate.
 * @return vector of random numbers.
 */
std::vector<double> random_vector(int n) {
    int seed = 19;  // Change this to change the random numbers
    auto gen {std::default_random_engine(seed)}; // Generator
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    std::vector<double> random_values;
    for (int i=0; i<n; i++)
        random_values.push_back(uniform(gen));
    return random_values;
} 

/**
 * Sorting a vector with the selection sort algorithm.
 * 
 * @param v vector of doubles to order.
 * @return ordered vector.
 */
std::vector<double> selection_sort(std::vector<double> v) {
    int n = v.size();
    for (int i=0; i<n; i++) {
        int ind_min = i;
        for (int j=i+1; j<n; j++)
            if (v.at(j) < v.at(ind_min))
                ind_min = j;
        // Swap elements i, ind_min
        std::swap(v.at(i), v.at(ind_min));
    }
    return v;
}

/**
 * Sorting a vector with the heap sort algorithm.
 * Using STL priority queue implementation for the heap.
 * 
 * @param v vector of doubles to order.
 * @return ordered vector.
 */
std::vector<double> heap_sort(std::vector<double> v) {
    std::priority_queue<double> heap_v;
    for (auto x : v)
        heap_v.push(-x);
    int n = v.size();
    std::vector<double> v_ord;
    while (!heap_v.empty()) {
        v_ord.push_back(-heap_v.top());
        heap_v.pop();
    }
    return v_ord;
}

void quick_sort(std::vector<double>& v,int low,int high)
{
    if(low<high)
    {
        int pivot_index=partition(v,low,high);
        quick_sort(v,low,pivot_index-1);
        quick_sort(v,pivot_index+1,high);
    }
}

int partition(std::vector<double>& v,int low,int high)
{
    double pivot=v.at(high);
    int i=low-1;
    for(int j=low;j<high;j++)
        if(v.at(j)<pivot)
        {
            i++;
            std::swap(v.at(i),v.at(j));
        }
    std::swap(v.at(i+1),v.at(high));
    return i+1;
}