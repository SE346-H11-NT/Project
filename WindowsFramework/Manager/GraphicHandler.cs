using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using WindowsFramework.Graphic;

namespace WindowsFramework.Manager
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class GraphicHandler
    {
        private GraphicsDeviceManager m_graphics;
        private SpriteBatch m_spriteBatch;
        private Game m_gameInstance;
        private GraphicHandler m_thisRef;

        static public GraphicHandler getInstance()
        {
            if (m_instance == null)
            {
                m_instance = new GraphicHandler();
            }

            return m_instance;
        }

        public T loadContent<T>(string path)
        {
            return m_gameInstance.Content.Load<T>(path);
        }
        

        public SpriteBatch getSpriteBatch()
        {
            return m_spriteBatch;
        }

        public GraphicsDeviceManager getGraphicDeviceManager()
        {
            return m_graphics;
        }

        public Game getGameInstance()
        {
            return m_gameInstance;
        }

        public void setGameInstance(ref Game gameInstance)
        {
            m_gameInstance = gameInstance;
            m_graphics = new GraphicsDeviceManager(m_gameInstance);
        }

        public void createSpriteBatch()
        {
            m_spriteBatch = new SpriteBatch(m_gameInstance.GraphicsDevice);
        }

        public void beginDraw()
        {
            m_graphics.BeginDraw();
            m_spriteBatch.Begin();
            m_gameInstance.GraphicsDevice.Clear(Color.CornflowerBlue);
        }

        public void endDraw()
        {
            m_spriteBatch.End();
            m_graphics.EndDraw();
        }

        // PRIVATE SECTION
        private GraphicHandler() {
            m_thisRef = this;
            MTexture.setGraphicHandler(ref m_thisRef);
        }

        static GraphicHandler m_instance = null;
        // ====================================================================
    }
}
