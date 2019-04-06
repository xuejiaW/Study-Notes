using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DecoratorPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            Espresso espresso = new Espresso();
            Console.WriteLine(espresso.getDescription() + " Cost: " + espresso.Cost());

            Beverage doubleMochaWhipEspresso = new Mocha(new Mocha(new Whip(espresso)));
            Console.WriteLine(doubleMochaWhipEspresso.getDescription() + " Cost: " + doubleMochaWhipEspresso.Cost());

        }
    }
}

