#ifndef VE_VECTOR_BASE_H
#define VE_VECTOR_BASE_H

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
                        for (unsigned int i = 0; i < _dimension; i++)
                            dp += ((float*)this)[i] * b.evaluate(i);
                    }
                    return dp;
                }

                inline float magnitude() const;

            private:
                unsigned int _dimension;
            };

            
            template<class A, class B>
            inline float dot(const A& a, const B& b)
            {
                float dp = 0.0f;
                if (a.getDimension() == b.getDimension())
                {
                    const unsigned int dimension = a.getDimension();
                    for (unsigned int i = 0; i < dimension; i++)
                        dp += a.evaluate(i) * b.evaluate(i);
                }
                return dp;
            }

            template<class T>
            inline float Base<T>::magnitude() const
            {
                return sqrt(this->dot(*this));
            }
        }
    }
}

#endif