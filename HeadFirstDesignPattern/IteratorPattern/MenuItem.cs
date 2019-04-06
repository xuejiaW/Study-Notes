using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IteratorPattern
{
    public class MenuItem
    {
        public string Name { get; private set; }
        public string Description { get; private set; }
        public bool Vegetarian { get; private set; }
        public float Price { get; private set; }

        public MenuItem(string name, string description, bool vegetarian, float price)
        {
            Name = name;
            Description = description;
            Vegetarian = vegetarian;
            Price = price;
        }

        public void Debug()
        {
            Console.WriteLine(Name + " , " + Description + " , " + Vegetarian + " , " + Price);
        }
    }
}
