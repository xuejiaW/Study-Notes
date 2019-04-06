using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdapterPattern
{
    public interface Duck
    {
        void Quack();
        void Fly();
    }

    public class MallardDuck : Duck
    {
        public void Fly()
        {
            Console.WriteLine("MallardDuck Fly");
        }

        public void Quack()
        {
            Console.WriteLine("MallardDuck Quack");
        }
    }
}
