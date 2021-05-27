using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenerateSpheres : MonoBehaviour
{
    private float gap = 1.5f;
    public Material colorMaterial = null;

    private void Start()
    {
        for (int row = -25; row != 25; ++row)
        {
            for (int col = -25; col != 25; ++col)
            {
                GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
                sphere.AddComponent<ModifyColor>();
                sphere.GetComponent<MeshRenderer>().material = colorMaterial;
                sphere.transform.localScale = new Vector3(gap, gap, gap);
                sphere.transform.position = new Vector3(gap * row, 0, gap * col);
            }
        }
    }
}