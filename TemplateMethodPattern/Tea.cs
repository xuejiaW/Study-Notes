using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethodPattern
{
    class Tea : CaffeineBeverage
    {
        protected override void addCondiments()
        {
            Console.WriteLine("Adding lemon");
        }

        protected override void brew()
        {
            Console.WriteLine("Steeping the tea");
        }
    }
}
