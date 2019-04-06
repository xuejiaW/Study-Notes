using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrategyPattern
{
    public class BlackDuck:Duck
    {
        public BlackDuck():base()
        {
            setFlyBehavior(new FlyWithWings());
        }

        public override void disPlay()
        {
            Console.WriteLine("I am a black duck");
        }
    }
}
