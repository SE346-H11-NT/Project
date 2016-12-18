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

        private Matrix m_scale;
        public static float BUFFER_WIDTH = 256;
        public static float BUFFER_HEIGHT = 240;

        public static float SCREEN_WIDTH = 800;
        public static float SCREEN_HEIGHT = 600;

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

            m_graphics.PreferredBackBufferWidth = (int)SCREEN_WIDTH;
            m_graphics.PreferredBackBufferHeight = (int)SCREEN_HEIGHT;
            m_graphics.ApplyChanges();

            Vector3 scalingFactor = new Vector3(
                SCREEN_WIDTH / BUFFER_WIDTH,
                SCREEN_HEIGHT / BUFFER_HEIGHT,
                1.0f);

            m_scale = Matrix.CreateScale(scalingFactor);
        }

        public void createSpriteBatch()
        {
            m_spriteBatch = new SpriteBatch(m_gameInstance.GraphicsDevice);
        }

        public void beginDraw()
        {
            m_graphics.BeginDraw();
            m_spriteBatch.Begin(SpriteSortMode.Immediate, null, SamplerState.PointClamp, null, null, null, m_scale);
            m_gameInstance.GraphicsDevice.Clear(Color.Black);
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
