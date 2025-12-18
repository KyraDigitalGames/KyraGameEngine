
#ifndef KYRAGAMEENGINE_MATH_MATRIX4_HPP
#define KYRAGAMEENGINE_MATH_MATRIX4_HPP

#include "Vector3.hpp"
#include "Vector2.hpp"

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

        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 result;
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    result.m_Data[col + row * 4] =
                        m_Data[0 + row * 4] * other.m_Data[col + 0 * 4] +
                        m_Data[1 + row * 4] * other.m_Data[col + 1 * 4] +
                        m_Data[2 + row * 4] * other.m_Data[col + 2 * 4] +
                        m_Data[3 + row * 4] * other.m_Data[col + 3 * 4];
                }
            }
            return result;
		}

        Matrix4& operator*=(const Matrix4& other) {
            *this = *this * other;
            return *this;
		}

        Matrix4 transpose() const {
            Matrix4 result;
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    result.m_Data[row + col * 4] = m_Data[col + row * 4];
                }
            }
            return result;
		}

        Matrix4 translate(const Vector3<float>& vec) const {
            Matrix4 translation;
            translation.m_Data[12] = vec.getX();
            translation.m_Data[13] = vec.getY();
            translation.m_Data[14] = vec.getZ();
            return (*this) * translation;
        }
        
        Matrix4 translate(const Vector2<float>& vec) const {
            Matrix4 translation;
            translation.m_Data[12] = vec.getX();
            translation.m_Data[13] = vec.getY();
            translation.m_Data[14] = 0;
            return (*this) * translation;
        }

        Matrix4 scale(const Vector3<float>& vec) const {
            Matrix4 scaling;
            scaling.m_Data[0] = vec.getX();
            scaling.m_Data[5] = vec.getY();
            scaling.m_Data[10] = vec.getZ();
            return (*this) * scaling;
        }
        
        Matrix4 scale(const Vector2<float>& vec) const {
            Matrix4 scaling;
            scaling.m_Data[0] = vec.getX();
            scaling.m_Data[5] = vec.getY();
            scaling.m_Data[10] = 1;
            return (*this) * scaling;
        }

        const float* getDataPtr() const {
            return m_Data;
        }
    };

}

#endif