using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public class NYPizzaIngredientFactory : PizzaIngredientFactory
    {
        public Cheese createCheese()
        {
            return new NYCheese();
        }

        public Onion createOnion()
        {
            return new NYOnion();
        }

        public Sauce createSauce()
        {
            return new NYSauce();
        }
    }
}
