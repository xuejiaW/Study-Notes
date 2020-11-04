using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class BundledObjectLoader : MonoBehaviour
{
    public string assetName = "BundledSpriteObject";
    public string bundleName = "testbundle.test";

    private void Start()
    {
        AssetBundle localAssetBundle = AssetBundle.LoadFromFile(Path.Combine(Application.streamingAssetsPath, bundleName));
        GameObject asset = localAssetBundle.LoadAsset<GameObject>(assetName);
        Instantiate(asset);
        localAssetBundle.Unload(false);
    }

}

