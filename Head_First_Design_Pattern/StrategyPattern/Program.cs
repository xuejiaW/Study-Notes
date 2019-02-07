using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrategyPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            RubberDuck rubberDuck = new RubberDuck();
            rubberDuck.disPlay();
            rubberDuck.PerformFly();

            BlackDuck blackDuck = new BlackDuck();
            blackDuck.disPlay();
            blackDuck.PerformFly();
            blackDuck.setFlyBehavior(new FlyWithRocket());
            blackDuck.PerformFly();
        }
    }
}


