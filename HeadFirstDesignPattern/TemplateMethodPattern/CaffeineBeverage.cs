using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethodPattern
{
    public abstract class CaffeineBeverage
    {
        public void PrepareRecipe()
        {
            boilWater();
            brew();
            pourInCup();
            if (NeedCondiments())
                addCondiments();
        }

        protected abstract void brew();

        protected abstract void addCondiments();

        private void boilWater()
        {
            Console.WriteLine("Boiling Water");
        }

        private void pourInCup()
        {
            Console.WriteLine("Pouring Water");
        }

        public virtual bool NeedCondiments()
        {
            return true;
        }
    }
}
