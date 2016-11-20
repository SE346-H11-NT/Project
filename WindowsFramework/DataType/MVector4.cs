using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;

namespace WindowsFramework.DataType
{
    public class MVector4
    {
        private Vector4 m_vector;

        public MVector4() 
        {
            m_vector = new Vector4(0.0f);
        }

        public MVector4(float x, float y, float z, float w)
        {
            m_vector = new Vector4(x, y, z, w);
        }

        public Vector4 getRawData()
        {
            return m_vector;
        }

        public Color getColor()
        {
            return new Color(m_vector);
        }
    }
}
