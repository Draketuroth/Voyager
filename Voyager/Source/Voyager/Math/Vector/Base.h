#ifndef VE_VECTOR_BASE_H
#define VE_VECTOR_BASE_H

namespace VE 
{
    namespace Math 
    {
        namespace Vector 
        {
            template<int dimensions, class T>
            struct Base : public T
            {

            };
        }
    }
}

#endif