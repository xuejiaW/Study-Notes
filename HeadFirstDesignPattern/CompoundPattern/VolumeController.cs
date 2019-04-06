using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompoundPattern
{
    public class VolumeController : IViewController
    {
        private VolumeModel model = null;
        public VolumeController(VolumeModel model)
        {
            this.model = model;
        }

        public void SetVolume(int volume)
        {
            model.Volume = volume;
        }

        public void VolumeDown()
        {
            --model.Volume;
        }

        public void VolumeUp()
        {
            ++model.Volume;
        }
    }
}
