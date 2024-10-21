#include <iostream>

using namespace std;

short int getMinRun(short int len)
{
    short int r = 0;
    while (len >= 64)
    {
        r |= (len & 1);
        len >>= 1;
    }
    return len + r;
}

short int binarySearch(short int arr[], short int value, short int start, short int end)
{
    short int mid;
    while (end >= start)
    {
        mid = (start + end) / 2;
        if (arr[mid] == value)
        {
            return mid;
        }
        if (arr[mid] > value)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return end;
}


void insertionSort(short int arr[], short int left, short int right)
{
    short int i, j, key;
    for (short int i = left + 1; i <= right; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= left && key < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(short int arr[], int left, int mid, int right)
{
    short int leftArrLen = mid - left + 1;
    short int rightArrLen = right - mid;
    short int* leftArr = new short int[leftArrLen];
    short int* rightArr = new short int[rightArrLen];
    for (short int i = 0; i < leftArrLen; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (short int i = 0; i < leftArrLen; i++)
    {
        rightArr[i] = arr[mid + 1 + i];
    }

    short int i = 0, j = 0, k = left;
    short int currStreakLeft = 0, currStreakRight = 0, indicatorForGallop = 7, index = 0;
    while (i < leftArrLen && j < rightArrLen)
    {
        if (currStreakLeft >= indicatorForGallop)
        {
            index = binarySearch(leftArr, rightArr[j], i, leftArrLen - 1);
            for (short int x = i; x <= index; x++)
            {
                arr[k] = leftArr[x];
                k++;
            }
            i = index + 1;
            currStreakLeft = 0;
        }
        if (currStreakRight >= indicatorForGallop)
        {
            index = binarySearch(rightArr, leftArr[i], j, rightArrLen - 1);
            for (short int x = j; x <= index; x++)
            {
                arr[k] = rightArr[x];
                k++;
            }
            j = index + 1;
            currStreakRight = 0;
        }

        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            currStreakLeft++;
            currStreakRight = 0;
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            currStreakLeft = 0;
            currStreakRight++;
            j++;
        }
        k++;
    }

    while (i < leftArrLen)
    {
        arr[k] = leftArr[i];
        k++;
        i++;
    }

    while (j < rightArrLen)
    {
        arr[k] = rightArr[j];
        k++;
        j++;
    }
}

void TimSort(short int arr[], int len)
{
    short int minRun = getMinRun(len);
    for (short int i = 0; i < len; i+=minRun)
    {
        insertionSort(arr, i, min(len - 1, i + minRun - 1));
    }
    short int size = minRun;
    while (size < len)
    {
        for (short int left = 0; left < len; left = left + 2 * size)
        {
            short int mid = left + size - 1;
            short int right = min((left + 2 * size - 1), (len - 1));
            merge(arr, left, mid, right);
        }
        size = size * 2;
    }
}

void printArr(short int arr[], short int len)
{
    for (short int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main()
{
    setlocale(0, "");
    bool isEnd = false;
    short int length = 0;
    while (!isEnd)
    {
        system("cls");
        cout << "Введите длину массива: ";
        cin >> length;
        while (length < 1)
        {
            cout << "Длина массива должна быть больше нуля\n";
            cout << "Введите длину массива: ";
            cin >> length;
        }
        short int* arr = new short int[length];
        short int option = 0;
        cout << "0. Заполнение массива случайными числами\n1. Ввод элементов массива с клавиатуры\n";
        cin >> option;
        if (option)
        {
            for (short int i = 0; i < length; i++)
            {
                cin >> arr[i];
            }
        }
        else
        {
            srand(time(NULL));
            for (short int i = 0; i < length; i++)
            {
                arr[i] = rand() % (1001) - 500;
            }
            cout << "Созданный массив:\n";
            printArr(arr, length);
        }
        //insertionSort(arr, 0, lenght - 1);
        TimSort(arr, length);
        cout << "Отсортированный массив:\n";
        printArr(arr, length);
        delete[] arr;
        short int ex = 0;
        cout << "Хотите пересоздать массив?\n0. Нет\n1. Да\n";
        cin >> ex;
        isEnd = !ex;
        
    }
}

