using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IteratorPattern
{
    public class DinerMenuIterator : Iterator
    {
        private MenuItem[] itemsArray = null;
        private int currentPosition = 0;

        public DinerMenuIterator(MenuItem[] items)
        {
            this.itemsArray = items;
        }
        public bool hasNext()
        {
            return currentPosition < itemsArray.Length && itemsArray[currentPosition] != null;
        }

        public object next()
        {
            return itemsArray[currentPosition++];
        }
    }
}
