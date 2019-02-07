using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompoundPattern
{
    public class VolumeView : IVolumeObserver
    {
        private IViewController controller = null;
        private IVolumeModel model = null;

        public VolumeView(IViewController controller, IVolumeModel model)
        {
            this.controller = controller;
            this.model = model;
            this.model.RegisterObserver(this);
            Console.WriteLine("View: volume init is " + model.Volume);
        }

        public void OnVolumeUpButtonClick()
        {
            controller.VolumeUp();
        }

        public void OnVolumeDownButtonClick()
        {
            controller.VolumeDown();
        }

        public void VolumeUpdated()
        {
            Console.WriteLine("View: volume updated " + model.Volume);
        }

        ~VolumeView()
        {
            model.UnRegisterObserver(this);
        }
    }
}
