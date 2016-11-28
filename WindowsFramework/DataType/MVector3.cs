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
        private static Dictionary<int, MVector3> m_storage = new Dictionary<int, MVector3>();
        private static int m_IDCounter = 0;

        private Vector3 m_vector;
        public int m_ID;

        private MVector3(float x, float y, float z)
        {
            m_vector = new Vector3(x, y, z); 
            MVector3 instance = this;
            addToStorage(ref instance);
        }

        private MVector3()
        {
            m_vector = new Vector3(0.0f);
            MVector3 instance = this;
            addToStorage(ref instance);
        }

        private MVector3(MVector3 vec)
        {
            m_vector = new Vector3(vec.m_vector.X, vec.m_vector.Y, vec.m_vector.Z);
            MVector3 instance = this;
            addToStorage(ref instance);
        }

        public static int create()
        {
            MVector3 instance = new MVector3();
            return instance.m_ID;
        }

        public static int create(float x, float y, float z)
        {
            MVector3 instance = new MVector3(x, y, z);
            return instance.m_ID;
        }

        public static int createCopy(int ID)
        {
            MVector3 instance = new MVector3(getFromStorage(ID));
            return instance.m_ID;
        }

        public static void destroy(int ID)
        {
            if (m_storage.ContainsKey(ID))
            {
                m_storage.Remove(ID);
            }
        }

        private static void addToStorage(ref MVector3 vec)
        {
            while (m_storage.ContainsKey(m_IDCounter))
            {
                m_IDCounter = (m_IDCounter + 1) % int.MaxValue;
            }

            m_storage.Add(m_IDCounter, vec);
            vec.m_ID = m_IDCounter;
        }

        public static MVector3 getFromStorage(int ID)
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
            MVector3 result = new MVector3();
            result.m_vector = Vector3.Transform(m_vector, MMatrix.getFromStorage(matID).getRawData());
            return result.m_ID;
        }

        public Vector2 getRawVec2()
        {
            return new Vector2(m_vector.X, m_vector.Y);
        }

        public float getX() { return m_vector.X; }
        public float getY() { return m_vector.Y; }
        public float getZ() { return m_vector.Z; }
    }
}
