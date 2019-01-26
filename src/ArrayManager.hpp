#pragma once

#include "Camera.hpp"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

template<class T>
class ArrayManager
{
public:
    ArrayManager(const size_t size, T *const a) :
        mSize(size),
        mLast(0),
        mArray(a)
    {
        if (!a || !size)
        {
            printf("Invalid given information\n");
            while (1);
        }
    }

    T* AddElement(const T& element)
    {
        for (size_t i = mLast + 1; ; i++)
        {
            if (i >= mSize)
            {
                i = 0;
            }

            T& t = mArray[i];

            if (!t.isActive())
            {
                t = element;

                t.setActive(true);

                printf("Inserted element into offset %d\n", i);

                return &t;
            }
            else
            {
                printf("Offset %d is busy, mLast = %d\n", i, mLast);
            }

            if (i == mLast)
            {
                break;
            }
        }

        return nullptr;
    }

    void Update(void* const data)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T& t = mArray[i];

            if (t.isActive())
            {
                t.Update(data);
            }
        }
    }

    T *get(const size_t i) const
    {
        if (i < mSize)
        {
            return &mArray[i];
        }

        return nullptr;
    }

    size_t count(void) const
    {
        return mSize;
    }

    void render(const Camera& cam)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T& t = mArray[i];

            if (t.isActive())
            {
                t.render(cam);
            }
        }
    }

private:
    size_t mSize, mLast;
    T *const mArray;
};
