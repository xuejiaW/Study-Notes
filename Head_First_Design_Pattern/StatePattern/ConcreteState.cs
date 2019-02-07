using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatePattern
{
    public class NoQuarterState : State
    {
        private GumballMachine gumballMachine = null;

        public NoQuarterState(GumballMachine gumballMachine)
        {
            this.gumballMachine = gumballMachine;
        }

        public void Dispense() { Console.WriteLine("You need to pay first"); }

        public void EjectQuarter() { Console.WriteLine("You haven't inserted a quarter"); }

        public void InsertQuarter()
        {
            gumballMachine.SetState(gumballMachine.HasQuarterState);
            Console.WriteLine("You inserted a quarter");
        }

        public void TurnCrank() { Console.WriteLine("You turned,but there's no quarter"); }
    }

    public class HasQuarterState : State
    {
        private GumballMachine gumballMachine = null;

        public HasQuarterState(GumballMachine gumballMachine)
        {
            this.gumballMachine = gumballMachine;
        }
        public void Dispense()
        {
            Console.WriteLine("No gumball dispensed");
        }

        public void EjectQuarter()
        {
            Console.WriteLine("Quarter returned");
            gumballMachine.SetState(gumballMachine.NoQuarterState);
        }

        public void InsertQuarter()
        {
            Console.WriteLine("You can't insert another quater");
        }

        public void TurnCrank()
        {
            Console.WriteLine("You turned");
            gumballMachine.SetState(gumballMachine.SoldState);
        }
    }

    public class SoldState : State
    {
        private GumballMachine gumballMachine = null;

        public SoldState(GumballMachine gumballMachine)
        {
            this.gumballMachine = gumballMachine;
        }

        public void Dispense()
        {
            gumballMachine.ReleaseBall();
            if (gumballMachine.remainGumballsNum > 0)
                gumballMachine.SetState(gumballMachine.NoQuarterState);
            else
            {
                Console.WriteLine("Opps,out of gumballs");
                gumballMachine.SetState(gumballMachine.SoldOutState);
            }
        }

        public void EjectQuarter()
        {
            Console.WriteLine("Sorry,you already turned the crank");
        }

        public void InsertQuarter()
        {
            Console.WriteLine("Please wait,we are already giving you a gumball");
        }

        public void TurnCrank()
        {
            Console.WriteLine("Turning twice dones't get you another gumball");
        }
    }

    public class SoldOutState : State
    {
        private GumballMachine gumballMachine = null;
        public SoldOutState(GumballMachine gumballMachine)
        {
            this.gumballMachine = gumballMachine;
        }
        public void Dispense()
        {
            Console.WriteLine("No gumball dispensed");
        }

        public void EjectQuarter()
        {
            Console.WriteLine("You can't eject,you haven't inserted a quarter yet");
        }

        public void InsertQuarter()
        {
            Console.WriteLine("You can't insert a quarter,the machine is sold out");
        }

        public void TurnCrank()
        {
            Console.WriteLine("You turned,but there are no gumballs");
        }
    }
}
