using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstancedDrawingMeshBall : MonoBehaviour
{
    private static int baseColorID = Shader.PropertyToID("_BaseColor");

    [SerializeField]
    private Mesh mesh = default;

    [SerializeField]
    private Material material = default;

    private Matrix4x4[] matrices = new Matrix4x4[1023];
    private Vector4[] baseColors = new Vector4[1023];
    private MaterialPropertyBlock propertyBlock = null;

    private void Awake()
    {
        for (int i = 0; i != matrices.Length; ++i)
        {
            matrices[i] = Matrix4x4.TRS(Random.insideUnitSphere * 10f,
            Quaternion.Euler(Random.value * 360f, Random.value * 360f, Random.value * 360f),
            Vector3.one * Random.Range(0.5f, 0.1f));
            baseColors[i] = new Vector4(Random.value, Random.value, Random.value, Random.Range(0.5f, 1f));
        }
    }

    private void Update()
    {
        if (propertyBlock == null)
        {
            propertyBlock = new MaterialPropertyBlock();
            propertyBlock.SetVectorArray(baseColorID, baseColors);
        }

        Graphics.DrawMeshInstanced(mesh, 0, material, matrices, 1023, propertyBlock);
    }
}
