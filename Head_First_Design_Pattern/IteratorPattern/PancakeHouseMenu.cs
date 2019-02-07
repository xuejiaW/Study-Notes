using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IteratorPattern
{
    public class PancakeHouseMenu
    {
        private List<MenuItem> menuItemsList = null;

        public PancakeHouseMenu()
        {
            menuItemsList = new List<MenuItem>();
            addItem("K&B's Pancake Breakfast", "Pancake with eggs and toast", true, 2.99f);
            addItem("Regular's Pancake Breakfast", "Pancake with eggs and sausags", true, 2.99f);
            addItem("Blueberry's Pancake Breakfast", "Pancake with eggs and fresh blueberries", true, 2.99f);
        }

        public Iterator createIterator()
        {
            return new PancakeIterator(menuItemsList);
        }

        public void addItem(string name, string description, bool vegetarian, float price)
        {
            MenuItem menuItem = new MenuItem(name, description, vegetarian, price);
            menuItemsList.Add(menuItem);
        }
    }
}
