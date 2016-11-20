using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;

using WindowsFramework.DataType;

namespace WindowsFramework.DataType
{
    public class MVector2
    {
        public MVector2()
        {
            m_vector = new Vector2(0.0f);
        }

        public MVector2(float x, float y)
        {
            m_vector = new Vector2(x, y);
        }

        public Vector2 getRawData()
        {
            return m_vector;
        }

        private Vector2 m_vector;
    }
}
