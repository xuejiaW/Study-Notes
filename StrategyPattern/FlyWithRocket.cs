using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrategyPattern
{
    public class FlyWithRocket : IFlyBehavior
    {
        public void Fly()
        {
            Console.WriteLine("Fly with rocket");
        }
    }
}

