using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FacadePattern
{
    class Program
    {
        static void Main(string[] args)
        {
            HomeTheaderFacade facade = new HomeTheaderFacade(new Amplifier(), new Tuner(), new DvdPlayer(), new Projector());
            facade.WatchMovie();
            Console.WriteLine();
            facade.endMovie();
        }
    }
}
