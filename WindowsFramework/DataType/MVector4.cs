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
        private static Dictionary<int, MVector4> m_storage = new Dictionary<int, MVector4>();
        private static int m_IDCounter = 0;

        private Vector4 m_vector;
        public int m_ID;
        
        private MVector4(float x, float y, float z, float w)
        {
            m_vector = new Vector4(x, y, z, w); 
            MVector4 instance = this;
            addToStorage(ref instance);
        }

        private MVector4()
        {
            m_vector = new Vector4(0.0f);
            MVector4 instance = this;
            addToStorage(ref instance);
        }

        private MVector4(MVector4 vec)
        {
            m_vector = new Vector4(vec.m_vector.X, vec.m_vector.Y, vec.m_vector.Z, vec.m_vector.W);
            MVector4 instance = this;
            addToStorage(ref instance);
        }

        public static int create()
        {
            MVector4 instance = new MVector4();
            return instance.m_ID;
        }

        public static int create(float x, float y, float z, float w)
        {
            MVector4 instance = new MVector4(x, y, z, w);
            return instance.m_ID;
        }

        public static int createCopy(int ID)
        {
            MVector4 instance = new MVector4(getFromStorage(ID));
            return instance.m_ID;
        }

        public static void destroy(int ID)
        {
            if (m_storage.ContainsKey(ID))
            {
                m_storage.Remove(ID);
            }
        }

        private static void addToStorage(ref MVector4 vec)
        {
            while (m_storage.ContainsKey(m_IDCounter))
            {
                m_IDCounter = (m_IDCounter + 1) % int.MaxValue;
            }

            m_storage.Add(m_IDCounter, vec);
            vec.m_ID = m_IDCounter;
        }

        public static MVector4 getFromStorage(int ID)
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
