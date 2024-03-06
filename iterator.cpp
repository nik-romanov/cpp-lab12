#include <cstddef>

template <typename T>
class Vector{
    T      *data;
    size_t count;
public:
    class              VectorIterator;
    typedef              T value_type;
    typedef T*                pointer;
    typedef T&              reference;
    typedef T const & const_reference;

    Vector();

    Vector(size_t count, const T& value = T());

    VectorIterator begin();

    VectorIterator end();

    size_t size() const;

    T& operator [] (size_t);

};

template <typename T>
Vector<T>::Vector()
: data(0), count(0) {}

template <typename T>
Vector<T>::Vector(size_t count, const T& value)
{ data = new T [count]; this->count = count; 
 for (size_t i = 0; i < count; ++i) data[i] = value; }

template<typename T>
typename Vector<T>::VectorIterator Vector<T>::begin()
{ return VectorIterator(this, 0); }

template<typename T>
typename Vector<T>::VectorIterator Vector<T>::end()
{ return VectorIterator(this, count); }

template<typename T>
size_t Vector<T>::size() const
{ return count; }

template<typename T>
T& Vector<T>::operator [] (size_t ind)
{ return data[ind]; }

#include <iterator>

template <typename T>
class Vector<T>::VectorIterator{

private:
    Vector<T> *cont;
    size_t      pos;
    //template <class Iter>
    //friend struct std::iterator_traits;

public:
    typedef ptrdiff_t                           difference_type;
    typedef typename Vector<T>::value_type           value_type;
    typedef typename Vector<T>::pointer                 pointer;
    typedef typename Vector<T>::reference             reference;
    typedef typename Vector<T>::const_reference const_reference;
    typedef std::random_access_iterator_tag   iterator_category;
    
    VectorIterator()
    : cont(0), pos(0) {}

    VectorIterator(const VectorIterator &o)
    : cont(o.cont), pos(o.pos) {}

    VectorIterator(Vector<T> *cont, size_t pos)
    : cont(cont), pos(pos) {}

    ~VectorIterator() { cont = 0; pos = -1; }

    VectorIterator & operator = (const VectorIterator &o)
    { cont = o.cont; pos = o.pos; return *this; }
    
    VectorIterator & operator ++ ()
    { ++pos; if (pos >= cont->count) pos = cont->count; return *this; }

    VectorIterator & operator ++ (int)
    { VectorIterator old(*this); ++pos; if (pos >= cont->count) pos = cont->count; return old; }

    //Input
    bool operator == (const VectorIterator &o) const
    { return (cont == o.cont) && (pos == o.pos); }

    bool operator != (const VectorIterator &o) const
    { return (cont == o.cont) && (pos != o.pos); }

    typename Vector<T>::reference & operator * ()
    { return cont->data[pos]; }

    typename Vector<T>::const_reference & operator * () const
    { return cont->data[pos]; }

    //Bidirectional
    VectorIterator & operator -- ()
    { --pos; if (pos >= cont->count) pos = cont->count; return *this; }

    VectorIterator & operator -- (int)
    { VectorIterator old(*this); --pos; if (pos >= cont->count) pos = cont->count; return old; }

    //Random Access
    VectorIterator & operator += (size_t n)
    { pos += n; if (pos >= cont->count) pos = cont->count; return *this; }

    VectorIterator operator + (size_t n)
    { VectorIterator temp(*this); temp.pos += n; if (pos >= cont->count) pos = cont->count; return temp; }

    VectorIterator & operator -= (size_t n)
    { pos -= n; if (pos >= cont->count) pos = cont->count; return *this; }

    VectorIterator operator - (size_t n)
    { VectorIterator temp(*this); temp.pos -= n; if (pos >= cont->count) pos = cont->count; return temp; }

    difference_type operator - (VectorIterator &r)
    { if (cont == r.cont && pos <= cont->count && r.pos <= cont->count)
      return (pos > r.pos ? pos : r.pos) - (pos < r.pos ? pos : r.pos);
      return 0; }

    bool operator < (VectorIterator &r)
    { if (cont == r.cont) return pos < r.pos; return false; }

    bool operator <= (VectorIterator &r)
    { if (cont == r.cont) return pos <= r.pos; return false; }

    bool operator > (VectorIterator &r)
    { if (cont == r.cont) return pos > r.pos; return false; }

    bool operator >= (VectorIterator &r)
    { if (cont == r.cont) return pos >= r.pos; return false; }
};

#include <algorithm>
#include <iostream>
int main()
{
    Vector<int> v(5, 7); //инициализируем вектор размера 3 значением 7
    std::cout << v[0] << v[1] << v[2] << v[3] << v[4] << std::endl;

    v[0] = 8;
    v[1] = 3;
    v[2] = 6;
    v[3] = 1;
    std::cout << v[0] << v[1] << v[2] << v[3] << v[4] << std::endl;

    std::sort(v.begin(), v.end());
    std::cout << v[0] << v[1] << v[2] << v[3] << v[4] << std::endl;

    Vector<int>::VectorIterator iter = v.end() - 1; //возвращает итератор на последний элемент + 1
    for (size_t count = 0; count < v.size(); count++) {
        std::cout << *iter;
        iter--;
    }std::cout << std::endl;

    return 0;
}