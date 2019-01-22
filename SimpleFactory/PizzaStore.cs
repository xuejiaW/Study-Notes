using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleFactory
{
    public class PizzaStore
    {
        SimplePizzaFactory simpleFactory;
        public PizzaStore(SimplePizzaFactory factory)
        {
            this.simpleFactory = factory;
        }

        public Pizza orderPizza(string type)
        {
            Pizza pizza = simpleFactory.createPizza(type);
            pizza.prepare();
            pizza.bake();
            pizza.cut();
            pizza.box();
            return pizza;
        }
    }
}
