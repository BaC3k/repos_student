//#include <cstdio>
//#include <algorithm>
#include <cassert>
//#include <stdexcept>
#include <iostream>
//#include <iomanip>
//#include <cstring>
//#include <cmath>
//#include <cstdlib>
#include <chrono>

//using namespace std;

struct MyStruct { // структура элемента сортируемых данных
    double Key;		// ключ
    unsigned long long Value;		// значение
};

// вектор
template <typename T>
class vector {
public:
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    vector() :
        already_used_(0), storage_size_(0), storage_(nullptr)
    {
    }

    vector(int size, const value_type& default_value = value_type()) :
        vector()
    {
        assert(size >= 0);

        if (size == 0)
            return;

        already_used_ = size;
        storage_size_ = size;
        storage_ = new value_type[size];

        std::fill(storage_, storage_ + already_used_, default_value);
    }

    int size() const
    {
        return already_used_;
    }

    bool empty() const
    {
        return size() == 0;
    }

    iterator begin() const
    {
        return storage_;
    }

    iterator end() const
    {
        if (storage_)
            return storage_ + already_used_;

        return nullptr;
    }

    friend void swap(vector& lhs, vector& rhs)
    {
        using std::swap;

        swap(lhs.already_used_, rhs.already_used_);
        swap(lhs.storage_size_, rhs.storage_size_);
        swap(lhs.storage_, rhs.storage_);
    }

    vector& operator=(vector other)
    {
        swap(*this, other);
        return *this;
    }

    vector(const vector& other) :
        vector()
    {
        vector next(other.storage_size_);
        next.already_used_ = other.already_used_;

        if (other.storage_)
            std::copy(other.storage_, other.storage_ + other.storage_size_,
                next.storage_);

        swap(*this, next);
    }

    ~vector()
    {
        delete[] storage_;

        storage_size_ = 0;
        already_used_ = 0;
        storage_ = nullptr;
    }

    void push_back(const value_type& value)
    {
        if (already_used_ < storage_size_) {
            storage_[already_used_] = value;
            ++already_used_;
            return;
        }

        int next_size = 1;
        if (storage_size_)
            next_size = storage_size_ * 2;

        vector next(next_size);
        next.already_used_ = already_used_;

        if (storage_)
            std::copy(storage_, storage_ + storage_size_, next.storage_);

        next.push_back(value);
        swap(*this, next);
    }

    const value_type& at(int index) const
    {
        if (index < 0 || index > already_used_)
            throw std::out_of_range("You are doing this wrong!");

        return storage_[index];
    }

    value_type& at(int index)
    {
        const value_type& elem = const_cast<const vector*>(this)->at(index);
        return const_cast<value_type&>(elem);
    }

    const value_type& operator[](int index) const
    {
        return at(index);
    }

    value_type& operator[](int index)
    {
        return at(index);
    }

private:
    int already_used_;
    int storage_size_;
    value_type* storage_;
};
// вектор

double getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<double>(rand() * fraction * (max - min + 1) + min);
}

// сортировка внутри корзины
/*void Sort(vector<MyStruct>& a) {
    if (a.size() <= 1) {
        return;
    }
    for (int i = 1; i < a.size(); i++)
        for (int j = i; j > 0 && a[j - 1].Key > a[j].Key; j--)
        {
            std::swap(a[j - 1].Key, a[j].Key);
            std::swap(a[j - 1].Value, a[j].Value);
        }
}
*/

/*void b_sort(int sarray[], int array_size) {
    const int max = array_size;
    // use bucket[x][max] to hold the current count
    int bucket[10][max + 1];
    // init bucket counters
    for (int x = 0; x < 10; x++) 
        bucket[x][max] = 0;
    // main loop for each digit position
    for (int digit = 1; digit <= 1000000000; digit *= 10) {
        // array to bucket
        for (int i = 0; i < max; i++) {
            // get the digit 0-9
            int dig = (sarray[i] / digit) % 10;
            // add to bucket and increment count
            bucket[dig][bucket[dig][max]++] = sarray[i];
        }
        // bucket to array
        int idx = 0;
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < bucket[x][max]; y++) {
                sarray[idx++] = bucket[x][y];
            }
            // reset the internal bucket counters
            bucket[x][max] = 0;
        }
    }
}*/

void qsortRecursive(vector<MyStruct>& a, int begin, int size) {
    if (a.size() <= 1) {
        return;
    }
    int i = begin;
    int j = size - 1;
    double mid = a[size / 2].Key;
    do {
        while (a[i].Key < mid) {
            i++;
        }
        while (a[j].Key > mid) {
            j--;
        }
        if (i <= j) {
            std::swap(
                a[i].Key, a[j].Key);
            std::swap(a[i].Value, a[j].Value);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 1) {
        qsortRecursive(a, 0, j + 1);
    }
    if (i < size) {
        qsortRecursive(a, i, size - i);
    }
}
// корзинная сортировка
void BucketSort(vector<MyStruct>& mas) {
    if (mas.size() <= 1) { // сортировать имеет смысл только 2 и более элементов
        return;
    }

    const double MIN_VALUE = -100; // минимум возможных сортируемых значений
    const double MAX_VALUE = 100; // максимум возможных сортируемых значений
    const int BUCKETS = 272;     // количество корзин


    vector<MyStruct> b[BUCKETS]; // массив из векторов (каждый вектор - это корзина)


    for (int i = 0; i < mas.size(); i++) {
        int bi = (BUCKETS - 1) * ((mas[i].Key + (abs)(MIN_VALUE)) / (MAX_VALUE - MIN_VALUE));
        b[bi].push_back(mas[i]); // заполняем корзины данными из исходного вектора
    }


    for (int i = 0; i < BUCKETS; i++) {	// содержимое каждой корзины
        qsortRecursive(b[i],0,b[i].size());					// отсортируем
    }

    int index = 0;
    for (int i = 0; i < BUCKETS; i++) 		  // последовательно переносим
        for (int j = 0; j < b[i].size(); j++)//  содержимое отсортированных  векторов (корзин)
            mas[index++] = b[i][j]; 		//   в первоначальный массив
}
// конец корзинной сортировки


/* Driver program to test above funtion */
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    vector<MyStruct> arr; //введенные ключи и идентификаторы строк будут храниться в векторе arr
    MyStruct s;

    while (std::cin >> s.Key>> s.Value) {	//ввод данных
        arr.push_back(s);       
    }
    /*int count; //тестовый ввод данных
    std::cin >> count; 
    for (int i = 0; i < count; i++) {
        s.Key = getRandomNumber(-99, 99);
        s.Value = getRandomNumber(0,pow(2, 64));
        arr.push_back(s);
    }*/

    auto t1 = std::chrono::high_resolution_clock::now();
    BucketSort(arr);	// сортируем arr корзинной сортировкой
    auto t2 = std::chrono::high_resolution_clock::now();
   // std::cout << std::setprecision(6) << std::fixed;
    for (size_t i = 0; i < arr.size(); i++) {// последовательно выводим элементы отсортированного вектора
        //printf("%.6f\t%d\n", arr[i].Key, arr[i].Value);
        std::cout << arr[i].Key <<"\t"<< arr[i].Value << std::endl;
    }

    auto res = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "res = " << res.count() / 1e9 << '\n';
    return 0;
}