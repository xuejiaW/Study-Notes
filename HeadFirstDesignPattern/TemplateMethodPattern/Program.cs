using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethodPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            Coffee coffee = new Coffee();
            Tea tea = new Tea();
            coffee.PrepareRecipe();
            Console.WriteLine();
            tea.PrepareRecipe();
        }
    }
}