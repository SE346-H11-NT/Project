using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using System.Runtime.InteropServices;

using WindowsFramework.Manager;
using WindowsFramework.Graphic;

namespace MainApp
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class MainApp : Game
    {
        [DllImport("NativeLogic.dll")]
        public static extern void update(double deltaTime);

        private WindowsFramework.Manager.GraphicHandler m_graphicHandlerRef;
        private Game m_thisRef;

        private WindowsFramework.Graphic.MTexture m_testingTexture;
        public MainApp()
        {
            m_thisRef = this;
            m_graphicHandlerRef = GraphicHandler.getInstance();
            m_graphicHandlerRef.setGameInstance(ref m_thisRef);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            m_graphicHandlerRef.createSpriteBatch();
            // TODO: Add your initialization logic here

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // TODO: use this.Content to load your game content here
            m_testingTexture = new MTexture("Resource\\BillAndLance");
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// game-specific content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            // TODO: Add your update logic here
            update(gameTime.ElapsedGameTime.TotalMilliseconds);

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            m_graphicHandlerRef.beginDraw();

            // TODO: Add your drawing code here
            m_testingTexture.draw();

            base.Draw(gameTime);
            m_graphicHandlerRef.endDraw();
        }
    }
}
