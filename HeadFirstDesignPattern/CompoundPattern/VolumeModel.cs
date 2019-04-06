using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompoundPattern
{
    public class VolumeModel : IVolumeModel
    {
        private int volume = 0;
        public int Volume
        {
            get { return volume; }
            set
            {
                volume = value;
                observersList.ForEach(observer => observer.VolumeUpdated());
            }
        }
        private List<IVolumeObserver> observersList = null;

        public VolumeModel()
        {
            observersList = new List<IVolumeObserver>();
        }

        public void RegisterObserver(IVolumeObserver observer)
        {
            observersList.Add(observer);
        }

        public void UnRegisterObserver(IVolumeObserver observer)
        {
            observersList.Remove(observer);
        }
    }
}
