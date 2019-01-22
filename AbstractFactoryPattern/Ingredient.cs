using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactoryMethod
{
    public class Cheese { }
    public class Sauce { }
    public class Onion { }

    public class NYOnion:Onion { }
    public class NYSauce : Sauce { }
    public class NYCheese : Cheese { }

    public class ChicagoOnion : Onion { }
    public class ChicagoSauce : Sauce { }
    public class ChicagoCheese : Cheese { }
}
