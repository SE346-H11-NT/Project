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
    public class MTexture
    {
        private Texture2D m_texture;
        static private GraphicHandler m_graphicHandlerRef;

        static public void setGraphicHandler(ref GraphicHandler handler)
        {
            m_graphicHandlerRef = handler;
        }

        public MTexture(string path)
        {
            m_texture = m_graphicHandlerRef.loadContent<Texture2D>(path);
        }

        public void draw(MVector3 pos, MRectangle srcRect, MVector2 scale,
            MVector2 translate, MVector3 drawCenter, float angle, MVector4 color)
        {
            //m_graphicHandlerRef.getSpriteBatch().Draw(m_texture, m_graphicHandlerRef.getGameInstance().Window.ClientBounds, Color.White);

            Rectangle? rect;
            if (srcRect.Equals(null))
            {
                rect = srcRect.getRawData();
            }
            else
            {
                rect = null;
            }

            m_graphicHandlerRef.getSpriteBatch()
                .Draw(
                m_texture, 
                pos.getRawVec2(),
                rect,
                color.getColor(), 
                angle, 
                drawCenter.getRawVec2(), 
                scale.getRawData(), 
                SpriteEffects.None, 
                0.0f);
        }

        public int getWidth()
        {
            return m_texture.Width;
        }

        public int getHeight()
        {
            return m_texture.Height;
        }
    }
}
