using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DecoratorPattern
{
    public class Espresso: Beverage
    {
        public Espresso()
        {
            description = "Espresson";
        }

        public override double Cost()
        {
            return 1.99;
        }
    }
}
