using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ModifyColor : MonoBehaviour
{
    private MeshRenderer meshRenderer = null;

    private MaterialPropertyBlock propertyBlock = null;

    private void Start()
    {
        meshRenderer = GetComponent<MeshRenderer>();
        propertyBlock = new MaterialPropertyBlock();
    }

    private void Update()
    {
        Color color = new Color(Mathf.Sin(Time.time), Mathf.Cos(Time.time), 0, 1);

        // // Using Material
        // meshRenderer.material.color = color;

        // // Using MaterialPropertyBlock
        propertyBlock.SetColor("_Color", color);
        meshRenderer.SetPropertyBlock(propertyBlock);
    }
}

