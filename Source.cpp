
// sorting using arrays

#include <iostream>
using namespace std;

class ArrayOperations {
public:

    void DisplayContents(int array[], int size) {
        cout << "Array Contents: ";
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    void findEvenValues(int array[], int size) {
        cout << "Even Values: ";
        for (int i = 0; i < size; i++) {
            if (array[i] % 2 == 0) {
                cout << array[i] << " ";
            }
        }
        cout << endl;
    }
    void findOddValues(int array[], int size) {
        cout << "Odd Values: ";
        for (int i = 0; i < size; i++) {
            if (array[i] % 2 != 0) {
                cout << array[i] << " ";
            }
        }
        cout << endl;
    }
    int* findMinMax(int array[], int size) {
        static int result[2];  

        int min = array[0];
        int max = array[0];

        for (int i = 1; i < size; i++) {
            if (array[i] < min)
                min = array[i];
            if (array[i] > max)
                max = array[i];
        }

        result[0] = min;
        result[1] = max;

        cout << "Minimum: " << min << endl;
        cout << "Maximum: " << max << endl;

        return result;
    }

    int* SortArray(int array[], int size, char orderType) {
        static int sorted[100]; 

        for (int i = 0; i < size; i++) {
            sorted[i] = array[i];
        }
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {

                if ((orderType == 'a' || orderType == 'A') && sorted[j] > sorted[j + 1]) {
                    swap(sorted[j], sorted[j + 1]);
                }

                if ((orderType == 'd' || orderType == 'D') && sorted[j] < sorted[j + 1]) {
                    swap(sorted[j], sorted[j + 1]);
                }
            }
        }

        return sorted;
    }
};

int main() {
    int size = 7;
    int arr[] = { 5, 12, 7, 3, 20, 9, 2 };
    
    ArrayOperations obj;

    obj.DisplayContents(arr, size);
    obj.findEvenValues(arr, size);
    obj.findOddValues(arr, size);

    obj.findMinMax(arr, size);
    int* sortedAsc = obj.SortArray(arr, size, 'A');
    cout << "Sorted Ascending: ";
    for (int i = 0; i < size; i++) {
        cout << sortedAsc[i] << " ";
    }
    cout << endl;

    int* sortedDesc = obj.SortArray(arr, size, 'D');
    cout << "Sorted Descending: ";
    for (int i = 0; i < size; i++) {
        cout << sortedDesc[i] << " ";
    }
    cout << endl;

    return 0;
}