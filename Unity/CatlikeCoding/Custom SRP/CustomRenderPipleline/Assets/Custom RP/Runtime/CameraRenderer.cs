using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

public partial class CameraRenderer
{
    private Camera camera = null;
    private ScriptableRenderContext renderContext = default;
    private CullingResults cullingResults = default;
    private CommandBuffer buffer = new CommandBuffer { name = "Render Camera" };
    private static ShaderTagId unlitShaderTagId = new ShaderTagId("SRPDefaultUnlit");

    partial void DrawUnSupportedShadersGeometry();
    partial void DrawGizmos();
    partial void PrepareForSceneWindow();
    partial void PrepareBuffer();

    public void Render(ScriptableRenderContext renderContext, Camera camera)
    {
        this.renderContext = renderContext;
        this.camera = camera;

        PrepareBuffer();
        PrepareForSceneWindow();
        if (!Cull()) // Get Culling parameters failed
            return;

        Setup();
        DrawVisibleGeometry();
        DrawUnSupportedShadersGeometry();
        DrawGizmos();
        Submit();
    }

    private void Setup()
    {
        renderContext.SetupCameraProperties(camera);
        CameraClearFlags flags = camera.clearFlags;
        buffer.ClearRenderTarget(flags <= CameraClearFlags.Depth, flags == CameraClearFlags.Color,
                    flags == CameraClearFlags.Color ? camera.backgroundColor.linear : Color.clear);
        buffer.BeginSample("Profile Render Camera");
        ExecuteCommandBuffer();
    }

    private void DrawVisibleGeometry()
    {
        // Render Opaque objects
        SortingSettings sortingSettings = new SortingSettings(camera) { criteria = SortingCriteria.CommonOpaque };
        DrawingSettings drawingSettings = new DrawingSettings(unlitShaderTagId, sortingSettings);
        FilteringSettings filteringSettings = new FilteringSettings(RenderQueueRange.opaque);
        renderContext.DrawRenderers(cullingResults, ref drawingSettings, ref filteringSettings);

        renderContext.DrawSkybox(camera);

        // Render Transparent objects
        sortingSettings.criteria = SortingCriteria.CommonTransparent;
        drawingSettings.sortingSettings = sortingSettings;
        filteringSettings.renderQueueRange = RenderQueueRange.transparent;
        renderContext.DrawRenderers(cullingResults, ref drawingSettings, ref filteringSettings);
    }


    private void Submit()
    {
        buffer.EndSample("Profile Render Camera");
        ExecuteCommandBuffer();
        renderContext.Submit();
    }

    private void ExecuteCommandBuffer()
    {
        renderContext.ExecuteCommandBuffer(buffer);
        buffer.Clear();
    }

    private bool Cull()
    {
        if (camera.TryGetCullingParameters(out ScriptableCullingParameters cullingParameters))
        {
            cullingResults = renderContext.Cull(ref cullingParameters);
            return true;
        }
        return false;
    }
}
