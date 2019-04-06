using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public class ChicagoPizzaIngredientFactory : PizzaIngredientFactory
    {
        public Cheese createCheese()
        {
            return new ChicagoCheese();
        }

        public Onion createOnion()
        {
            return new ChicagoOnion();
        }

        public Sauce createSauce()
        {
            return new ChicagoSauce();
        }
    }
}
