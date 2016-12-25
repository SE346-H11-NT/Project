using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WindowsFramework.Manager;
using Microsoft.Xna.Framework.Audio;

namespace WindowsFramework.Media
{
    public class MSound
    {
        private static GraphicHandler m_deviceHandlerRef;
        private static Dictionary<int, SoundEffect> m_storage = new Dictionary<int, SoundEffect>();
        private static Dictionary<int, List<SoundEffectInstance>> m_instanceStorage = new Dictionary<int, List<SoundEffectInstance>>();
        private static int m_IDCounter = -1;

        static public void setDeviceHandler(ref GraphicHandler handler)
        {
            m_deviceHandlerRef = handler;
        }

        public static int loadSound(String path)
        {
            m_IDCounter += 1;
            SoundEffect newSound = m_deviceHandlerRef.loadContent<SoundEffect>(path);
            m_storage.Add(m_IDCounter, newSound);
            m_instanceStorage.Add(m_IDCounter, new List<SoundEffectInstance>());

            return m_IDCounter;
        }

        public static void playSound(int id, bool isLoop)
        {
            SoundEffectInstance soundInstance = m_storage[id].CreateInstance();
            soundInstance.IsLooped = isLoop;
            soundInstance.Play();
            if (isLoop)
            {
                m_instanceStorage[id].Add(soundInstance);
            }
        }

        public static void stopSound(int id)
        {
            foreach (SoundEffectInstance si in m_instanceStorage[id])
            {
                si.Stop();
            }
            m_instanceStorage[id].Clear();
        }
    }
}
