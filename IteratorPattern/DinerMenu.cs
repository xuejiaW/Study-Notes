using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IteratorPattern
{
    public class DinerMenu
    {
        private readonly int MaxItemsCount = 6;
        private MenuItem[] menuItemsArray = null;
        private int numberOfItems = 0;

        public DinerMenu()
        {
            menuItemsArray = new MenuItem[MaxItemsCount];
            addItem("Vegetarian BLT", "Fakin Bacon with tomato",true,2.99f);
            addItem("BLT", "Bacon with tomato", true, 3.99f);
            addItem("Soup of the day", "Soup of the day and salad", false, 3.29f);
        }

        public void addItem(string name, string description, bool vegetarian, float price)
        {
            if (numberOfItems >= MaxItemsCount)
                return;
            MenuItem menuItem = new MenuItem(name, description, vegetarian, price);
            menuItemsArray[numberOfItems++] = menuItem;
        }

        public Iterator createIterator()
        {
            return new DinerMenuIterator(menuItemsArray);
        }
    }
}
