using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryPattern
{
    public abstract class PizzaStore
    {
        protected abstract Pizza createPizza(string item);

        public Pizza OrderPizza(string type)
        {
            Pizza pizza = createPizza(type);
            Console.WriteLine("----Making a " + pizza.name + " ----");
            pizza.prepare();
            pizza.bake();
            pizza.cut();
            pizza.box();
            return pizza;
        }
    }
}
