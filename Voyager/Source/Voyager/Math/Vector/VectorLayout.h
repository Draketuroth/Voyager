#ifndef VE_VECTOR_LAYOUT_H
#define VE_VECTOR_LAYOUT_H

namespace VE
{
    namespace Math
    {
        namespace Vector 
        {
            struct LayoutXYZW 
            {
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                float w = 1.0f;
            };

            struct LayoutXYZ
            {
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
            };

            struct LayoutXY
            {
                float x = 0.0f;
                float y = 0.0f;
            };

            struct LayoutUV
            {
                float u = 0.0f;
                float v = 0.0f;
            };
        }
    }
}

#endif