using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompositePattern
{
    public class Menu : MenuComponent
    {
        private List<MenuComponent> menuComponetsList = null;

        public Menu(string name, string description)
        {
            menuComponetsList = new List<MenuComponent>();
            Name = name;
            Description = description;
        }

        public override void Add(MenuComponent menuComponent)
        {
            menuComponetsList.Add(menuComponent);
        }

        public override void Remove(MenuComponent menuComponent)
        {
            menuComponent.Remove(menuComponent);
        }

        public override MenuComponent GetChild(int i)
        {
            return menuComponetsList[i];
        }

        public override void Debug()
        {
            Console.WriteLine(Name + " , " + Description);
            menuComponetsList.ForEach(menuComponent => menuComponent.Debug());
        }
    }
}
