using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryMethodPattern
{
    public class ChicagoPizzaStore : PizzaStore
    {
        protected override Pizza createPizza(string type)
        {
            Pizza pizza = null;
            if (type.Equals("cheese"))
                pizza = new ChicagoStyleCheesePizza();
            else if (type.Equals("sauce"))
                pizza = new ChicagoStyleSaucePizza();
            return pizza;
        }
    }
}
