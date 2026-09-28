#include "tbitfield.h"

static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len <= 0) {
        throw("Некорректная длина множества!");
    }
    BitLen = len;
    MemLen = (len + BitSize - 1) / BitSize;
    pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &tmp) 
{
    BitLen = tmp.BitLen;
    MemLen = tmp.MemLen;
    pMem = MemLen ? new TELEM[MemLen]() : nullptr;
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = tmp.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const 
{ 
    if (n >= 0 && n < BitLen) {//
        return n >> 5;//
    }
    else {
        throw("Некорректный индекс!");
    }
    
}

TELEM TBitField::GetMemMask(const int n) const
{
    if (n >= 0 && n < BitLen) {
        return 1 << (n & (BitSize - 1));
    }
    else {
        throw("Некорректный индекс!");
    }
}

int TBitField::GetLength(void) const 
{
  return BitLen;
}

void TBitField::SetBit(const int n) 
{
    if (n >= 0 && n < BitLen) {
        pMem[n >> 5] |= (1 << (n & (BitSize - 1)));
    }
    else {
        throw("Некорректный индекс!");
    }
}

void TBitField::ClrBit(const int n) 
{
    if (n >= 0 && n < BitLen) {
        pMem[n >> 5] &= ~(1 << (n & (BitSize - 1)));
    }
    else {
        throw("Некорректный индекс!");
    }
}

int TBitField::GetBit(const int n) const 
{
    if (n >= 0 && n < BitLen) {
        return (pMem[n >> 5] & (1 << (n & (BitSize - 1)))) ? 1 : 0;
    }
    else {
        throw("Некорректный индекс!");
    }
}


const TBitField& TBitField::operator=(const TBitField &tmp) 
{
    if (this == &tmp) {
        return *this;
    }
    else {
        MemLen = tmp.MemLen;
        BitLen = tmp.BitLen;
        delete[] pMem;
        pMem = new TELEM[MemLen]();
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = tmp.pMem[i];
        }
    }
    return (*this);
}

int TBitField::operator==(const TBitField &tmp) const //
{
    if (this == &tmp) {
        return true;
    }
    else if (this->BitLen == tmp.BitLen) {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != tmp.pMem[i]) {
                return false;
            }
        }
        return true;
    }

  return false;
}

int TBitField::operator!=(const TBitField &tmp) const 
{
    return !((*this) == tmp);
}

TBitField TBitField::operator|(const TBitField &tmp) const
{   
    TBitField a(*this), b(tmp);
    PullForMax(a, b); //
    TBitField res(a.BitLen);
    for (int i = 0; i < a.MemLen; i++) {
        res.pMem[i] = a.pMem[i] | b.pMem[i];
    }

    return res;
}

TBitField TBitField::operator&(const TBitField &tmp)  const
{
    TBitField a(*this), b(tmp);
    PullForMax(a, b);//
    TBitField res(a.BitLen);
    for (int i = 0; i < a.MemLen; i++) {
        res.pMem[i] = a.pMem[i] & b.pMem[i];
    }

    return res;
}

TBitField TBitField::operator~(void) const
{
    TBitField res(BitLen); 
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~(this->pMem[i]);
    }

    int used = BitLen % BitSize;
    if (used != 0) {
        TELEM mask = (1 << used) - 1;
        res.pMem[MemLen - 1] &= mask;
    }
    return res;
}

istream &operator>>(istream &is, TBitField &tmp) 
{
    char c;
    for (int i = 0; i < tmp.BitLen; i++) {
        is >> c;
        if (c == '1') tmp.SetBit(i);
        else tmp.ClrBit(i);
    }
    return is;
}

ostream &operator<<(ostream &os, const TBitField &tmp) 
{
    for (int i = 0; i < tmp.BitLen; i++) {
        os << tmp.GetBit(i);
    }
    return os;
}

void PullForMax(TBitField& tmp1, TBitField& tmp2)
{
    int max_size = (tmp1.BitLen > tmp2.BitLen) ? tmp1.BitLen : tmp2.BitLen;

    if (tmp1.BitLen < max_size) {
        TBitField buff(max_size);
        for (int i = 0; i < tmp1.BitLen; i++)
            if (tmp1.GetBit(i)) buff.SetBit(i);
        tmp1 = buff;
    }
    if (tmp2.BitLen < max_size) {
        TBitField buff(max_size);
        for (int i = 0; i < tmp2.BitLen; i++)
            if (tmp2.GetBit(i)) buff.SetBit(i);
        tmp2 = buff;
    }
}