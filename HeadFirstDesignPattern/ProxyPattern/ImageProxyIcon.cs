using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ProxyPattern
{
    public class ImageProxyIcon : Icon
    {
        private ImageIcon icon = null;
        private bool isLoading = false;

        public ImageProxyIcon() { }

        public void PrintIconWidthAndHeight()
        {
            if (icon != null)
                icon.PrintIconWidthAndHeight();
            else if (!isLoading)
            {
                Console.WriteLine(DateTime.Now.ToLongTimeString()+": Is Loading Image...");
                isLoading = true;
                new Thread(() =>
                {
                    icon = new ImageIcon();
                    icon.PrintIconWidthAndHeight();
                }).Start();
            }
        }
    }
}
