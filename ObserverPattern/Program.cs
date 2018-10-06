using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObserverPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            WeatherData weatherData = new WeatherData();
            TemperatureObserver temperatureObserver = new TemperatureObserver(weatherData);
            PressureObserver pressureObserver = new PressureObserver(weatherData);

            weatherData.SetMeasurements(30, 20, 10);
            weatherData.SetMeasurements(20, 40, 5);
            weatherData.UnregisterObserver(temperatureObserver);
            weatherData.SetMeasurements(10, 50, 15);
        }
    }
}
