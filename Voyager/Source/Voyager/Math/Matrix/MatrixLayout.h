#ifndef VE_MATRIX_LAYOUT_H
#define VE_MATRIX_LAYOUT_H

namespace VE
{
    namespace Math
    {
        namespace Matrix
        {
            struct Layout2x2 
            {
                float m[2][2];
            };

            struct Layout2x3
            {
                float m[2][3];
            };

            struct Layout3x3
            {
                float m[3][3];
            };

            struct Layout4x4
            {
                float m[4][4];
            };
        }
    }
}

#endif