using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Graph : MonoBehaviour
{
    [SerializeField]
    private Transform pointPrefab = null;

    [SerializeField, Range(10, 100)]
    private int resolution = 10;

    private Transform[] points = null;

    private void Awake()
    {
        Vector3 position = Vector3.zero;
        float step = 2.0f / resolution;
        float scale = step;

        points = new Transform[resolution];

        for (int i = 0; i < points.Length; ++i)
        {
            Transform point = points[i] = Instantiate(pointPrefab);
            position.x = (i + 0.5f) * scale - 1.0f;
            position.y = position.x * position.x * position.x;
            point.localPosition = position;
            point.localScale = new Vector3(scale, scale, scale);
            point.SetParent(transform, false);
        }
    }

    private void Update()
    {
        float time = Time.time;
        for (int i = 0; i < points.Length; i++)
        {
            Transform point = points[i];
            Vector3 position = point.localPosition;
            position.y = Mathf.Sin(Mathf.PI * (position.x + time));
            point.localPosition = position;
        }
    }
}