#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>
#define BitSize 32

using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
  int  BitLen; 
  TELEM *pMem; 
  int  MemLen; 

  int   GetMemIndex(const int n) const; 
  TELEM GetMemMask (const int n) const; 
  friend void PullForMax(TBitField& tmp1, TBitField& tmp2);
public:

  TBitField(int len);                
  TBitField(const TBitField &tmp);   
  ~TBitField();                      

  // доступ к битам
  int GetLength(void) const;      
  void SetBit(const int n);       
  void ClrBit(const int n);       
  int  GetBit(const int n) const; 

  // битовые операции
  int operator==(const TBitField &tmp) const; 
  int operator!=(const TBitField &tmp) const; 
  const TBitField& operator=(const TBitField &tmp); 
  TBitField  operator|(const TBitField &tmp) const; 
  TBitField  operator&(const TBitField& tmp) const;
  TBitField  operator~(void) const;                

  friend istream &operator>>(istream &is, TBitField &tmp);       
  friend ostream &operator<<(ostream &os, const TBitField &tmp); 
};
#endif
