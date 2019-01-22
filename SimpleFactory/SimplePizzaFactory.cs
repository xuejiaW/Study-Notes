﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleFactory
{
    public class SimplePizzaFactory
{
    public Pizza createPizza(string type)
    {
        Pizza pizza = null;
        if (type.Equals("cheese"))
            pizza = new CheesePizza();
        else if (type.Equals("sauce"))
            pizza = new SaucePizza();
        return pizza;
    }
}
}
