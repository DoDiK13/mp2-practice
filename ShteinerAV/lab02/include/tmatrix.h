#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  explicit TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw std::out_of_range("Вышел за рамки размера вектора");
    pMem = new T[sz]();
  }
  TDynamicVector(const T* arr, size_t s) : sz(s)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
          throw std::out_of_range("Вышел за рамки размера вектора");
    if (arr == nullptr) throw std::invalid_argument("arr is nullptr");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.size())
  {
      T* newMem = new T[sz]();
      try {
          std::copy(v.pMem, v.pMem + sz, newMem);
      }
      catch (...) {
          delete[] newMem;
          throw;
      }
      pMem = newMem;
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.size()), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v) 
  {
      if (this == &v) return *this;
      if (sz != v.sz) {
          sz = v.sz;
      }

      T* newMem = new T[sz](); //после определения размера выделяем память для буферного вектора
      try {
          std::copy(v.pMem, v.pMem + sz, newMem);
      }
      catch (...) {
          delete[] newMem;
          throw;
      }
      
      delete[] pMem;
      pMem = newMem;
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      delete[] pMem;

      sz = v.sz;
      pMem = v.pMem;

      v.sz = 0;
      v.pMem = nullptr;

      return *this;
  }

  size_t size() const noexcept { return sz; }

  T& operator[](size_t ind)
  {
      if (ind >= sz) throw std::out_of_range("Выход за границы");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind >= sz) throw std::out_of_range("Выход за границы");
      return pMem[ind];
  }


  T& at(size_t ind)
  {
      if (ind >= sz) throw std::out_of_range("Выход за границы");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw std::out_of_range("Выход за границы");
      return pMem[ind];
  }


  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) {
          return false;
      } 
 
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !((*this) == v);
  }


  TDynamicVector operator+(T val) const
  {
      TDynamicVector v1(*this);
      for (int i = 0; i < sz; i++) {
          v1.pMem[i] += val;
      }

      return v1;
  }
  TDynamicVector operator-(T val) const // v1+v2*(-1) Не понял, как реализовать 
  {
      TDynamicVector v1(*this);
      for (int i = 0; i < sz; i++) {
          v1.pMem[i] -= val;
      }

      return v1;

  }
  TDynamicVector operator*(T val) const
  {
      TDynamicVector v1(*this);
      for (int i = 0; i < sz; i++) {
          v1.pMem[i] *= val;
      }

      return v1;
  }


  TDynamicVector operator+(const TDynamicVector& v) const
  {
      if (sz != v.sz) throw std::invalid_argument("Не совпадают размеры");
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v) const // v1+v2*(-1) 
  {
      if (sz != v.sz) throw std::invalid_argument("Не совпадают размеры");
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] - v.pMem[i];
      }
      return res;

      //return (*this) + (v * T(-1)); с такой реализацией вылезает ошибка
  }
  T operator*(const TDynamicVector& v) const
  {
      if (sz != v.sz) throw std::invalid_argument("Не совпадают размеры");
      T res = T();
      for (int i = 0; i < sz; i++) {
          res += pMem[i]*v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  friend istream &operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; 
    return ostr;
  }
};

// Динамическая треугольная матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  T& at(size_t i, size_t j)
  {
      if (ind >= sz || j >=sz || j < i) throw std::out_of_range("Выход за границы");
      return pMem[i][j-i];
  }
  const T& at(size_t i, size_t j) const
  {
      if (ind >= sz || j >= sz || j < j < i) throw std::out_of_range("Выход за границы");
      return pMem[i][j];
  }

  explicit TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz < 0 || sz > MAX_MATRIX_SIZE) throw std::out_of_range("Вышли за рамки");
      for (int i = 0; i < sz; i++) {
          pMem[i] = TDynamicVector<T>(sz - i);
      }
  }


  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m[i]) return false;
      }
      return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !((*this) == m);
  }


  TDynamicMatrix<T> operator+(T val) const
  {
      TDynamicMatrix<T> res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] + val;
      }

      return res;
  }

  TDynamicMatrix<T> operator-(T val) const
  {
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] - val;
      }

      return res;
  }
  
  TDynamicMatrix<T> operator*(T val) const
  {
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] * val;
      }

      return res;
  }


  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if (sz != v.size()) throw std::invalid_argument("Не совпадают размеры");
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < pMem[i].size(); j++) {
              res[i] += this->pMem[i][j] * v[j+i];
          }
      }

      return res;
  }


  TDynamicMatrix operator+(const TDynamicMatrix& m) const 
  {
      if (sz != m.sz) throw std::invalid_argument("Не совпадают размеры");
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] + m[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) const 
  {
      if (sz != m.sz) throw std::invalid_argument("Не совпадают размеры");
      TDynamicMatrix res(*this);
      for (size_t i = 0; i < sz; i++) {
          res[i] = res[i] - m[i];
      }
      return res;
  }
  TDynamicMatrix<T> operator*(const TDynamicMatrix& m) const
  {
      if (sz != m.sz) throw std::invalid_argument("Не совпадают размеры");
      TDynamicMatrix<T> res(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < pMem[i].size(); j++) {  
              for (size_t k = 0; k <= j; k++) {  
                  res[i][j] += pMem[i][k] * m.pMem[i + k][j - k];
              }
          }
      }

      return res;
  }


  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          istr >> v[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          ostr << v[i] << std::endl;
      }
      return ostr;
  }
};

#endif
