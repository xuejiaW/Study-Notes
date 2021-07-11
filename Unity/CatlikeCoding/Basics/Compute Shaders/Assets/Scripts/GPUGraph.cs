using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GPUGraph : MonoBehaviour
{
    public enum TransitionMode { Cycle, Random }

    [SerializeField]
    private TransitionMode transitionMode = default;

    private const int maxResolution = 1000;

    [SerializeField, Range(10, maxResolution)]
    private int resolution = 10;

    [SerializeField]
    private ComputeShader computeShader = null;

    [SerializeField]
    private Material material = null;

    [SerializeField]
    private Mesh mesh = null;

    [SerializeField]
    private FunctionLibrary.FunctionName targetFunction = default;

    [SerializeField, Min(0f)]
    private float functionDuration = 1f, transitionDuration = 1f;


    private static readonly int positionId = Shader.PropertyToID("_Positions");
    private static readonly int resolutionId = Shader.PropertyToID("_Resolution");
    private static readonly int stepId = Shader.PropertyToID("_Step");
    private static readonly int timeId = Shader.PropertyToID("_Time");
    private static readonly int transitionProgressId = Shader.PropertyToID("_TransitionProgress");


    private bool transitioning = false;
    private FunctionLibrary.FunctionName transitionFunction = default;
    private float duration = 0.0f;

    private ComputeBuffer positionBuffer = default;


    private void OnEnable()
    {
        positionBuffer = new ComputeBuffer(maxResolution * maxResolution, 3 * 4);
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

        UpdateFunctionOnGPU();
    }

    private FunctionLibrary.FunctionName PickNextFunction()
    {
        return transitionMode == TransitionMode.Cycle
            ? FunctionLibrary.GetNextFunctionNames(targetFunction)
            : FunctionLibrary.GetRandomFunctionNameOtherThan(targetFunction);
    }

    private void UpdateFunctionOnGPU()
    {
        float step = 2f / resolution;

        int kernelIndex = (int) targetFunction + (int) (transitioning ? transitionFunction : targetFunction) * FunctionLibrary.FunctionCount;

        computeShader.SetInt(resolutionId, resolution);
        computeShader.SetFloat(stepId, step);
        computeShader.SetFloat(timeId, Time.time);
        if (transitioning)
        {
            computeShader.SetFloat(transitionProgressId, Mathf.SmoothStep(0f, 1f, duration / transitionDuration));
        }

        computeShader.SetBuffer(kernelIndex, positionId, positionBuffer);

        int groupsCount = Mathf.CeilToInt(resolution / 8.0f);
        computeShader.Dispatch(kernelIndex, groupsCount, groupsCount, 1);

        material.SetBuffer(positionId, positionBuffer);
        material.SetFloat(stepId, step);
        Bounds bounds = new Bounds(Vector3.zero, Vector3.one * (2f + 2f / resolution));
        Graphics.DrawMeshInstancedProcedural(mesh, 0, material, bounds, resolution * resolution);
    }

    private void OnDisable()
    {
        positionBuffer.Release();
        positionBuffer = null;
    }
}