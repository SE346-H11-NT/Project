using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using WindowsFramework.Manager;
using WindowsFramework.DataType;

namespace WindowsFramework.Graphic
{
    public class MText
    {
        private static GraphicHandler m_graphicHandlerRef;
        private static SpriteFont m_spriteFont;

        private const int DT_LEFT      = 0x00000000;
        private const int DT_CENTER = 0x00000001;
        private const int DT_RIGHT = 0x00000002;
        
        static public void setGraphicHandler(ref GraphicHandler handler)
        {
            m_graphicHandlerRef = handler;
        }

        static public void loadFont(String path)
        {
            m_spriteFont = m_graphicHandlerRef.loadContent<SpriteFont>(path);
        }

        public static void drawText(String content, int posID, int colorID, int dockType)
        {
            Vector2 stringSize = m_spriteFont.MeasureString(content);
            Vector2 position = MVector3.getFromStorage(posID).getRawVec2();
            Vector2 origin;

            switch (dockType)
            {
                case DT_LEFT:
                    origin = new Vector2(0.0f, 0.0f);
                    break;

                case DT_CENTER:
                    position.X -= stringSize.X / 2.0f;
                    origin = new Vector2(stringSize.X / 2.0f, 0.0f);
                    break;

                case DT_RIGHT:
                    position.X -= stringSize.X;
                    origin = new Vector2(stringSize.X, 0.0f);
                    break;

                default:
                    break;
            }

            m_graphicHandlerRef.getSpriteBatch().DrawString(m_spriteFont, content, position, MVector4.getFromStorage(colorID).getColor());
        }
    }
}
