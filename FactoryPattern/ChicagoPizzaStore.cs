using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryPattern
{
    public class ChicagoPizzaStore : PizzaStore
    {
        protected override Pizza createPizza(string item)
        {
            Pizza pizza = null;
            PizzaIngredientFactory ingredientFactory = new ChicagoPizzaIngredientFactory();
            if (item == "cheese")
            {
                pizza = new CheesePizza(ingredientFactory);
                pizza.name = "Chicago Style Cheese Pizza";
            }
            else if (item == "sauce")
            {
                pizza = new SaucePizza(ingredientFactory);
                pizza.name = "Chicago Sttle Sauce Pizza";
            }
            return pizza;
        }
    }
}
