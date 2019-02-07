using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompoundPattern
{
    public interface IVolumeModel
    {
        int Volume { get; set; }
        void RegisterObserver(IVolumeObserver observer);
        void UnRegisterObserver(IVolumeObserver observer);
    }
}
