using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SingletonPattern
{
    public class Singleton
    {
        private static object lockObj = new object();
        private static Singleton instance = null;

        public static Singleton Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (lockObj)
                        if (instance == null)
                            instance = new Singleton();
                }
                return instance;
            }
        }

        private Singleton()
        {
            Console.WriteLine("Constructor the Singleton");
        }
    }
}
