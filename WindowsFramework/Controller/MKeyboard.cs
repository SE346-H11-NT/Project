using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework.Input;

namespace WindowsFramework.Controller
{
    public class MKeyboard
    {
        private static KeyboardState m_currentState;
        private static KeyboardState m_previousState;

        private static Dictionary<int, Keys> m_keyMap = new Dictionary<int,Keys>();

        public static void update()
        {
            m_previousState = m_currentState;
            m_currentState = Keyboard.GetState();
        }

        public static bool isKeyDown(int keyCode)
        {
            return m_currentState.IsKeyDown(m_keyMap[keyCode]);
        }

        public static bool isKeyPreviouslyDown(int keyCode)
        {
            return m_previousState.IsKeyDown(m_keyMap[keyCode]);
        }
        
        public static void initialize()
        {
            m_keyMap.Add(0X1E, Keys.A);
            m_keyMap.Add(0X20, Keys.D);
            m_keyMap.Add(0x11, Keys.W);
            m_keyMap.Add(0x1F, Keys.S);
            m_keyMap.Add(0X24, Keys.J);
            m_keyMap.Add(0X25, Keys.K);
            m_keyMap.Add(0x1C, Keys.Enter);
            m_keyMap.Add(0x36, Keys.RightShift);

            // Cheat keys
            m_keyMap.Add(0X16, Keys.U);
            m_keyMap.Add(0x02, Keys.NumPad1);
            m_keyMap.Add(0x03, Keys.NumPad2);
            m_keyMap.Add(0x04, Keys.NumPad3);
            m_keyMap.Add(0x05, Keys.NumPad4);
            m_keyMap.Add(0x06, Keys.NumPad5);
            m_keyMap.Add(0x07, Keys.NumPad6);
        }
    }
}
