using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FacadePattern
{
    class HomeTheaderFacade
    {
        private Amplifier amplifier = null;
        private Tuner tuner = null;
        private DvdPlayer dvdPlayer = null;
        private Projector projector = null;

        public HomeTheaderFacade(Amplifier amplifier, Tuner tuner, DvdPlayer dvdPlayer, Projector projector)
        {
            this.amplifier = amplifier;
            this.tuner = tuner;
            this.dvdPlayer = dvdPlayer;
            this.projector = projector;
        }

        public void WatchMovie()
        {
            amplifier.On();
            tuner.On();
            dvdPlayer.On();
            projector.On();
        }

        public void endMovie()
        {
            amplifier.Off();
            tuner.Off();
            dvdPlayer.Off();
            projector.Off();
        }
    }
}
