using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public abstract class Pizza
    {
        protected Cheese cheese = null;
        protected Sauce sauce = null;
        protected Onion onion = null;

        public string name { get; set; }

        public abstract void prepare();

        public void bake()
        {
            Console.WriteLine("Bake for 25 minutes at 350");
        }

        public void cut()
        {
            Console.WriteLine("Cutting the pizza into diagonal slices");
        }

        public void box()
        {
            Console.WriteLine("Place pizza in official PizzaStore box");
        }

        public void Debug()
        {
            Console.WriteLine("--------------");
            Console.WriteLine(name);
            Console.WriteLine("Cheese is " + (cheese != null ? cheese.ToString() : "Null"));
            Console.WriteLine("Sauce is " + (sauce != null ? sauce.ToString() : "Null"));
            Console.WriteLine("Onion is " + (onion != null ? onion.ToString() : "Null"));
            Console.WriteLine("--------------");
        }
    }
}
