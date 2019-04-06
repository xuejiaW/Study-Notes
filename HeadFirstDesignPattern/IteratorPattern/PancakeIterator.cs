using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IteratorPattern
{
    public class PancakeIterator : Iterator
    {
        private List<MenuItem> itemsList = null;
        private int currentPosition = 0;

        public PancakeIterator(List<MenuItem> itemsList)
        {
            this.itemsList = itemsList;
        }
        public bool hasNext()
        {
            return currentPosition < itemsList.Count && itemsList[currentPosition] != null;
        }

        public object next()
        {
            return itemsList[currentPosition++];
        }
    }
}
