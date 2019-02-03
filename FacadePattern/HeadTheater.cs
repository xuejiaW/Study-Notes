using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FacadePattern
{
    public class Amplifier
    {
        public void On()
        {
            Console.WriteLine(this.GetType().ToString() + " On");
        }

        public void Off()
        {
            Console.WriteLine(this.GetType().ToString() + " Off");
        }
    }

    public class Tuner
    {
        public void On()
        {
            Console.WriteLine(this.GetType().ToString() + " On");
        }

        public void Off()
        {
            Console.WriteLine(this.GetType().ToString() + " Off");
        }
    }

    public class DvdPlayer
    {
        public void On()
        {
            Console.WriteLine(this.GetType().ToString() + " On");
        }

        public void Off()
        {
            Console.WriteLine(this.GetType().ToString() + " Off");
        }
    }

    public class Projector
    {
        public void On()
        {
            Console.WriteLine(this.GetType().ToString() + " On");
        }

        public void Off()
        {
            Console.WriteLine(this.GetType().ToString() + " Off");
        }
    }
}
