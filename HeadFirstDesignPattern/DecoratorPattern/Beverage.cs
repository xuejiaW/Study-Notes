using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DecoratorPattern
{
    public abstract class Beverage
    {
        protected string description = "UnKnown Beverage";

        public virtual string getDescription()
        {
            return description;
        }

        public abstract double Cost();
    }
}
