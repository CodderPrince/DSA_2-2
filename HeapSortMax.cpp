#include <bits/stdc++.h>
using namespace std;

void heapify(vector<int> &arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(const vector<int> &arr)
{
    for (int val : arr)
    {
        cout << val << " ";
    }
    cout << "\n";
}

int main()
{
    int node;
    cin >> node;
    vector<int> arr(node);

    for (int i = 0; i < node; i++)
    {
        cin >> arr[i];
    }

    cout << "Original array:\n";
    printArray(arr);

    heapSort(arr);

    cout << "Sorted array (Ascending Order):\n";
    printArray(arr);

    return 0;
}