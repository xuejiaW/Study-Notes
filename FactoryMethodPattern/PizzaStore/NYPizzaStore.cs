using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryMethodPattern
{
    public class NYPizzaStore : PizzaStore
    {
        protected override Pizza createPizza(string type)
        {
            Pizza pizza = null;
            if (type.Equals("cheese"))
                pizza = new NYStyleCheesePizza();
            else if (type.Equals("sauce"))
                pizza = new NYStyleSausePizza();
            return pizza;
        }
    }
}
