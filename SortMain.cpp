#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Heap/Heap.h"
#include "Map/Map.h"

using namespace std;
#define num 100

//冒泡排序
template<class T>
void BubbleSort(vector<T> &x);

//选择排序(1:基本选择排序，2:双端选择排序，other:改进的双端选择排序(min-max+彩虹模式))
template<class T>
void SelectSort(vector<T> &x, int type);

//插入排序(1:线性插入排序，other:折半插入排序)
template<class T>
void InsertSort(vector<T> &x, int type);

//希尔排序
template<class T>
void ShellSort(vector<T> &x);

//计数排序
template<class T>
void CountedSort(vector<T> &x);

//基数排序
template<class T>
void RadixSort(vector<T> &x);

//二叉查找树排序，选做
template<class T>
void BSTSort(vector<T> &x);

//快速排序
template<class T>
void QuickSort(vector<T> &x, int left, int right);

//堆排序
template<class T>
void HeapSort(vector<T> &x);

template<class T>
void Display(vector<T> &x);

template<class T>
void ResetData(vector<T> &x, vector<T> &y);//使用y重置x
//......自行添加其他必要的函数声明
int main() {
    vector<int> a(num + 1), b(num + 1);
    //有效数据从1开始，也可以设计从0开始，自行根据需要调整
    int i;
    clock_t start, end;
    srand(time(nullptr));//随机数种子初始化
    for (i = 1; i <= num; i++) {
        a[i] = rand() % 10000 + 1; //随机生成1-10000内的数值作为排序对象
        b[i] = a[i];
    }
    //排序前显示数据
    cout << "排序前" << endl;
    Display(a);
    //冒泡排序
    start = clock();
    BubbleSort(a);
    end = clock();
    cout << endl << "冒泡排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //基础选择排序
    ResetData(a, b);
    start = clock();
    SelectSort(a, 1);
    end = clock();
    cout << "基础选择排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //双端选择排序
    ResetData(a, b);
    start = clock();
    SelectSort(a, 2);
    end = clock();
    cout << "双端选择排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //改进的双端选择排序
    ResetData(a, b);
    start = clock();
    SelectSort(a, 3);
    end = clock();
    cout << "改进的双端选择排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //线性插入排序
    ResetData(a, b);
    start = clock();
    InsertSort(a, 0);
    end = clock();
    cout << "线性插入排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //对分插入排序
    ResetData(a, b);
    start = clock();
    InsertSort(a, 1);
    end = clock();
    cout << "对分插入排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //希尔排序
    ResetData(a, b);
    start = clock();
    ShellSort(a);
    end = clock();
    cout << "希尔排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //计数排序
    ResetData(a, b);
    start = clock();
    CountedSort(a);
    end = clock();
    cout << "计数排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //基数排序
    ResetData(a, b);
    start = clock();
    RadixSort(a);
    end = clock();
    cout << "基数排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //快速排序
    ResetData(a, b);
    start = clock();
    QuickSort(a, 1, num);
    end = clock();
    cout << "快速排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //堆排序
    ResetData(a, b);
    start = clock();
    HeapSort(a);
    end = clock();
    cout << "堆排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    //额外产品：BST排序
    ResetData(a, b);
    start = clock();
    BSTSort(a);
    end = clock();
    cout << "BST排序后" << endl;
    Display(a);
    cout << endl << "使用时长：" << double(end - start) << "ms" << endl;
    return 0;
}

template<class T>
void Display(vector<T> &x) {
    for (int i = 1; i <= num; i++) {
        cout << x[i] << " ";
        if (i % 15 == 0) cout << endl;
    }
}

//使用y重置x
template<class T>
void ResetData(vector<T> &x, vector<T> &y) {
    for (int i = 1; i <= num; i++) {
        x[i] = y[i];
    }
}

template<class T>
void BubbleSort(vector<T> &x) {
    for (int i = 2; i <= num; ++i) {
        for (int j = 1; j <= num; ++j) {
            if (x[j - 1] > x[j]) {
                swap(x[j - 1], x[j]);
            }
        }
    }
}

