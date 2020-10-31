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
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                float w = 1.0f;
            };

            struct DescXYZ
            {
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
            };

            struct DescXY
            {
                float x = 0.0f;
                float y = 0.0f;
            };

            struct DescUV
            {
                float u = 0.0f;
                float v = 0.0f;
            };
        }
    }
}

#endif