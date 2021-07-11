using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Graph : MonoBehaviour
{
    public enum TransitionMode { Cycle, Random }

    [SerializeField]
    private TransitionMode transitionMode = default;

    [SerializeField]
    private Transform pointPrefab = null;

    [SerializeField, Range(10, 200)]
    private int resolution = 10;

    [SerializeField]
    private FunctionLibrary.FunctionName targetFunction = default;

    [SerializeField, Min(0f)]
    private float functionDuration = 1f, transitionDuration = 1f;

    private bool transitioning = false;
    private FunctionLibrary.FunctionName transitionFunction = default;
    private float duration = 0.0f;
    private Transform[] points = null;

    private void Awake()
    {
        Vector3 position = Vector3.zero;
        float step = 2.0f / resolution;
        float scale = step;

        points = new Transform[resolution * resolution];

        int index = 0;
        for (int x = 0; x != resolution; ++x)
        {
            for (int z = 0; z != resolution; ++z)
            {
                Transform point = points[index++] = Instantiate(pointPrefab);
                point.localScale = new Vector3(scale, scale, scale);
                point.SetParent(transform, false);
            }
        }
    }

    private void Update()
    {
        duration += Time.deltaTime;
       
        if (transitioning)
        {
            // Transition Time
            if (duration >= transitionDuration)
            {
                duration = 0.0f;
                transitioning = false;
            }
        }
        else if (duration >= functionDuration)
        {
            // Normal Time
            duration = 0.0f;

            transitioning = true;
            transitionFunction = targetFunction;
            targetFunction = PickNextFunction();
        }

        if (transitioning)
            UpdateFunctionTransition();
        else
            UpdateFunction();
    }

    private FunctionLibrary.FunctionName PickNextFunction()
    {
        return transitionMode == TransitionMode.Cycle
            ? FunctionLibrary.GetNextFunctionNames(targetFunction)
            : FunctionLibrary.GetRandomFunctionNameOtherThan(targetFunction);
    }

    private void UpdateFunction()
    {
        FunctionLibrary.Function function = FunctionLibrary.GetFunction(targetFunction);

        float time = Time.time;
        int index = 0;
        float step = 2.0f / resolution;

        for (int x = 0; x != resolution; ++x)
        {
            for (int z = 0; z != resolution; ++z)
            {
                float u = (x + 0.5f) * step - 1f;
                float v = (z + 0.5f) * step - 1f;
                points[index++].localPosition = function(u, v, time);
            }
        }
    }

    private void UpdateFunctionTransition()
    {
        FunctionLibrary.Function from = FunctionLibrary.GetFunction(transitionFunction);
        FunctionLibrary.Function to = FunctionLibrary.GetFunction(targetFunction);
        float progress = duration / transitionDuration;

        float time = Time.time;
        int index = 0;
        float step = 2.0f / resolution;

        for (int x = 0; x != resolution; ++x)
        {
            for (int z = 0; z != resolution; ++z)
            {
                float u = (x + 0.5f) * step - 1f;
                float v = (z + 0.5f) * step - 1f;
                points[index++].localPosition = FunctionLibrary.Morph(u, v, time, from, to, progress);
            }
        }
    }
}