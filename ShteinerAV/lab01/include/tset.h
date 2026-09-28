// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __SET_H__
#define __SET_H__

#include "tbitfield.h"

class TSet
{
private:
  int MaxPower;       
  TBitField BitField; 
public:
  TSet(int mp);
  TSet(const TSet &tmp); 
  TSet(const TBitField &bf);
  operator TBitField();
  // доступ к битам
  int GetMaxPower(void) const;
  void InsElem(const int Elem);       
  void DelElem(const int Elem);       
  int IsMember(const int Elem) const;
  // теоретико-множественные операции
  int operator== (const TSet &tmp) const; 
  int operator!= (const TSet &tmp) const; 
  const TSet& operator=(const TSet &s);
  TSet operator+ (const int Elem) const; // объединение с элементом
                                   // элемент должен быть из того же универса
  TSet operator- (const int Elem) const; // разность с элементом
                                   // элемент должен быть из того же универса
  TSet operator+ (const TSet &s) const;
  TSet operator* (const TSet &s) const;
  TSet operator~ (void) const;

  friend istream &operator>>(istream &is, TSet &bf);
  friend ostream &operator<<(ostream &os, const TSet &bf);
};
#endif
