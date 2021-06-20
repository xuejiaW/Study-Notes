using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Clock : MonoBehaviour
{
    [SerializeField]
    private Transform hoursPivot = null, minutesPivot = null, secondsPivot = null;

    private const float hoursToDegrees = -30.0f, minutesToDegrees = -6.0f, secondsToDegrees = -6.0f;

    private void Update()
    {
        TimeSpan totalTime = DateTime.Now.TimeOfDay;
        Debug.Log("DateTime TimeOfDay is " + totalTime.ToString());
        hoursPivot.localRotation = Quaternion.Euler(0f, 0f, hoursToDegrees * (float)totalTime.TotalHours);
        minutesPivot.localRotation = Quaternion.Euler(0f, 0f, minutesToDegrees * (float)totalTime.TotalMinutes);
        secondsPivot.localRotation = Quaternion.Euler(0f, 0f, secondsToDegrees * (float)totalTime.TotalSeconds);
    }
}