using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompoundPattern
{
    public interface IViewController
    {
        void VolumeUp();
        void VolumeDown();
        void SetVolume(int volume);
    }
}
