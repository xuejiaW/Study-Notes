using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatePattern
{
    public class GumballMachine
    {
        public State SoldOutState { get; private set; }
        public State NoQuarterState { get; private set; }
        public State HasQuarterState { get; private set; }
        public State SoldState { get; private set; }
        public int remainGumballsNum { get; private set; }

        private State currentState = null;

        public GumballMachine(int gumballsNum)
        {
            remainGumballsNum = gumballsNum;
            SoldOutState = new SoldOutState(this);
            NoQuarterState = new NoQuarterState(this);
            HasQuarterState = new HasQuarterState(this);
            SoldState = new SoldState(this);
            currentState = remainGumballsNum > 0 ? NoQuarterState : SoldOutState;
        }

        public void InsertQuarter()
        {
            currentState.InsertQuarter();
        }

        public void EjectQuarter()
        {
            currentState.EjectQuarter();
        }

        public void TurnCrank()
        {
            currentState.TurnCrank();
            currentState.Dispense();
        }

        public void ReleaseBall()
        {
            Console.WriteLine("A gumball comes rolling out the slot");
            remainGumballsNum = remainGumballsNum != 0 ? --remainGumballsNum : remainGumballsNum;
        }

        public void SetState(State state)
        {
            currentState = state;
        }
    }
}
