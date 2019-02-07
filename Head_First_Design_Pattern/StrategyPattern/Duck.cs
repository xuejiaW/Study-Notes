using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrategyPattern
{
    public abstract class Duck
    {
        private IFlyBehavior flyBehavior;

        public Duck() { }

        public abstract void disPlay();

        public void PerformFly()
        {
            flyBehavior.Fly();
        }

        public void setFlyBehavior(IFlyBehavior fb)
        {
            flyBehavior = fb;
        }
    }
}

