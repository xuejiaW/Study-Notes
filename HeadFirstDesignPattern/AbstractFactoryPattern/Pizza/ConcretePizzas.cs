using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public class CheesePizza : Pizza
    {
        private PizzaIngredientFactory ingredientFactory = null;

        public CheesePizza(PizzaIngredientFactory ingredientFactory)
        {
            this.ingredientFactory = ingredientFactory;
        }

        public override void prepare()
        {
            cheese = ingredientFactory.createCheese();
            onion = ingredientFactory.createOnion();
        }
    }

    public class SaucePizza : Pizza
    {
        private PizzaIngredientFactory ingredientFactory = null;

        public SaucePizza(PizzaIngredientFactory ingredientFactory)
        {
            this.ingredientFactory = ingredientFactory;
        }

        public override void prepare()
        {
            sauce = ingredientFactory.createSauce();
            onion = ingredientFactory.createOnion();
        }
    }
}
