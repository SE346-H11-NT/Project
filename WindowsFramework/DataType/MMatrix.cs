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
        private static Dictionary<int, MMatrix> m_storage = new Dictionary<int,MMatrix>();
        private static int m_IDCounter = 0;

        public  Microsoft.Xna.Framework.Matrix m_matrix;
        public int m_ID;

        private MMatrix()
        {
            m_matrix = new Matrix();
            m_matrix = Matrix.Identity;
            MMatrix instance = this;
            addMatrix(ref instance);
        }

        private MMatrix(MMatrix mat)
        {
            m_matrix = new Matrix();
            m_matrix = mat.m_matrix;
            MMatrix instance = this;
            addMatrix(ref instance);
        }

        public static int createMatrix()
        {
            MMatrix instance = new MMatrix();
            return instance.m_ID;
        }

        public static int createCopyMatrix(int ID)
        {
            MMatrix instance = new MMatrix();
            instance.m_matrix = getFromStorage(ID).m_matrix;
            return instance.m_ID;
        }

        public static void destroyMatrix(int ID)
        {
            if (m_storage.ContainsKey(ID))
            {
                m_storage.Remove(ID);
            }
        }

        private static void addMatrix(ref MMatrix mat)
        {
            while (m_storage.ContainsKey(m_IDCounter))
            {
                m_IDCounter = (m_IDCounter + 1) % int.MaxValue;
            }

            m_storage.Add(m_IDCounter, mat);
            mat.m_ID = m_IDCounter;
        }

        public static MMatrix getFromStorage(int ID)
        {
            if (m_storage.ContainsKey(ID))
            {
                return m_storage[ID];
            }
            else
            {
                return null;
            }
        }

        public int multiply(int matID)
        {
            MMatrix result = new MMatrix();
            result.m_matrix = m_matrix * MMatrix.getFromStorage(matID).m_matrix;
            return result.m_ID;
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
