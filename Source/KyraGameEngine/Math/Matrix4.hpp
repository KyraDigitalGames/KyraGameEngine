
#ifndef KYRAGAMEENGINE_MATH_MATRIX4_HPP
#define KYRAGAMEENGINE_MATH_MATRIX4_HPP

namespace kyra {

    class Matrix4 {

        float m_Data[16]; // Column-Major Layout

    public:
        Matrix4() : m_Data{ 1.f, 0.f, 0.f, 0.f,
                           0.f, 1.f, 0.f, 0.f,
                           0.f, 0.f, 1.f, 0.f,
                           0.f, 0.f, 0.f, 1.f }
        {

        }

        static Matrix4 ortho(float left, float right,
            float bottom, float top,
            float nearVal, float farVal) {
            Matrix4 m{};
            m.m_Data[0] = 2.0f / (right - left);
            m.m_Data[5] = 2.0f / (top - bottom);
            m.m_Data[10] = -2.0f / (farVal - nearVal);
            m.m_Data[12] = -(right + left) / (right - left);
            m.m_Data[13] = -(top + bottom) / (top - bottom);
            m.m_Data[14] = -(farVal + nearVal) / (farVal - nearVal);
            m.m_Data[15] = 1.0f;
            return m;
        }

        const float* getDataPtr() const {
            return m_Data;
        }
    };

}

#endif