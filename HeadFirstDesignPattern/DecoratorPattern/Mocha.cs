using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DecoratorPattern
{
    public class Mocha : CondimentDecorator
    {
        public Mocha(Beverage beverage):base(beverage){}

        public override string getDescription()
        {
            return beverage.getDescription()+", Mocha";
        }

        public override double Cost()
        {
            return 0.20 + beverage.Cost();
        }
    }
}
