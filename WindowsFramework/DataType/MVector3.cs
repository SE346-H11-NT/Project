using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;

using WindowsFramework.DataType;

namespace WindowsFramework.DataType
{
    public class MVector3
    {
        public MVector3()
        {
            m_vector = new Vector3(0.0f);
        }

        public MVector3(float x, float y, float z)
        {
            m_vector = new Vector3(x, y, z);
        }

        public MVector3 multiply(MMatrix mat)
        {
            MVector3 result = new MVector3();
            result.m_vector = Vector3.Transform(m_vector, mat.getRawData());
            return result;
        }

        public Vector2 getRawVec2()
        {
            return new Vector2(m_vector.X, m_vector.Y);
        }

        public float getX() { return m_vector.X; }
        public float getY() { return m_vector.Y; }
        public float getZ() { return m_vector.Z; }

        private Vector3 m_vector;
    }
}