template<class T>
void SelectSort(vector<T> &x, int type) {
    switch (type) {
        case 1: {
            for (int i = 1; i <= num; ++i) {
                for (int j = i + 1; j <= num; ++j) {
                    if (x[i] > x[j]) {
                        swap(x[i], x[j]);
                    }
                }
            }
            break;
        }
        case 2: {
            for (int i = 1, j = num; i < j; ++i, --j) {
                for (int k = i + 1; k < j; ++k) {
                    if (x[i] > x[k]) {
                        swap(x[i], x[k]);
                    }
                    if (x[j] < x[k]) {
                        swap(x[j], x[k]);
                    }
                }
            }
            break;
        }
        default: {
            for (int i = 1, j = num; i < j; ++i, --j) {
                int Min = i;
                int Max = j;
                for (int k = i + 1; k != j; ++k) {
                    if (x[Min] > x[k]) {
                        Min = k;
                    }
                    if (x[Max] < x[k]) {
                        Max = k;
                    }
                }
                if (Min != i) {
                    swap(x[Min], x[i]);
                }
                if (Max != j) {
                    swap(x[Max], x[j]);
                }
            }
            break;
        }
    }
}

template<class T>
void InsertSort(vector<T> &x, int type) {
    if (!type) {
        for (int i = 2; i <= num; ++i) {
            int pos = i;
            for (int j = 1; j < i; ++j) {
                if (x[j] >= x[i]) {
                    pos = j;
                    break;
                }
            }
            for (int j = i; j > pos; --j) {
                swap(x[j], x[j - 1]);
            }
        }
    } else {
        for (int i = 2; i <= num; ++i) {
            int left = 0;
            int right = i - 1;
            while (left <= right) {
                int mid = (right + left) / 2;
                if (x[mid] > x[i]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            for (int j = i; j > left; --j) {
                swap(x[j], x[j - 1]);
            }
        }
    }
}

template<class T>
void ShellSort(vector<T> &x) {
    int gap = num / 2;
    while (gap) {
        for (int i = 1; i <= gap; ++i) {
            for (int j = i + gap; j <= num; j += gap) {
                int k = i;
                for (; k < j; k += gap) {
                    if (x[j] < x[k]) {
                        break;
                    }
                }
                for (int l = j; l > k; l -= gap) {
                    swap(x[l], x[l - gap]);
                }
            }
        }
        gap /= 2;
    }
}

template<class T>
void CountedSort(vector<T> &x) {
    vector<T> count(num + 1);
    vector<T> tmp(num + 1);
    for (int i = 1; i <= num; ++i) {
        for (int j = 1; j <= num; ++j) {
            if (i != j && x[i] < x[j]) {
                count[j]++;
            }
        }
    }
    for (int i = 1; i <= num; ++i) {
        tmp[count[i] + 1] = x[i];
    }
    for (int i = 1; i <= num; ++i) {
        x[i] = tmp[i];
    }
}

// 求最大位数
template<class T>
int maxBit(vector<T> &x) {
    int maxData = x[0];
    for (int i = 1; i < x.size(); ++i) {
        if (maxData < x[i])
            maxData = x[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p) {
        maxData /= 10;
        ++d;
    }
    return d;
}

template<class T>
void RadixSort(vector<T> &x) {
    int d = maxBit(x);
    vector<T> tmp(num + 1);
    int count[10];
    int i, j, k, radix = 1;
    for (i = 1; i <= d; ++i) {
        for (j = 0; j < 10; j++) {
            count[j] = 0;
        }
        for (j = 1; j <= num; ++j) {
            k = (x[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; ++j) {
            count[j] += count[j - 1];
        }
        for (j = num; j > 0; --j) {
            k = (x[j] / radix) % 10;
            tmp[count[k]] = x[j];
            count[k]--;
        }
        for (j = 1; j <= num; ++j) {
            x[j] = tmp[j];
        }
        radix *= 10;
    }
}

template<class T>
int Paritition(vector<T> &x, int left, int right) {
    int pivot = x[left];
    while (left < right) {
        while (left < right && x[right] >= pivot) {
            --right;
        }
        x[left] = x[right];
        while (left < right && x[left] <= pivot) {
            ++left;
        }
        x[right] = x[left];
    }
    x[left] = pivot;
    return left;
}

template<class T>
void QuickSort(vector<T> &x, int left, int right) {
    if (left < right) {
        int pivot = Paritition(x, left, right);
        QuickSort(x, left, pivot - 1);
        QuickSort(x, pivot + 1, right);
    }
}

template<class T>
void HeapSort(vector<T> &x) {
    Heap<T> heap;
    for (auto item: x) {
        heap.add(item);
    }
    x.clear();
    while (!heap.empty()) {
        x.push_back(heap.top());
        heap.removeTop();
    }
}

template<class T>
void BSTSort(vector<T> &x) {
    Map<T, int> map;
    for (auto item: x) {
        map.insert(Pair<T, int>(item, 1));
    }
    x.clear();
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
        if (!iter.getPtr()) {
            break;
        }
        x.push_back(iter->getFirst());
    }
}