using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CommandPattern
{
    public class LightOffCommand : Command
    {
        private Light light;
        public LightOffCommand(Light light)
        {
            this.light = light;
        }
        public void Execute()
        {
            light.Off();
        }

        public void Undo()
        {
            light.On();
        }
    }

    public class LightOnCommand : Command
    {
        private Light light;
        public LightOnCommand(Light light)
        {
            this.light = light;
        }
        public void Execute()
        {
            light.On();
        }

        public void Undo()
        {
            light.Off();
        }
    }

    public class NoCommand : Command
    {
        public void Execute()
        {
            Console.WriteLine("No command execute");
        }

        public void Undo()
        {
            Console.WriteLine("No command undo");
        }
    }
}
