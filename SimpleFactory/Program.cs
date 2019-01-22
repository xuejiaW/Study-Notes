using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleFactory
{
    class Program
    {
        static void Main(string[] args)
        {
            PizzaStore store = new PizzaStore(new SimplePizzaFactory());
            Pizza pizza = store.orderPizza("cheese");
            pizza.Debug();

        }
    }
}
