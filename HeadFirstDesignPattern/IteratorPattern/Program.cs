using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IteratorPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            DinerMenu dinerMenu = new DinerMenu();
            PancakeHouseMenu pancakeHouseMenu = new PancakeHouseMenu();

            PrintMenu(dinerMenu.createIterator());
            Console.WriteLine();
            PrintMenu(pancakeHouseMenu.createIterator());
        }

        private static void PrintMenu(Iterator iterator)
        {
            while (iterator.hasNext())
            {
                ((MenuItem)iterator.next()).Debug();
            }
        }
    }
}
