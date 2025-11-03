#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Structure to represent a customer orders
struct CustomerOrder {
    int orderId;
    long long timestamp; // Using long long for large timestamps

    // Function to print an order
    void print() const {
        std::cout << "Order ID: " << orderId << ", Timestamp: " << timestamp << std::endl;
    }
};

// --- Merge Sort Implementation ---

/**
 * @brief Merges two sorted sub-arrays into a single sorted array.
 *
 * @param arr The array containing the orders.
 * @param left The starting index of the first sub-array.
 * @param mid The ending index of the first sub-array.
 * @param right The ending index of the second sub-array.
 */
void merge(std::vector<CustomerOrder>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors for the two halves
    std::vector<CustomerOrder> L(n1);
    std::vector<CustomerOrder> R(n2);

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0; // Initial index of first sub-array
    int j = 0; // Initial index of second sub-array
    int k = left; // Initial index of merged sub-array

    while (i < n1 && j < n2) {
        // Compare orders based on timestamp
        if (L[i].timestamp <= R[j].timestamp) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief Sorts the array using the Merge Sort algorithm.
 *
 * @param arr The vector of customer orders to be sorted.
 * @param left The starting index of the sub-array.
 * @param right The ending index of the sub-array.
 */
void mergeSort(std::vector<CustomerOrder>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// --- Example Usage and Testing ---

// Function to generate a large dummy dataset (up to 1 million orders)
std::vector<CustomerOrder> generateDummyData(int count) {
    std::vector<CustomerOrder> data;
    for (int i = 0; i < count; ++i) {
        data.push_back({
            i + 1, // Simple order ID
            // Generate a 'random' but reproducible timestamp for example
            1600000000000LL + (long long)(std::rand() % 100000000000LL)
        });
    }
    return data;
}

int main() {
    // Define the size of the dataset
    const int DATASET_SIZE = 10; // Set to 1000000 for full-scale test

    // 1. Generate Data
    std::srand(std::time(0)); // Seed for random number generation
    std::vector<CustomerOrder> orders = generateDummyData(DATASET_SIZE);

    if (DATASET_SIZE <= 10) {
        std::cout << "--- Original Orders (First " << DATASET_SIZE << " ) ---" << std::endl;
        for (const auto& order : orders) {
            order.print();
        }
        std::cout << "\n";
    }

    // 2. Perform Sorting and Time Measurement
    std::cout << "Starting Merge Sort on " << DATASET_SIZE << " orders..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();

    mergeSort(orders, 0, orders.size() - 1);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // 3. Output Results
    if (DATASET_SIZE <= 10) {
        std::cout << "--- Sorted Orders (First " << DATASET_SIZE << " ) ---" << std::endl;
        for (const auto& order : orders) {
            order.print();
        }
        std::cout << "\n";
    }

    std::cout << "Merge Sort completed." << std::endl;
    std::cout << "Total time taken: **" << duration.count() << " milliseconds**" << std::endl;

    return 0;
}