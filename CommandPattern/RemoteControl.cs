using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CommandPattern
{
    class RemoteControl
    {
        Command[] commands;
        Command lastCommond;

        public RemoteControl()
        {
            commands = new Command[2] { new NoCommand(), new NoCommand() };
            lastCommond = new NoCommand();
        }

        public void SetCommand(int index, Command command)
        {
            commands[index] = command;
        }

        public void OnButtonClick(int index)
        {
            commands[index].Execute();
            lastCommond = commands[index];
        }

        public void OnClickUndo()
        {
            lastCommond.Undo();
            lastCommond = new NoCommand();
        }
    }
}
