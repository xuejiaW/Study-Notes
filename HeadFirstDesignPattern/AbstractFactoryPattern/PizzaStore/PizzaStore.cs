using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public abstract class PizzaStore
    {
        protected abstract Pizza createPizza(string item);

        public Pizza OrderPizza(string type)
        {
            Pizza pizza = createPizza(type);
            pizza.prepare();
            pizza.bake();
            pizza.cut();
            pizza.box();
            return pizza;
        }
    }
}
