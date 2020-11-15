#ifndef VE_MATRIX_BASE_H
#define VE_MATRIX_BASE_H

#include "Voyager/Math/Utils.h"

#include <iostream>

namespace VE
{
    namespace Math
    {
        namespace Matrix
        {
            enum class Mode : unsigned int
            {
                ROW = 0u,
                COLUMN = 1u
            };

            template<class T>
            struct Base : public T
            {
                Base() {
                    m_mode = Mode::ROW;
                    m_rows = sizeof(T::m) / sizeof(T::m[0]);
                    m_columns = sizeof(T::m[0]) / sizeof(float);
                }

                Mode m_mode;
                unsigned int m_rows;
                unsigned int m_columns;
            };

            
            template<class T>
            inline Base<T> multColumn(const Base<T>& A, const Base<T>& B) 
            {
                Base<T> C;
                return C;
            }

            template<class T>
            inline Base<T> multRow(const Base<T>& A, const Base<T>& B)
            {
                Base<T> C;
                if (A.m_columns == B.m_rows) 
                {
                    unsigned int ra = A.m_rows;
                    unsigned int ca = A.m_columns;

                    unsigned int rb = B.m_rows;
                    unsigned int cb = B.m_columns;

                    for (unsigned int i = 0u; i < ra; ++i)
                    {
                        for (unsigned int j = 0u; j < cb; ++j)
                        {
                            float val = 0.0f;
                            for (unsigned int k = 0u; k < ca; ++k)
                            {
                                val += A.m[i][k] * B.m[k][j];
                            }
                            C.m[i][j] = val;
                        }
                    }
                }  
                return C;
            }

            template<class T>
            inline Base<T> multiply(const Base<T>& A, const Base<T>& B, Base<T>(*F)(const Base<T>&, const Base<T>&))
            {
                return (*F)(A, B);
            }

            template<class T>
            inline Base<T> operator*(const Base<T>& a, const Base<T>& b)
            {
                return a.m_mode == Mode::COLUMN ? multiply(a, b, multColumn) : multiply(a, b, multRow);
            }
            
        }
    }
}

#endif