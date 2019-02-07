using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdapterPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            MallardDuck duck = new MallardDuck();
            WildTurkey turkey = new WildTurkey();
            TestDuck(duck);
            TestDuck(new TurkeyAdapter(turkey));
        }

        static void TestDuck(Duck duck)
        {
            duck.Fly();
            duck.Quack();
        }
    }
}
