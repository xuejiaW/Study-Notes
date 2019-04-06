using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompositePattern
{
    public class MenuItem : MenuComponent
    {
        public MenuItem(string name, string description, bool vegetarian, float price)
        {
            Name = name;
            Description = description;
            Vegetarian = vegetarian;
            Price = price;
        }
    }
}
