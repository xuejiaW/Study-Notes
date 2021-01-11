using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestIMGUI : MonoBehaviour
{
    public Texture2D icon;
    private string textFieldString = "text field";
    private string textAreaString = "text area";
    private bool toggleBool = true;

    private int toolbarInt = 1;
    private string[] toolbarStrings = { "ToolBar1", "Toolbar2", "Toolbar3" };

    private int selectionGridInt = 2;
    private string[] selectionStrings = { "Grid 1", "Grid 2", "Grid 3", "Grid 4" };

    private float hSliderValue = 3.0f;
    private float vSliderValue = 3.0f;

    private float hScrollBarValue = 3.0f;
    private float vScrollBarValue = 3.0f;

    private Vector2 scrollViewVector = Vector2.zero;
    private string innerText = "I am inside the scrollView";

    Rect windowRect = new Rect(10, 10, 100, 100);

    public GUIStyle customButtonStyle;
    public GUISkin customSkin;

    private float sliderValue = 1.0f;
    private float maxSliderValue = 10.0f;

    private void OnGUI()
    {
        // // Example 1:
        // if (GUILayout.Button("Press Me"))
        //     Debug.Log("Hello!");

        // // Example 2:
        // GUI.Box(new Rect(10, 10, 100, 90), "Loader Menu");

        // if (GUI.Button(new Rect(20, 40, 80, 20), "Level 1"))
        // {
        //     Application.LoadLevel(1);
        // }

        // if (GUI.Button(new Rect(20, 70, 80, 20), "Level 2"))
        // {
        //     Application.LoadLevel(2);
        // }

        // // Example 3:
        // GUI.Box(new Rect(0, 0, 100, 50), "Top-left");
        // GUI.Box(new Rect(Screen.width - 100, 0, 100, 50), "Top-right");
        // GUI.Box(new Rect(0, Screen.height - 50, 100, 50), "Bottom-left");
        // GUI.Box(new Rect(Screen.width - 100, Screen.height - 50, 100, 50), "Bottom-right");

        // // Example 4:
        // GUI.Label(new Rect(0, 0, 100, 50), "This is the text string for a Label Control");
        // GUI.Label(new Rect(0, 50, 100, 50), icon);

        // if (GUI.Button(new Rect(10, 110, 100, 50), icon)) print("you clicked the icon");
        // if (GUI.Button(new Rect(10, 170, 100, 20), "This is text")) print("you clicked the text button");

        // // Example 5：
        // GUI.Box (new Rect (10,10,100,50), new GUIContent("This is text", icon));

        // Example 6:
        // GUI.Button(new Rect(10, 10, 100, 20), new GUIContent("Click me", icon, "This is the tooltip"));
        // GUI.Label(new Rect(10, 40, 100, 20), GUI.tooltip);

        // Example 7: all controls
        // GUI.Label(new Rect(25, 25, 100, 30), "Label");
        // if (GUI.Button(new Rect(25, 60, 100, 30), "Button")) { Debug.Log("Click button"); }
        // if (GUI.RepeatButton(new Rect(25, 95, 100, 30), "RepeatButton")) { Debug.Log("Click repeatButton"); }
        // textFieldString = GUI.TextField(new Rect(25, 130, 100, 50), textFieldString);
        // textAreaString = GUI.TextArea(new Rect(25, 185, 100, 50), textAreaString);
        // toggleBool = GUI.Toggle(new Rect(25, 240, 100, 50), toggleBool, "Toggle");
        // toolbarInt = GUI.Toolbar(new Rect(25, 295, 250, 50), toolbarInt, toolbarStrings);
        // selectionGridInt = GUI.SelectionGrid(new Rect(25, 350, 250, 100), selectionGridInt, selectionStrings, 3);
        // hSliderValue = GUI.HorizontalSlider(new Rect(25, 455, 250, 25), hSliderValue, 0, 10);
        // vSliderValue = GUI.VerticalSlider(new Rect(150, 25, 25, 250), vSliderValue, 0, 10);
        // hScrollBarValue = GUI.HorizontalScrollbar(new Rect(25, 475, 250, 25), hScrollBarValue, 1, 0, 10);
        // vScrollBarValue = GUI.VerticalScrollbar(new Rect(200, 25, 25, 200), vScrollBarValue, 1, 0, 10);
        // scrollViewVector = GUI.BeginScrollView(new Rect(25, 505, 200, 200), scrollViewVector, new Rect(0, 0, 400, 400));
        // innerText = GUI.TextArea(new Rect(0, 0, 400, 300), innerText);
        // GUI.Label(new Rect(0, 300, 400, 100), icon);
        // GUI.EndScrollView();
        // windowRect = GUI.Window(0, windowRect, WindowFunction, "A Window");

        // Example 8 : GUI.changed
        // toolbarInt = GUI.Toolbar(new Rect(20, 20, 250, 50), toolbarInt, toolbarStrings);
        // if (GUI.changed)
        // {
        //     Debug.Log(toolbarInt);
        // }

        // // Example 9: Styles:
        // GUI.Label(new Rect(20, 20, 200, 100), "Hi - I'm a label looking like a box", "box");
        // GUI.Button(new Rect(20, 140, 180, 20), "This is a button", "toggle");

        // // Example 10: Custom Styles:
        // GUI.Button(new Rect(20, 20, 200, 100), "Custom Button", customButtonStyle);

        // // Example 11 : Custom GUI Skins
        // GUI.skin = customSkin;
        // GUI.Button(new Rect(10, 10, 150, 20), "Custom skinned button");
        // GUI.skin = null;
        // GUI.Button(new Rect(10, 40, 150, 20), "Default skinned button");

        // Example 12: Dynamic modifying style property
        //Set the GUIStyle style to be label
        // GUI.skin = customSkin;
        // GUIStyle style = GUI.skin.GetStyle("label");
        // style.fontSize = (int)(20.0f + 10.0f * Mathf.Sin(Time.time));
        // GUI.Label(new Rect(10, 10, 200, 80), "Hello World!");

        // // Example 13: Simple GUILayout
        // GUILayout.Box("Loader Menu");
        // if (GUILayout.Button("Level 1"))
        // {
        //     Debug.Log("Level 1");
        // }
        // if (GUILayout.Button("Level 2"))
        // {
        //     Debug.Log("Level 2");
        // }

        // Example 14 : Groups
        // GUI.BeginGroup(new Rect(Screen.width / 2 + 50 * Mathf.Sin(Time.time), Screen.height / 2 - 50, 100, 100));
        // GUI.Box(new Rect(0, 0, 100, 100), "Group is here");
        // GUI.Button(new Rect(10, 40, 80, 30), "Click me");
        // GUI.EndGroup();

        // Example 15: Group Clip
        // GUI.BeginGroup(new Rect(20, 20, (Mathf.Sin(Time.time) + 1) / 2.0f * 256, 32));
        // GUI.Box(new Rect(0, 0, 256, 32), icon);
        // GUI.EndGroup();

        // // Example 16: Area
        // GUILayout.Button("I am not inside an Area");
        // GUILayout.BeginArea(new Rect(Screen.width / 2, Screen.height / 2, 300, 300));
        // GUILayout.Button("I am completely inside an Area");
        // GUILayout.EndArea();
        // GUILayout.Button("I am not inside an Area too");

        // // Example 17: Horizontal / Vertical Group
        // GUILayout.BeginHorizontal();
        // // Place a Button normally
        // if (GUILayout.RepeatButton("Increase max \n Slider Value"))
        //     sliderValue += 3.0f * Time.deltaTime;
        // GUILayout.BeginVertical();
        // GUILayout.Box("Slider Value: " + Mathf.Round(sliderValue));
        // sliderValue = GUILayout.HorizontalSlider(sliderValue, 0.0f, 10.0f);
        // GUILayout.EndVertical();
        // GUILayout.EndHorizontal();

        // Example 18: Area width and GUILayoutOptions
        // GUILayout.BeginArea(new Rect(100, 100, 300, 50));
        // GUILayout.Button("ABC");
        // GUILayout.Button("ABC", GUILayout.Width(50));
        // GUILayout.EndArea();
        // GUILayout.Button("ABCD");

        // GUILayout.Button("Short Button", GUILayout.ExpandWidth(false));
        GUILayout.Button("Short Button");
        GUILayout.Button("Very very long Button");

    }

    private void WindowFunction(int windowID)
    {
        Debug.Log("window ID" + windowID);
        GUI.Label(new Rect(25, 25, 100, 30), "Label");

        if (GUI.Button(new Rect(25, 60, 100, 30), "Button")) { Debug.Log("Click button"); }
        if (GUI.RepeatButton(new Rect(25, 95, 100, 30), "RepeatButton")) { Debug.Log("Click repeatButton"); }
    }
}





