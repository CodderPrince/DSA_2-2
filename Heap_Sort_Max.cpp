/*
    HeapSort
    Using Max Heap
    Ascending order sort
    Graphical Representation
*/

#include <bits/stdc++.h>
using namespace std;

void fillPrint(const vector<int> &arr, int n, vector<string> &res, int index, int row, int col, int space)
{
    if (index >= n)
    {
        return;
    }

    string val = to_string(arr[index]);
    for (int i = 0; i < val.size(); ++i)
    {
        res[row][col + i] = val[i];
    }

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n)
    {
        res[row + 1][col - space / 2] = '/';
        fillPrint(arr, n, res, left, row + 2, col - space, space / 2);
    }

    if (right < n)
    {
        res[row + 1][col + val.size() + space / 2] = '\\';
        fillPrint(arr, n, res, right, row + 2, col + val.size() + space, space / 2);
    }
}

void printHeapTree(const vector<int> &arr, int n)
{
    if (n == 0)
    {
        return;
    }

    int height = log2(n) + 1;
    int rows = height * 2 - 1;
    int cols = pow(2, height + 2);
    vector<string> res(rows, string(cols, ' '));

    int mid = cols / 2;
    fillPrint(arr, n, res, 0, 0, mid, cols / 4);

    for (const string &line : res)
    {
        int end = line.find_last_not_of(' ');
        if (end != string::npos)
        {
            cout << line.substr(0, end + 1) << "\n";
        }
    }
}

void heapify(vector<int> &arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n)
    {
        if (arr[left] > arr[largest])
        {
            largest = left;
        }
    }

    if (right < n)
    {
        if (arr[largest] < arr[right])
        {
            largest = right;
        }
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

    cout << "Heap Tree (Max Heap):\n";
    printHeapTree(arr, n);
    cout << "\n";

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

    cout << "Ascending Order Sorted array:\n";
    printHeapTree(arr, node);
    cout << "\n";

    cout << "Sorted array: ";
    printArray(arr);
    cout << "\n";

    return 0;
}

/*
t-1
6
5 30 40 20 15 10
*/