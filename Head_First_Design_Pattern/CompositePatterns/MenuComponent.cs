using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompositePattern
{
    public abstract class MenuComponent
    {
        public virtual void Add(MenuComponent menuComponent) { throw new NotImplementedException(); }
        public virtual void Remove(MenuComponent menuComponent) { throw new NotImplementedException(); }
        public virtual MenuComponent GetChild(int i) { throw new NotImplementedException(); }
        public virtual string Name { get; protected set; }
        public virtual string Description { get; protected set; }
        public virtual float Price { get; protected set; }
        public virtual bool Vegetarian { get; protected set; }
        public virtual void Debug()
        {
            Console.WriteLine(Name + " , " + Description + " , " + Vegetarian + " , " + Price);
        }
    }
}
