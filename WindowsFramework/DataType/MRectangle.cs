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
        private Rectangle m_rectangle;

        public MRectangle()
        {

        }

        public MRectangle(int left, int top, int right, int bottom)
        {
            m_rectangle = new Rectangle(left, top, right - left, bottom - top);
        }

        public Rectangle getRawData()
        {
            return m_rectangle;
        }
    }
}
