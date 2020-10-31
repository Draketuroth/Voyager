#ifndef VE_VECTOR_BASE_H
#define VE_VECTOR_BASE_H

#include "Voyager/Math/Utils.h"

namespace VE 
{
    namespace Math 
    {
        namespace Vector 
        {
            template<class T>
            struct Base : public T
            {
                Base() {
                    _dimension = sizeof(T) / sizeof(float);
                }

                inline float& operator[](const int i) { return ((float*)this)[i]; }
                inline const float evaluate(const int i) const { return ((float*)this)[i]; }
                inline const unsigned int getDimension() const { return _dimension; }

                template<class B>
                inline float dot(const B & b) const
                {
                    float dp = 0.0f;
                    if (_dimension == b.getDimension())
                    {
                        const unsigned int range = clamp(_dimension, 0, 3);
                        for (unsigned int i = 0; i < range; i++)
                            dp += ((float*)this)[i] * b.evaluate(i);
                    }
                    return dp;
                }

                inline float magnitude() const;

                template<class T>
                inline Base<T> normalized() const 
                {
                    float inverseMagnitude = 1.0f / this->magnitude();
                    return inverseMagnitude * (*this);
                }

                template<class T>
                Base<T>& operator=(const Base<T> &other)
                {
                    for (unsigned int i = 0; i < _dimension; i++)
                        ((float*)this)[i] = other.evaluate(i);

                    return *this;
                }

                template<class T>
                Base<T>& operator+=(const Base<T>& other)
                {
                    const unsigned int range = clamp(_dimension, 0, 3);
                    for (unsigned int i = 0; i < range; i++)
                        ((float*)this)[i] += other.evaluate(i);

                    return *this;
                }

                template<class T>
                Base<T>& operator-=(const Base<T>& other)
                {
                    const unsigned int range = clamp(_dimension, 0, 3);
                    for (unsigned int i = 0; i < _dimension; i++)
                        ((float*)this)[i] -= other.evaluate(i);

                    return *this;
                }

            private:
                unsigned int _dimension;
            };
            
            template<class A, class B>
            inline float dot(const A& a, const B& b)
            {
                float dp = 0.0f;
                if (a.getDimension() == b.getDimension())
                {
                    const unsigned int range = clamp(a.getDimension(), 0, 3);
                    for (unsigned int i = 0; i < range; i++)
                        dp += a.evaluate(i) * b.evaluate(i);
                }
                return dp;
            }

            template<class T>
            inline Base<T> normalize(const Base<T>& v) 
            {
                float inverseMagnitude = 1.0f / v.magnitude();
                return inverseMagnitude * v;
            }

            template<class T>
            inline float Base<T>::magnitude() const
            {
                return sqrt(this->dot(*this));
            }

            template<class T>
            inline Base<T> operator-(const Base<T>& left, const Base<T>& right) 
            {
                Base<T> ret;
                const unsigned int range = clamp(left.getDimension(), 0, 3);
                for (unsigned int i = 0; i < range; i++)
                    ret[i] = left.evaluate(i) - right.evaluate(i);
                return ret;
            }

            template<class T>
            inline Base<T> operator+(const Base<T>& left, const Base<T>& right)
            {
                Base<T> ret;
                const unsigned int range = clamp(left.getDimension(), 0, 3);
                for (unsigned int i = 0; i < range; i++)
                    ret[i] = left.evaluate(i) + right.evaluate(i);
                return ret;
            }

            template<class T>
            inline Base<T> operator*(float scalar, const Base<T>& vector)
            {
                Base<T> ret;
                const unsigned int range = clamp(vector.getDimension(), 0, 3);
                for (unsigned int i = 0; i < range; i++)
                    ret[i] = scalar * vector.evaluate(i);
                return ret;
            }

            template<class T>
            inline Base<T> operator*(const Base<T>& left, const Base<T>& right)
            {
                Base<T> ret;
                const unsigned int range = clamp(left.getDimension(), 0, 3);
                for (unsigned int i = 0; i < range; i++)
                    ret[i] = left.evaluate(i) * right.evaluate(i);
                return ret;
            }
        }
    }
}

#endif