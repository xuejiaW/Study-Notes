using System;
using System.Collections.Generic;
using System.Threading;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProxyPattern
{
    public class ImageIcon : Icon
    {
        private int width, height;
        public ImageIcon()
        {
            Thread.Sleep(5000);//Pretend there is some hard work to load the image
            width = 800;
            height = 1000;
        }
        public void PrintIconWidthAndHeight()
        {
            Console.WriteLine(DateTime.Now.ToLongTimeString() + ": Width is " + width + ",height is " + height);
        }
    }
}
