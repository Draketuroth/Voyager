#ifndef VE_VECTOR_DESCRIPTOR_H
#define VE_VECTOR_DESCRIPTOR_H

namespace VE
{
    namespace Math
    {
        namespace Vector 
        {
            struct DescXYZW 
            {
                float x;
                float y;
                float z;
                float w;
            };

            struct DescXYZ
            {
                float x;
                float y;
                float z;
            };

            struct DescXY
            {
                float x;
                float y;
            };

            struct DescUV
            {
                float u;
                float v;
            };
        }
    }
}

#endif