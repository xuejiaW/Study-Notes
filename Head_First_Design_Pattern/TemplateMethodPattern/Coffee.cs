using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethodPattern
{
    public class Coffee : CaffeineBeverage
    {
        protected override void addCondiments()
        {
            Console.WriteLine("Add sugar and Milk");
        }

        protected override void brew()
        {
            Console.WriteLine("Dripping coffee through filter");
        }

        public override bool NeedCondiments()
        {
            return false;
        }
    }
}
