#pragma once

#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class TArray
{
public:
    TArray()
    {
        Arr = new T[BaseCapacity];
    }
    
    virtual ~TArray()
    {
        delete[] Arr;
    }
    
    T& operator[](int Idx)
    {
        return Arr[Idx];
    }

    int Num()
    {
        return Size;
    }
    
public:
    void Reserve(int NewCapacity)
    {
        if(ChangeCapacity(NewCapacity))
        {
            if(Size > Capacity)
            {
                Size = Capacity;
            }
            
            T* NewArr = new T[NewCapacity];
            
            for(int i = 0; i < Size; ++i)
            {
                NewArr[i] = Arr[i];
            }
            delete[] Arr;
            Arr = NewArr;
        }
    }
    
    void Resize(int NewSize ,const T& Val)
    {
        if(ChangeCapacity(NewSize))
        {
            T* NewArr = new T[Capacity];
            for(int i = 0; i < min(NewSize, Size); ++i)
            {
                NewArr[i] = Arr[i];
            }

            delete[] Arr;

            for(int i = min(NewSize, Size); i < NewSize; ++i)
            {
                NewArr[i] = Val;
            }

            Arr = NewArr;
        }
        else
        {
            for(int i = Size; i <NewSize; ++i)
            {
                Arr[i] = Val;
            }
            Size = NewSize;
        }
    }
    
    void PushBack(const T& Elem)
    {
        if(Size != Capacity)
        {
            Arr[Size++] = Elem;
        }
        else
        {
            if(ChangeCapacity(Capacity*2))
            {
                T* NewArr = new T[Capacity];
                for(int i = 0; i < Size; ++i)
                {
                    NewArr[i] = Arr[i];
                }

                delete[] Arr;

                Arr = NewArr;
                Arr[Size++] = Elem;
            }
        }
    }

    void PopBack()
    {
        delete Arr[Size];
        Arr[Size--] = nullptr;
    }

    template<typename Pr>
    void SortData(Pr InPr)
    {
        sort(begin(Arr), end(Arr), InPr);
    }

public:
    class Iterator {
    private:
        TArray& container;
        size_t index;

    public:
        Iterator(TArray& container, size_t startIndex = 0)
            : container(container), index(startIndex) {}
        
        T& operator*() {
            return container.Arr[index];
        }
        
        Iterator& operator++() {
            ++index;
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }
    };
    
    Iterator begin() {
        return Iterator(*this, 0);
    }

    Iterator end() {
        return Iterator(*this, Size);
    }
    

private:
    T* Arr;
    int Size = 0;
    int Capacity = 5;
    int BaseCapacity = 5;
    
    bool ChangeCapacity(int NewCapacity)
    {
        bool Ret = false;
        if(NewCapacity > Capacity)
        {
            while(Capacity < NewCapacity)
            {
                Capacity *= 2;
            }
            Ret = true;
        }
        else if(NewCapacity < Capacity)
        {
            while(Capacity > NewCapacity)
            {
                Capacity /= 2;
                if(Capacity <= BaseCapacity)
                {
                    Capacity = BaseCapacity;
                }
            }
            Ret = true;
        }

        return Ret;
    }
};