#include "rang.hpp" // rang is a library for terminal colors and styles

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace rang;

// Function declarations
void mergeSort(std::vector<int>& arr, int low, int high);
void merge(std::vector<int>& arr, int low, int mid, int high);
void insertionSort(std::vector<int>& arr);
void bubbleSort(std::vector<int>& arr);
void displayProgressBar(float progress);

int main() {
    int choice; // option for choosing the sorting algorithm

    std::cout << fg::cyan << "NUMBER CRUNCHER" << fg::reset << std::endl;

    // Sorting algorithms menu
    std::cout << fg::red << "1. Merge sort\n";
    std::cout << "2. Insertion sort\n";
    std::cout << "3. Bubble sort" << fg::reset << std::endl;

    std::cout << fg::cyan << "[+] " << fg::reset;
    std::cin >> choice;

    std::vector<int> numbers; // Vector to store numbers read from file

    // Read numbers from file
    std::ifstream inputFile("numbers.txt"); // Replace with your actual file name
    if (!inputFile.is_open()) {
        std::cerr << fg::red << "Error opening file: numbers.txt" << fg::reset << std::endl;
        return 1;
    }

    int num;
    while (inputFile >> num) {
        numbers.push_back(num);
    }

    inputFile.close();

    // Choose sorting algorithm and call the corresponding function
    if (choice == 1) {
        std::cout << "Using Merge Sort...\n";
        mergeSort(numbers, 0, numbers.size() - 1);
    } else if (choice == 2) {
        std::cout << "Using Insertion Sort...\n";
        insertionSort(numbers);
    } else if (choice == 3) {
        std::cout << "Using Bubble Sort...\n";
        bubbleSort(numbers);
    } else {
        // Invalid choice
        std::cout << fg::red << "Please enter a number between 1 and 3." << fg::reset << std::endl;
        return 1;
    }

    // Display progress bar
    std::cout << "Sorting in progress:\n";
    for (float progress = 0.0; progress <= 1.0; progress += 0.01) {
        displayProgressBar(progress);
    }

    // Write sorted numbers to 'sorted.txt'
    std::ofstream outputFile("sorted.txt");
    if (!outputFile.is_open()) {
        std::cerr << fg::red << "Error creating 'sorted.txt'" << fg::reset << std::endl;
        return 1;
    }

    for (const int& n : numbers) {
        outputFile << n << " ";
    }

    outputFile.close();

    std::cout << fg::cyan << "\nSorting completed. Sorted numbers are stored in 'sorted.txt'" << fg::reset << std::endl;

    return 0;
}

// Function definitions

// Merge Sort
void merge(std::vector<int>& arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    std::vector<int> left(n1);
    std::vector<int> right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// Insertion Sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

// Bubble Sort
// this shit looks so crazy but it isnt once you understand it
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Display progress bar
void displayProgressBar(float progress) {
    int barWidth = 50;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}