using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleFactory
{
    public class CheesePizza : Pizza
    {
        public override void prepare()
        {
            cheese = new Cheese();
        }
    }

    public class SaucePizza : Pizza
    {
        public override void prepare()
        {
            sauce = new Sauce();
        }
    }
}
