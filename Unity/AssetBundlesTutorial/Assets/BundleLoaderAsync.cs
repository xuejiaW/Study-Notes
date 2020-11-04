using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class BundleLoaderAsync : MonoBehaviour
{
    public string assetName = "BundledSpriteObject";
    public string bundleName = "testbundle.test";

    IEnumerator Start()
    {
        AssetBundleCreateRequest asyncBundleRequest = AssetBundle.LoadFromFileAsync(Path.Combine(Application.streamingAssetsPath, bundleName));
        yield return asyncBundleRequest;

        AssetBundle loadAssetBundle = asyncBundleRequest.assetBundle;

        AssetBundleRequest assetRequest = loadAssetBundle.LoadAssetAsync<GameObject>(assetName);
        yield return assetRequest;

        GameObject prefab = assetRequest.asset as GameObject;
        Instantiate(prefab);

        loadAssetBundle.Unload(false);
    }
}