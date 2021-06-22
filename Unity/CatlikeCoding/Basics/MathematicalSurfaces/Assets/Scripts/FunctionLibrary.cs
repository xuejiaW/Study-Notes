using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.Mathf;

public static class FunctionLibrary
{
    public delegate Vector3 Function(float u, float v, float t);

    public enum FunctionName
    {
        Wave,
        MultiWave,
        Ripple,
        Sphere,
        PerturbSphere,
        Torus,
        PerturbTorus
    }

    private static Function[] functions = {Wave, MultiWave, Ripple, Sphere, PerturbSphere, Torus, PerturbTorus};

    public static Function GetFunction(FunctionName functionName)
    {
        return functions[(int) functionName];
    }

    public static Vector3 Wave(float u, float v, float t)
    {
        Vector3 result;
        result.x = u;
        result.y = Sin(PI * (u + v + t));
        result.z = v;
        return result;
    }

    public static Vector3 MultiWave(float u, float v, float t)
    {
        Vector3 result;
        result.x = u;

        result.y = Sin(PI * (u + 0.5f * t));
        result.y += 0.5f * Sin(2 * PI * (v + t));
        result.y += Sin(PI * (u + v + 0.25f * t));
        result.y *= (1f / 2.5f);

        result.z = v;

        return result;
    }

    public static Vector3 Ripple(float u, float v, float t)
    {
        float distance = Sqrt(u * u + v * v);

        Vector3 result;
        result.x = u;
        result.y = Sin(PI * (4f * distance - t));
        result.y /= (1f * 10f + distance);
        result.z = v;
        return result;
    }

    public static Vector3 Sphere(float u, float v, float t)
    {
        Vector3 result;
        float r = Cos(0.5f * PI * v);
        result.x = r * Sin(PI * u);
        result.y = Sin(PI * v * 0.5f);
        result.z = r * Cos(PI * u);
        return result;
    }

    public static Vector3 PerturbSphere(float u, float v, float t)
    {
        Vector3 result;
        float r = 0.9f + 0.1f * Sin(PI * (6f * u + 4f * v + t));
        float s = r * Cos(0.5f * PI * v);
        result.x = s * Sin(PI * u);
        result.y = r * Sin(PI * v * 0.5f);
        result.z = s * Cos(PI * u);
        return result;
    }

    public static Vector3 Torus(float u, float v, float t)
    {
        Vector3 result;
        float r1 = 0.75f;
        float r2 = 0.25f;

        float s = r1 + r2 * Cos(PI * v);
        result.x = s * Sin(PI * u);
        result.y = r2 * Sin(PI * v);
        result.z = s * Cos(PI * u);
        return result;
    }

    public static Vector3 PerturbTorus(float u, float v, float t)
    {
        Vector3 result;
        float r1 = 0.7f + 0.1f * Sin(PI * (6f * u + 0.5f * t));
        float r2 = 0.15f + 0.05f * Sin(PI * (8f * u + 4f * v + 2f * t));

        float s = r1 + r2 * Cos(PI * v);
        result.x = s * Sin(PI * u);
        result.y = r2 * Sin(PI * v);
        result.z = s * Cos(PI * u);
        return result;
    }
}