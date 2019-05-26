using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Delegate
{
    using System.Collections.Specialized;
    class Program
    {
        private delegate void StringProcessor(string input);
        static void Main(string[] args)
        {
            StringProcessor stringProcessor = null;
            stringProcessor += PrintString;
            stringProcessor += PrintObject;
            stringProcessor("Test");

        }

        private static void PrintObject(object x)
        {
            //In C# 1,delegate must have exactly the same parameter
            //So this function would cause compile error in c# 1,but it works on C# 2 and above

            Console.WriteLine("Print Object: " + x);
        }
        private static void PrintString(string x)
        {
            Console.WriteLine("Print String: " + x);
        }
    }
}
