#pragma once

#include "Camera.hpp"
#include "SpaceEntity.hpp"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

struct GlobalData;

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

    bool areAllInactive(void)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T& t = mArray[i];

            if (t.isActive())
            {
                return false;
            }
        }

        return true;
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
                return &t;
            }

            if (i == mLast)
            {
                break;
            }
        }

        return nullptr;
    }

    void Update(GlobalData& data)
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

    void collision(SpaceEntity& other)
    {
        if (other.isActive())
        {
            for (size_t i = 0; i < count(); i++)
            {
                T* const entptr = dynamic_cast<T*>(get(i));

                if (entptr)
                {
                    T& entity = *entptr;

                    if (entity.isActive())
                    {
                        if (other.isCollidingWith(entity))
                        {
                            entity.injured();
                            other.setActive(false);
                            break;
                        }
                    }
                }
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

    void setActive(const bool state)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T& t = mArray[i];

            t.setActive(state);
        }
    }

private:
    const size_t mSize;
    size_t mLast;
    T *const mArray;
};
