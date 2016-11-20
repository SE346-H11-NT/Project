using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;

namespace WindowsFramework.DataType
{
    public class MMatrix
    {
        private Microsoft.Xna.Framework.Matrix m_matrix;

        public MMatrix()
        {
            m_matrix = new Matrix();
            m_matrix = Matrix.Identity;
        }

        public MMatrix(MMatrix mat)
        {
            m_matrix = new Matrix();
            m_matrix = mat.m_matrix;
        }

        public MMatrix multiply(MMatrix mat)
        {
            MMatrix result = new MMatrix();
            result.m_matrix = m_matrix * mat.m_matrix;
            return result;
        }

        public Microsoft.Xna.Framework.Matrix getRawData()
        {
            return m_matrix;
        }

        public void scaling(float sx, float sy, float sz)
        {
            Microsoft.Xna.Framework.Matrix.CreateScale(sx, sy, sz, out this.m_matrix);
        }

        public void translation(float tx, float ty, float tz)
        {
            Microsoft.Xna.Framework.Matrix.CreateTranslation(tx, ty, tz, out this.m_matrix);
        }

        public void identity()
        {
            this.m_matrix = Microsoft.Xna.Framework.Matrix.Identity;
        }
    }
}
