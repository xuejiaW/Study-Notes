using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using UnityEngine.Rendering;

public partial class CameraRenderer
{

#if UNITY_EDITOR || DEVELOPMENT_BUILD

    private string samplerName = "";
    private static ShaderTagId[] legacyShaderTagIds =
    {
        new ShaderTagId("Always"),
        new ShaderTagId("ForwardBase"),
        new ShaderTagId("PrepassBase"),
        new ShaderTagId("Vertex"),
        new ShaderTagId("VertexLMRGBM"),
        new ShaderTagId("VertexLM")
    };

    private static Material errorMaterial = null;

    partial void DrawUnSupportedShadersGeometry()
    {
        if (errorMaterial == null)
            errorMaterial = new Material(Shader.Find("Hidden/InternalErrorShader"));

        DrawingSettings drawingSettings = new DrawingSettings();
        drawingSettings.sortingSettings = new SortingSettings(camera);
        drawingSettings.overrideMaterial = errorMaterial;

        for (int i = 0; i != legacyShaderTagIds.Length; ++i)
            drawingSettings.SetShaderPassName(i, legacyShaderTagIds[i]);

        FilteringSettings filteringSettings = FilteringSettings.defaultValue;

        renderContext.DrawRenderers(cullingResults, ref drawingSettings, ref filteringSettings);
    }

    partial void DrawGizmos()
    {
        if (Handles.ShouldRenderGizmos())
        {
            renderContext.DrawGizmos(camera, GizmoSubset.PreImageEffects);
            renderContext.DrawGizmos(camera, GizmoSubset.PostImageEffects);
        }
    }

    partial void PrepareForSceneWindow()
    {
        if (camera.cameraType == CameraType.SceneView)
        {
            ScriptableRenderContext.EmitWorldGeometryForSceneView(camera);
        }
    }

    partial void PrepareBuffer()
    {
        buffer.name = samplerName = camera.name;
    }
#endif
}
