using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using WindowsFramework.Manager;

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

        public void draw()
        {
            m_graphicHandlerRef.getSpriteBatch().Draw(m_texture, m_graphicHandlerRef.getGameInstance().Window.ClientBounds, Color.White);
        }
    }
}
