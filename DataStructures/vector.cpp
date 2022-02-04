#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>
template <typename T>
class Vector
{

public:
    class Iterator;
    Vector() : array(nullptr), size_(0) {}
    std::size_t size()
    {
        return size_;
    }
    void push(T &&val)
    {
        array = static_cast<T *>(realloc(array, (size() + 1) * sizeof(T)));
        array[size_++] = std::move(val);
    }
    void pop()
    {
        if (size_ > 0)
        {
            array = static_cast<T *>(realloc(array, (size() - 1) * sizeof(T)));
            size_--;
        }
    }
    void resize(int newSize, int val = 0)
    {
        array = static_cast<T *>(realloc(array, (newSize) * sizeof(T)));
        if (newSize > size_)
        {
            if (val != 0)
            {
                for (std::size_t i = size_; i < newSize; i++)
                {
                    array[i] = val;
                }
            }
        }
        size_ = newSize;
    }
    T operator[](size_t index)
    {
        return array[index];
    }

    void clear()
    {
        if (array)
        {
            free(array);
            array = nullptr;
        }
        size_ = 0;
    }
    ~Vector()
    {
        clear();
    }
    Iterator begin() { return array; }
    Iterator end() { return array + size_; }

    class Iterator : public std::iterator<std::input_iterator_tag, T>
    {
    private:
        T *val;

    public:
        typedef typename std::iterator<std::input_iterator_tag, T>::difference_type difference_type;
        Iterator(T *value) : val(value) {}
        Iterator operator+(T i) { return Iterator(val + i); }
        Iterator operator-(T i) { return Iterator(val - i); }
        difference_type operator-(const Iterator &it) const { return val - it.val; }
        difference_type operator<(const Iterator &it) const { return val < it.val; }
        Iterator &operator++()
        {
            ++val;
            return *this;
        }
        Iterator &operator--()
        {
            --val;
            return *this;
        }
        Iterator &operator++(T)
        {
            Iterator t(*this);
            ++val;
            return t;
        }
        Iterator &operator--(T)
        {
            Iterator t(*this);
            --val;
            return t;
        }
        T &operator*() { return *val; }
        bool operator!=(const Iterator &it) { return val != it.val; }
        bool operator==(const Iterator &it) { return val == it.val; }
    };

private:
    T *array;
    std::size_t size_;
};
int main()
{

    Vector<int> v;
    v.push(9);
    v.push(8);
    v.push(7);

    for (auto a : v)
    {
        std::cout << a << " ";
    }
    std::cout << "\n";

    v.pop();
    v.push(6);
    std::cout << v.size() << std::endl;
    std::cout << v[0] << "\n";

    v.resize(8, 8);
    std::sort(v.begin(), v.end());
    for (auto &x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << "\n";

    v.clear();

    Vector<int>::Iterator it = v.begin();

    while (it != v.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "\n";
}