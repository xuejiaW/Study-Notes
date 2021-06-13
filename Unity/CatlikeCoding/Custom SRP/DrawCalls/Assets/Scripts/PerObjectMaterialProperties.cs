using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[DisallowMultipleComponent]
public class PerObjectMaterialProperties : MonoBehaviour
{
    [SerializeField]
    private Color baseColor = Color.white;
    [SerializeField]
    private float cutoff = 0.5f;

    private static int baseColorID = Shader.PropertyToID("_BaseColor");
    private static int cutoffID = Shader.PropertyToID("_Cutoff");

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
        block.SetFloat(cutoffID, cutoff);

        GetComponent<Renderer>().SetPropertyBlock(block);
    }
}
