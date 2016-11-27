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
        private static Dictionary<int, MVector2> m_storage = new Dictionary<int, MVector2>();
        private static int m_IDCounter = 0;

        private Vector2 m_vector;
        public int m_ID;

        private MVector2(float x, float y)
        {
            m_vector = new Vector2(x, y); 
            MVector2 instance = this;
            addToStorage(ref instance);
        }

        private MVector2()
        {
            m_vector = new Vector2(0.0f);
            MVector2 instance = this;
            addToStorage(ref instance);
        }

        private MVector2(MVector2 vec)
        {
            m_vector = new Vector2(vec.m_vector.X, vec.m_vector.Y);
            MVector2 instance = this;
            addToStorage(ref instance);
        }

        public static int create()
        {
            MVector2 instance = new MVector2();
            return instance.m_ID;
        }

        public static int create(float x, float y)
        {
            MVector2 instance = new MVector2(x, y);
            return instance.m_ID;
        }

        public static int createCopy(int ID)
        {
            MVector2 instance = new MVector2(getFromStorage(ID));
            return instance.m_ID;
        }

        public static void destroy(int ID)
        {
            if (m_storage.ContainsKey(ID))
            {
                m_storage.Remove(ID);
            }
        }

        private static void addToStorage(ref MVector2 vec)
        {
            while (m_storage.ContainsKey(m_IDCounter))
            {
                m_IDCounter = (m_IDCounter + 1) % int.MaxValue;
            }

            m_storage.Add(m_IDCounter, vec);
            vec.m_ID = m_IDCounter;
        }

        public static MVector2 getFromStorage(int ID)
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

        public Vector2 getRawData()
        {
            return m_vector;
        }
    }
}
