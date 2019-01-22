using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    class Program
    {
        static void Main(string[] args)
        {
            PizzaStore pizzaStore = new NYPizzaStore();
            Pizza pizza= pizzaStore.OrderPizza("cheese");
            pizza.Debug();
            Console.WriteLine("--------");
            pizzaStore = new ChicagoPizzaStore();
            pizza = pizzaStore.OrderPizza("cheese");
            pizza.Debug();
        }
    }
}
