#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <limits>
using namespace std;

const int DELAY = 1000; // milliseconds delay between steps

// Helper to print array and highlight two elements
void printArray(const vector<int>& arr, int h1 = -1, int h2 = -1) {
    for (int i = 0; i < arr.size(); ++i) {
        if (i == h1 || i == h2)
            cout << "[ "  << arr[i] << " ]";
        else
            cout << "  " << arr[i] << "  ";
    }
    cout << endl;
}

// ---------------- SEARCHING -----------------

// Linear Search Visualization
void linearSearch(vector<int> arr, int target) {
    cout << "\n Linear Search Visualization:\n";
    for (int i = 0; i < arr.size(); ++i) {
        printArray(arr, i);
        this_thread::sleep_for(chrono::milliseconds(DELAY));

        if (arr[i] == target) {
            cout << "\nElement found at index " << i << "!\n";
            return;
        }
    }
    cout << "\nElement not found.\n";

}

// Binary Search Visualization
void binarySearch(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    cout << "\n Binary Search Visualization (on sorted array):\n";
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        printArray(arr, low, high);
        cout << "Checking mid index " << mid << " -> " << arr[mid] << endl;
        this_thread::sleep_for(chrono::milliseconds(DELAY));

        if (arr[mid] == target) {
            cout << "\nElement found at index " << mid << "!\n";
            return;
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << "\nElement not found.\n";
}

// ---------------- SORTING -----------------

// Bubble Sort
void bubbleSort(vector<int> arr) {
    cout << "\n Bubble Sort Visualization:\n";
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            printArray(arr, j, j + 1);
            this_thread::sleep_for(chrono::milliseconds(DELAY));
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
        printArray(arr, -1, -1);
        cout << endl;
    }
    cout << "\nFinal sorted array:\n";
    printArray(arr);
}

// Insertion Sort
void insertionSort(vector<int> arr) {
    cout << "\n Insertion Sort Visualization:\n";
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        printArray(arr, j + 1, i);
		cout << "Inserting " << key << endl;
        while (j >= 0 && arr[j] > key) {
            printArray(arr, j , j);
            arr[j + 1] = arr[j];
            printArray(arr, -1, -1);
            j--;
            this_thread::sleep_for(chrono::milliseconds(DELAY));
        }
        arr[j + 1] = key;
        printArray(arr);
        cout << endl;
    }
    cout << "\nFinal sorted array:\n";
    printArray(arr);
}

// Selection Sort
void selectionSort(vector<int> arr) {
    cout << "\n Selection Sort Visualization:\n";
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            printArray(arr, minIdx, j);
            this_thread::sleep_for(chrono::milliseconds(DELAY));

            if (arr[j] < arr[minIdx])
                minIdx = j;

        }
        swap(arr[i], arr[minIdx]);
		printArray(arr);
        cout << endl;
    }
    cout << "\nFinal sorted array:\n";
    printArray(arr);
}

//Merge Sort

void printMergeSortNode(int l, int r, vector<int>& arr, int depth, bool isLast) {
    for (int i = 0; i < depth - 1; i++) cout << "|   "; // indentation
    if (depth > 0) cout << "|-- ";
    cout << "mergeSort(" << l << "," << r << "): [";
    for (int i = l; i <= r; i++) {
        cout << arr[i];
        if (i < r) cout << " ";
    }
    cout << "]";
    if (l == r) cout << "        (base)";
    cout << endl;
}
void merge(vector<int>& arr, int l, int m, int r, int depth) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    for (int i = 0; i < depth; i++) cout << "|   ";
    cout << "Merging leaves: [";

    for (int i = 0; i < left.size(); i++) {
        cout << left[i];
        if (i + 1 < left.size()) cout << " ";
    }

    cout << "] + [";

    for (int i = 0; i < right.size(); i++) {
        cout << right[i];
        if (i + 1 < right.size()) cout << " ";
    }

    cout << "]  -> ";

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];

    cout << "[";
    for (int x = l; x <= r; x++) {
        cout << arr[x];
        if (x < r) cout << " ";
    }
    cout << "]\n";
    this_thread::sleep_for(chrono::milliseconds(DELAY));
}


