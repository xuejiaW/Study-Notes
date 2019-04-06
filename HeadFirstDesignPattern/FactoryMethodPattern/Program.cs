using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryMethodPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            PizzaStore store = new ChicagoPizzaStore();
            Pizza pizza = store.orderPizza("cheese");
            pizza.Debug();

            store = new NYPizzaStore();
            pizza = store.orderPizza("cheese");
            pizza.Debug();
        }
    }
}
