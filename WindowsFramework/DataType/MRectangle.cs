using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;

namespace WindowsFramework.DataType
{
    public class MRectangle
    {
        private static Dictionary<int, MRectangle> m_storage = new Dictionary<int, MRectangle>();
        private static int m_IDCounter = 0;

        private Rectangle m_rectangle;
        public int m_ID;

        private MRectangle()
        {
            m_rectangle = new Rectangle();
            MRectangle instance = this;
            addToStorage(ref instance);
        }

        private MRectangle(int left, int top, int right, int bottom)
        {
            m_rectangle = new Rectangle(left, top, right - left, bottom - top);
            MRectangle instance = this;
            addToStorage(ref instance);
        }

        private MRectangle(MRectangle rec)
        {
            m_rectangle = new Rectangle(rec.m_rectangle.Location, rec.m_rectangle.Size);
            MRectangle instance = this;
            addToStorage(ref instance);
        }

        public static int create()
        {
            MRectangle instance = new MRectangle();
            return instance.m_ID;
        }

        public static int create(int left, int top, int right, int bottom)
        {
            MRectangle instance = new MRectangle(left, top, right, bottom);
            return instance.m_ID;
        }

        public static int createCopy(int ID)
        {
            MRectangle instance = new MRectangle(getFromStorage(ID));
            return instance.m_ID;
        }

        public static void destroy(int ID)
        {
            if (m_storage.ContainsKey(ID))
            {
                m_storage.Remove(ID);
            }
        }

        private static void addToStorage(ref MRectangle vec)
        {
            while (m_storage.ContainsKey(m_IDCounter))
            {
                m_IDCounter = (m_IDCounter + 1) % int.MaxValue;
            }

            m_storage.Add(m_IDCounter, vec);
            vec.m_ID = m_IDCounter;
        }

        public static MRectangle getFromStorage(int ID)
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
        
        public Rectangle getRawData()
        {
            return m_rectangle;
        }
    }
}
