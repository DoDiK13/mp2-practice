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
    memset(pMem, 0, sizeof(TELEM) * MemLen);
    
}

TBitField::TBitField(const TBitField &tmp) 
{
    BitLen = tmp.BitLen;
    MemLen = tmp.MemLen;
    pMem = new TELEM[MemLen];
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
    if (n < 0 || n >= BitLen) {
        throw("Некорректный индекс!");
    }
    return n >> BitShift;
    
}

TELEM TBitField::GetMemMask(const int n) const
{
    if (n < 0 || n >= BitLen) {
        throw("Некорректный индекс!");
    }
    return 1 << (n & (BitSize - 1));
}

int TBitField::GetLength(void) const 
{
  return BitLen;
}

void TBitField::SetBit(const int n) 
{
    if (n < 0 || n >= BitLen) {
        throw("Некорректный индекс!");
    }
    pMem[n >> BitShift] |= (1 << (n & (BitSize - 1)));
}

void TBitField::ClrBit(const int n) 
{
    if (n < 0 || n >= BitLen) {
        throw("Некорректный индекс!");
    }
    pMem[n >> BitShift] &= ~(1 << (n & (BitSize - 1)));
    
}

int TBitField::GetBit(const int n) const 
{
    if (n < 0 || n >= BitLen) {
        throw("Некорректный индекс!");
    }
    return (pMem[n >> BitShift] & (1 << (n & (BitSize - 1)))) ? 1 : 0;
}


const TBitField& TBitField::operator=(const TBitField &tmp) 
{
    if (this == &tmp) {
        return *this;
    }
    else {
        if (MemLen != tmp.MemLen) {
            MemLen = tmp.MemLen;
            delete[] pMem;
            pMem = new TELEM[MemLen];
        }
        BitLen = tmp.BitLen;
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = tmp.pMem[i];
        }
    }
    return (*this);
}

int TBitField::operator==(const TBitField &tmp) const 
{
    if (this->BitLen == tmp.BitLen) {
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

TBitField TBitField::operator|(const TBitField& tmp) const
{
    if (BitLen > tmp.BitLen) {
        TBitField res(BitLen);
        for (int i = 0; i < tmp.BitLen; i++) {
            if (GetBit(i) | tmp.GetBit(i)) res.SetBit(i);
        }
        for (int i = tmp.BitLen; i < BitLen; i++) {
            if (GetBit(i)) res.SetBit(i);
        }
        return res;
    }
    else {
        TBitField res(tmp.BitLen);
        for (int i = 0; i < BitLen; i++) {
            if (GetBit(i) | tmp.GetBit(i)) res.SetBit(i);
        }
        for (int i = BitLen; i < tmp.BitLen; i++) {
            if (tmp.GetBit(i)) res.SetBit(i);
        }
        return res;
    }
}

TBitField TBitField::operator&(const TBitField& tmp) const
{
    int minLen = (BitLen < tmp.BitLen) ? BitLen : tmp.BitLen;
    TBitField res(minLen);

    for (int i = 0; i < minLen; i++) {
        if (GetBit(i) & tmp.GetBit(i)) res.SetBit(i);
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