void mergeSortTree(vector<int>& arr, int l, int r, int depth, bool isLast) {
    printMergeSortNode(l, r, arr, depth, isLast);
    this_thread::sleep_for(chrono::milliseconds(DELAY));
    if (l >= r) return;

    int m = (l + r) / 2;             // normal balanced split for other nodes

    mergeSortTree(arr, l, m, depth + 1, false);
    mergeSortTree(arr, m + 1, r, depth + 1, true);
    merge(arr, l, m, r,depth);
}

void mergeSort(vector<int> arr){
    cout << "\nMerge Sort Visualization:\n";
    mergeSortTree(arr,0,arr.size()-1,0,true);
    cout << "\nFinal sorted array:\n[";
    for(int i=0;i<arr.size();i++) { cout << arr[i] << (i<arr.size()-1?" ":""); }
    cout << "]\n";
}

//Quick Sort

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        printArray(arr, j, high);
        this_thread::sleep_for(chrono::milliseconds(DELAY));

        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
	printArray(arr);
    cout << endl;
    return i + 1;
}

void quickSortUtil(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortUtil(arr, low, pi - 1);
        quickSortUtil(arr, pi + 1, high);
    }
}

void quickSort(vector<int> arr) {
    cout << "\n Quick Sort Visualization:\n";
    quickSortUtil(arr, 0, arr.size() - 1);
    cout << "\nFinal sorted array:\n";
    printArray(arr);
}


// ---------------- MENU INTERFACE -----------------

void searchingMenu(vector<int> arr) {
    int choice, target;
    cout << "\n=== SEARCHING ALGORITHMS ===";
    cout << "\n1. Linear Search\n2. Binary Search\nEnter your choice: ";
    cin >> choice;
    cout << "Enter element to search: ";
    cin >> target;
    if (choice == 1) linearSearch(arr, target);
    else if (choice == 2) binarySearch(arr, target);
    else cout << "Invalid choice!\n";
}

void sortingMenu(vector<int> arr) {
    int choice;
    cout << "\n=== SORTING ALGORITHMS ===";
    cout << "\n1. Bubble Sort";
    cout << "\n2. Insertion Sort";
    cout << "\n3. Selection Sort";
    cout << "\n4. Merge Sort";
    cout << "\n5. Quick Sort";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) bubbleSort(arr);
    else if (choice == 2) insertionSort(arr);
    else if (choice == 3) selectionSort(arr);
    else if (choice == 4) mergeSort(arr);
    else if (choice == 5) quickSort(arr);
    else cout << "Invalid choice!\n";
}


int main() {
    while (true) {
        cout << "\n===  Algorithm Visualizer ===\n";
        cout << "Select Category:\n";
        cout << "1. Searching Algorithms\n";
        cout << "2. Sorting Algorithms\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        int mainChoice;
        cin >> mainChoice;

        if (mainChoice == 0) break;

        if (mainChoice == 1) {
            vector<int> arr;
            int n;
            cout << "Enter size of array: ";
            cin >> n;
            arr.resize(n);
            cout << "Enter elements: ";
            for (int i = 0; i < n; ++i) cin >> arr[i];
            searchingMenu(arr);
        }
        else if (mainChoice == 2) {
            vector<int> arr;
            int n;
            cout << "Enter size of array: ";
            cin >> n;
            arr.resize(n);
            cout << "Enter elements: ";
            for (int i = 0; i < n; ++i) cin >> arr[i];
            sortingMenu(arr);
        }
        else cout << "Invalid choice!\n";
    }
    cout << "\n=== Visualization Completed ===\n";
    return 0;
}
