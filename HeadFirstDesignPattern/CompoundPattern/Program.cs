using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompoundPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            VolumeModel model = new VolumeModel();
            VolumeView view = new VolumeView(new VolumeController(model), model);
            view.OnVolumeUpButtonClick();
            view.OnVolumeUpButtonClick();
            view.OnVolumeDownButtonClick();
        }
    }
}
