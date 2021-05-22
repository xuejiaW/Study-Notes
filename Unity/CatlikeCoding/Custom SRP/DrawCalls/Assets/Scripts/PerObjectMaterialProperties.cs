using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[DisallowMultipleComponent]
public class PerObjectMaterialProperties : MonoBehaviour
{
    [SerializeField]
    private Color baseColor = Color.white;

    private static int baseColorID = Shader.PropertyToID("_BaseColor");

    private static MaterialPropertyBlock block = null;

    private void Awake()
    {
        OnValidate();
    }

    private void OnValidate()
    {
        if (block == null)
            block = new MaterialPropertyBlock();

        block.SetColor(baseColorID, baseColor);
        GetComponent<Renderer>().SetPropertyBlock(block);
    }
}
