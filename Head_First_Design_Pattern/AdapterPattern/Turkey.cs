using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdapterPattern
{
    public interface Turkey
    {
        void Gobble();
        void Fly();
    }

    public class WildTurkey : Turkey
    {
        public void Fly()
        {
            Console.WriteLine("WildTurkey Fly");
        }

        public void Gobble()
        {
            Console.WriteLine("WildTurkey Gobble");
        }
    }
}
