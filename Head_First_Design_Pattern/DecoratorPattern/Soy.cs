using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DecoratorPattern
{
    public class Soy : CondimentDecorator
    {
        public Soy(Beverage beverage) : base(beverage) { }

        public override string getDescription()
        {
            return beverage.getDescription() + ", Soy";
        }

        public override double Cost()
        {
            return 0.30 + beverage.Cost();
        }
    }
}
