using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public interface PizzaIngredientFactory
    {
        Onion createOnion();
        Sauce createSauce();
        Cheese createCheese();
    }
}
