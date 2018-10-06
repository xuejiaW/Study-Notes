using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObserverPattern
{
    public class PressureObserver : IObserver
    {
        private ISubject subject;
        public PressureObserver(ISubject subject)
        {
            this.subject = subject;
            this.subject.RegisterObserver(this);
        }

        public void Update(ISubject subject)
        {
            WeatherData weatherData = subject as WeatherData;
            if (weatherData != null)
                Console.WriteLine("Pressure is " + weatherData.Pressure);
        }
    }
}
