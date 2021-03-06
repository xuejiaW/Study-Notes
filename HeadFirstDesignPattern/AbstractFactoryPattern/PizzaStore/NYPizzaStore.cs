﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public class NYPizzaStore : PizzaStore
    {
        protected override Pizza createPizza(string item)
        {
            Pizza pizza = null;
            PizzaIngredientFactory ingredientFactory = new NYPizzaIngredientFactory();
            if (item == "cheese")
                pizza = new CheesePizza(ingredientFactory);
            else if (item == "sauce")
                pizza = new SaucePizza(ingredientFactory);
            return pizza;
        }
    }
}
