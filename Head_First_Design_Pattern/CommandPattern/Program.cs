using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CommandPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            Light light = new Light();
            RemoteControl remoteControl = new RemoteControl();
            remoteControl.SetCommand(0, new LightOnCommand(light));
            remoteControl.SetCommand(1, new LightOffCommand(light));
            remoteControl.OnButtonClick(0);
            remoteControl.OnButtonClick(1);
            remoteControl.OnClickUndo();
        }
    }
}
