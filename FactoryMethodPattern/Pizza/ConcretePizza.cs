using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryMethodPattern
{
    public class CheesePizza : Pizza
    {
        public override void prepare()
        {
            cheese = new Cheese();
        }
    }

    public class SaucePizza : Pizza
    {
        public override void prepare()
        {
            sauce = new Sauce();
        }
    }

    public class NYStyleCheesePizza : Pizza
    {
        public override void prepare()
        {
            cheese = new NYCheese();
        }
    }

    public class NYStyleSausePizza : Pizza
    {
        public override void prepare()
        {
            sauce = new NYSauce();
        }
    }

    public class ChicagoStyleCheesePizza : Pizza
    {
        public override void prepare()
        {
            cheese = new ChicagoCheese();
        }
    }

    public class ChicagoStyleSaucePizza : Pizza
    {
        public override void prepare()
        {
            sauce = new ChicagoSauce();
        }
    }
}
