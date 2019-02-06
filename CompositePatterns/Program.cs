using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompositePattern
{
    class Program
    {
        static void Main(string[] args)
        {
            Menu menu = new Menu("General Menu", "Holds all menus and menu items");
            Menu dinnerMenu = new Menu("Dinner Menu", "Holds dinner menu items");
            Menu breakfastMenu = new Menu("Breakfast Menu", "Holds Breakfast menu items");
            menu.Add(dinnerMenu);
            menu.Add(breakfastMenu);


            breakfastMenu.Add(new MenuItem("K&B's Pancake Breakfast", "Pancake with eggs and toast", true, 2.99f));
            breakfastMenu.Add(new MenuItem("Regular's Pancake Breakfast", "Pancake with eggs and sausags", true, 2.99f));
            breakfastMenu.Add(new MenuItem("Blueberry's Pancake Breakfast", "Pancake with eggs and fresh blueberries", true, 2.99f));

            dinnerMenu.Add(new MenuItem("Vegetarian BLT", "Fakin Bacon with tomato", true, 2.99f));
            dinnerMenu.Add(new MenuItem("BLT", "Bacon with tomato", true, 3.99f));
            dinnerMenu.Add(new MenuItem("Soup of the day", "Soup of the day and salad", false, 3.29f));

            menu.Debug();
        }
    }
}


