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
        private static GraphicHandler m_graphicHandlerRef;
        private static Dictionary<int, MTexture> m_storage = new Dictionary<int, MTexture>();
        private static int m_IDCounter = 0;

        private Texture2D m_texture;
        public int m_ID;
        
        static public void setGraphicHandler(ref GraphicHandler handler)
        {
            m_graphicHandlerRef = handler;
        }

        private MTexture()
        {
            MTexture instance = this;
            addToStorage(ref instance);
        }

        private MTexture(string path)
        {
            m_texture = m_graphicHandlerRef.loadContent<Texture2D>(path);
            MTexture instance = this;
            addToStorage(ref instance);
        }
        
        public static int create(string path)
        {
            MTexture instance = new MTexture(path);
            return instance.m_ID;
        }

        public static int createCopy(int ID)
        {
            MTexture instance = new MTexture();
            instance.m_texture = getFromStorage(ID).m_texture;
            return instance.m_ID;
        }

        public static void destroy(int ID)
        {
            if (m_storage.ContainsKey(ID))
            {
                m_storage.Remove(ID);
            }
        }

        private static void addToStorage(ref MTexture tex)
        {
            while (m_storage.ContainsKey(m_IDCounter))
            {
                m_IDCounter = (m_IDCounter + 1) % int.MaxValue;
            }

            m_storage.Add(m_IDCounter, tex);
            tex.m_ID = m_IDCounter;
        }

        public static MTexture getFromStorage(int ID)
        {
            return m_storage[ID];
        }

        //public void draw(MVector3 pos, MRectangle srcRect, MVector2 scale,
        //    MVector2 translate, MVector3 drawCenter, float angle, MVector4 color)
        public static void draw(int textureID, int pos, int srcRect, int scale,
        int translate, int drawCenter, float angle, int color)
        {
            //m_graphicHandlerRef.getSpriteBatch().Draw(m_texture, m_graphicHandlerRef.getGameInstance().Window.ClientBounds, Color.White);

            Rectangle? rect;
            MRectangle trueRect = MRectangle.getFromStorage(srcRect);
            if (trueRect != null)
            {
                rect = trueRect.getRawData();
            }
            else
            {
                rect = null;
            }

            m_graphicHandlerRef.getSpriteBatch()
                .Draw(
                MTexture.getFromStorage(textureID).m_texture,
                MVector3.getFromStorage(pos).getRawVec2(),
                rect,
                MVector4.getFromStorage(color).getColor(), 
                angle,
                MVector3.getFromStorage(drawCenter).getRawVec2(),
                MVector2.getFromStorage(scale).getRawData(), 
                SpriteEffects.None, 
                0.0f);
        }

        public static int getWidth(int ID)
        {
            return MTexture.getFromStorage(ID).m_texture.Width;
        }

        public static int getHeight(int ID)
        {
            return MTexture.getFromStorage(ID).m_texture.Height;
        }
    }
}
