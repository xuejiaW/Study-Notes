using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrategyPattern
{
    public class RubberDuck : Duck
    {
        public RubberDuck() : base()
        {
            setFlyBehavior(new FlyNoWay());
        }

        public override void disPlay()
        {
            Console.WriteLine("I am a rubber duck");
        }
    }
}
