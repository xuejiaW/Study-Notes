using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DecoratorPattern
{
    public class Whip : CondimentDecorator
    {
        public Whip(Beverage beverage) : base(beverage) { }

        public override string getDescription()
        {
            return beverage.getDescription() + ", Whip";
        }

        public override double Cost()
        {
            return 0.30 + beverage.Cost();
        }
    }
}
