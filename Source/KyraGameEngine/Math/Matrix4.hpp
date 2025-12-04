#ifndef KYRAGAMEENGINE_MATH_MATRIX4_HPP
#define KYRAGAMEENGINE_MATH_MATRIX4_HPP

#include <array>

namespace kyra {
  
  class Matrix4 {

    std::array<std::array<float,4>,4> m_Data;

    public:
    Matrix4() {
      m_Data[0] = {1,0,0,0};
      m_Data[1] = {0,1,0,0};
      m_Data[2] = {0,0,1,0};
      m_Data[3] = {0,0,0,1};
    }
  
    static Matrix4 ortho(float left, float right,
                                          float bottom, float top,
                                          float nearVal, float farVal) 
    {
      Matrix4 m{};
      m.m_Data[0][0] = 2.0f / (right - left);
      m.m_Data[1][1] = 2.0f / (top - bottom);
      m.m_Data[2][2] = -2.0f / (farVal - nearVal);
      m.m_Data[3][3] = 1.0f;
      m.m_Data[0][3] = -(right + left) / (right - left);
      m.m_Data[1][3] = -(top + bottom) / (top - bottom);
      m.m_Data[2][3] = -(farVal + nearVal) / (farVal - nearVal);
      return m;
    }

    const float* getDataPtr() const {
        return &m_Data[0][0];
    }

    
  };
  
}

#endif