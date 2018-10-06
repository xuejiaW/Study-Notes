using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObserverPattern
{
    public class WeatherData : ISubject
    {
        private List<IObserver> observersList;

        public float Temperature { get; private set; }
        public float Humidity { get; private set; }
        public float Pressure { get; private set; }

        public WeatherData()
        {
            observersList = new List<IObserver>();
        }

        public void NotifyObservers()
        {
            observersList.ForEach(o => o.Update(this));
        }

        public void RegisterObserver(IObserver o)
        {
            observersList.Add(o);
        }

        public void UnregisterObserver(IObserver o)
        {
            observersList.Remove(o);
        }

        private void measurementsChanged()
        {
            NotifyObservers();
        }

        public void SetMeasurements(float temperature,float humidity,float pressure)
        {
            this.Temperature = temperature;
            this.Humidity = humidity;
            this.Pressure = pressure;
            measurementsChanged();
        }
    }
}
