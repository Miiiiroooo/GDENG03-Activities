using UnityEngine;
using UnityEditor;
using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using Unity.Plastic.Newtonsoft.Json.Linq;
using Unity.VisualScripting;


public class SceneHandler : EditorWindow
{
    CustomScene currentScene = null;


    [MenuItem("Finals/SceneHandler")]
    public static void ShowWindow()
    {
        GetWindow<SceneHandler>().Show();
    }

    private void OnGUI()
    {
        GUILayout.BeginHorizontal();
        GUILayout.Label("Current Scene: ", GUILayout.Width(GUI.skin.label.CalcSize(new GUIContent("Current Scene: ")).x));
        string newSceneName = GUILayout.TextField(currentScene.SceneName);
        currentScene.SceneName = newSceneName;
        GUILayout.EndHorizontal();
        GUILayout.Space(20);

        if (GUILayout.Button("Open Scene"))
        {
            OnOpenScene();
        }
        GUILayout.Space(10);

        if (GUILayout.Button("Save Scene"))
        {
            OnSaveScene();
        }
    }

    private void OnEnable()
    {
        currentScene = new CustomScene();
        MeshManager.CreateMeshTable();
    }


    #region Open Scene
    private void OnOpenScene()
    {
        string currentDir = System.IO.Directory.GetCurrentDirectory();
        string rootDir = currentDir.TrimEnd('\\').Remove(currentDir.LastIndexOf('\\') + 1) + "levels";
        string path = EditorUtility.OpenFilePanel("Open new scene", rootDir, "level");

        if (path.Length != 0 && File.Exists(path))
        {
            ClearCurrentScene();

            using (StreamReader reader = new StreamReader(path))
            {
                string json = reader.ReadToEnd();
                JObject jsonScene = JObject.Parse(json);

                currentScene = new CustomScene();
                currentScene.SceneName = jsonScene["SceneName"].ToString();
                currentScene.RootObjs = new List<GameObject>();

                var objArray = (JArray)jsonScene["GameObjects"];
                foreach (var jsonObj in  objArray)
                {
                    ParseIntoObjs((JObject)jsonObj, null);
                }
            }
        }
    }

    private void ClearCurrentScene()
    {
        var allObjsInScene = UnityEngine.Object.FindObjectsOfType<GameObject>();
        foreach (var obj in allObjsInScene)
        {
            GameObject.DestroyImmediate(obj);
        }
    }

    private void ParseIntoObjs(JObject jsonObj, GameObject parent)
    {
        GameObject newObj = new GameObject(jsonObj["ObjName"].Value<string>());
        newObj.SetActive(jsonObj["IsEnabled"].Value<bool>());

        if (parent == null) currentScene.RootObjs.Add(newObj);
        else newObj.transform.parent = parent.transform;

        var childArray = (JArray)jsonObj["ChildrenList"];
        foreach (var jsonChild in childArray)
        {
            ParseIntoObjs((JObject)jsonChild, newObj);
        }

        var compArray = (JArray)jsonObj["ComponentsList"];
        foreach (var jsonToken in compArray)
        {
            JObject jsonComp = (JObject)jsonToken;
            string compType = jsonComp["ComponentType"].Value<string>();

            if (compType == "Transform")
            {
                InitializeTransform(jsonComp, newObj);
            }
            else if (compType == "MeshRenderer")
            {
                InitializeMeshRenderer(jsonComp, newObj);
            }
            else if (compType == "RigidBody3D")
            {
                InitializeRigidBody3D(jsonComp, newObj);
            }
        }
    }

    private void InitializeTransform(JObject jsonComp, GameObject owner)
    {
        Transform t = owner.transform;

        Vector3 pos = new Vector3
        (
            jsonComp["Position"]["x"].Value<float>(),
            jsonComp["Position"]["y"].Value<float>(),
            jsonComp["Position"]["z"].Value<float>()
        );

        Vector3 euler = new Vector3
        (
            jsonComp["Rotation"]["x"].Value<float>(),
            jsonComp["Rotation"]["y"].Value<float>(),
            jsonComp["Rotation"]["z"].Value<float>()
        );

        Vector3 scale = new Vector3
        (
            jsonComp["Scale"]["x"].Value<float>(),
            jsonComp["Scale"]["y"].Value<float>(),
            jsonComp["Scale"]["z"].Value<float>()
        );

        t.position = pos;
        t.eulerAngles = euler;
        t.localScale = scale;
    }

    private void InitializeMeshRenderer(JObject jsonComp, GameObject owner)
    {
        MeshRenderer mr = owner.AddComponent<MeshRenderer>();
        mr.sharedMaterial = AssetDatabase.GetBuiltinExtraResource<Material>("Default-Material.mat");

        if (jsonComp["Material"]["MaterialType"].Value<string>() == "ColorMaterial")
        {
            Color matColor = new Color
            (
                jsonComp["Material"]["Color"]["r"].Value<float>(),
                jsonComp["Material"]["Color"]["g"].Value<float>(),
                jsonComp["Material"]["Color"]["b"].Value<float>()
            );

            MaterialPropertyBlock propertyBlock = new MaterialPropertyBlock();
            propertyBlock.SetColor("_Color", matColor);
            mr.SetPropertyBlock(propertyBlock);
        }

        int meshInt = jsonComp["MeshType"].Value<int>();
        PrimitiveType meshType = GetPrimitiveType(meshInt);

        MeshFilter mf = owner.AddComponent<MeshFilter>();
        mf.sharedMesh = MeshManager.GetMesh(meshType);
    }

    private void InitializeRigidBody3D(JObject jsonComp, GameObject owner)
    {
        int bodyType = jsonComp["BodyType"].Value<int>();
        int meshInt = jsonComp["MeshType"].Value<int>();
        PrimitiveType meshType = GetPrimitiveType(meshInt);

        switch(meshType)
        {
            case PrimitiveType.Cube:
                owner.AddComponent<BoxCollider>();
                break;
            case PrimitiveType.Sphere:
                owner.AddComponent<SphereCollider>();
                break;
            case PrimitiveType.Plane:
                var col = owner.AddComponent<MeshCollider>();
                col.sharedMesh = MeshManager.GetMesh(meshType);
                owner.transform.localScale = owner.transform.localScale / 2.0f;
                break;
            case PrimitiveType.Capsule:
                owner.AddComponent<CapsuleCollider>();
                break;
            default:
                break;
        }

        if (bodyType == 0) return; // static object, no rb

        Rigidbody rb = owner.AddComponent<Rigidbody>();
        rb.mass = jsonComp["Mass"].Value<float>();
        rb.useGravity = jsonComp["GravityEnabled"].Value<bool>();
        rb.drag = jsonComp["LinearDamping"].Value<float>();
        rb.angularDrag = jsonComp["AngularDamping"].Value<float>();
        rb.isKinematic = (bodyType == 1);
    }

    private PrimitiveType GetPrimitiveType(int meshInt)
    {
        if (meshInt == 1) return PrimitiveType.Cube;
        if (meshInt == 2) return PrimitiveType.Sphere;
        if (meshInt == 4) return PrimitiveType.Plane;
        if (meshInt == 8) return PrimitiveType.Capsule;
        return PrimitiveType.Cube;
    }
    #endregion


    #region Save Scene
    private void OnSaveScene()
    {
        string currentDir = System.IO.Directory.GetCurrentDirectory();
        string rootDir = currentDir.TrimEnd('\\').Remove(currentDir.LastIndexOf('\\') + 1) + "levels";
        string path = EditorUtility.SaveFilePanel("Save new scene", rootDir, "New Level", "level");

        if (path.Length != 0)
        {
            using (StreamWriter writer = new StreamWriter(path))
            {
                JObject jsonRoot = new JObject();
                jsonRoot.Add("SceneName", currentScene.SceneName);

                JArray objArray = new JArray();
                var rootObjsList = Array.FindAll(UnityEngine.Object.FindObjectsOfType<GameObject>(),
                                                 obj => obj.transform.parent == null);
                foreach (var rootObj in rootObjsList)
                {
                    SaveObject(rootObj, objArray);
                }

                jsonRoot.Add("GameObjects", objArray);

                writer.Write(jsonRoot.ToString());
            }
        }
    }

    private void SaveObject(GameObject objToSave, JArray objArray)
    {
        JObject newJsonObj = new JObject();
        newJsonObj.Add("ObjName", objToSave.name);
        newJsonObj.Add("IsEnabled", objToSave.activeSelf);

        JArray childrenArray = new JArray();
        foreach (Transform child in objToSave.transform)
        {
            SaveObject(child.gameObject, childrenArray);
        }
        newJsonObj.Add("ChildrenList", childrenArray);

        JArray compArray = new JArray();
        foreach (var comp in objToSave.GetComponents(typeof(Component)))
        {
            SaveComponent(comp, compArray);
        }
        newJsonObj.Add("ComponentsList", compArray);

        objArray.Add(newJsonObj);
    }

    private void SaveComponent(Component comp, JArray compArray)
    {
        JObject newJsonComp = new JObject();

        if (comp is Transform)
        {
            SaveTransform((Transform)comp, newJsonComp);
        }
        else if (comp is MeshRenderer)
        {
            SaveMeshRenderer((MeshRenderer)comp, comp.GetComponent<MeshFilter>(), newJsonComp);
        }
        else if (comp is Collider)
        {
            SaveRigidBody3D(comp.GetComponent<Rigidbody>(), (Collider)comp, newJsonComp);
        }

        if (newJsonComp.HasValues) compArray.Add(newJsonComp);
    }

    private void SaveTransform(Transform t, JObject jsonComp)
    {
        jsonComp.Add("ComponentType", "Transform");

        JObject jsonPos = new JObject();
        jsonPos.Add("x", t.position.x);
        jsonPos.Add("y", t.position.y);
        jsonPos.Add("z", t.position.z);
        jsonComp.Add("Position", jsonPos);

        JObject jsonEuler = new JObject();
        jsonEuler.Add("x", t.eulerAngles.x);
        jsonEuler.Add("y", t.eulerAngles.y);
        jsonEuler.Add("z", t.eulerAngles.z);
        jsonComp.Add("Rotation", jsonEuler);

        JObject jsonScale = new JObject();
        jsonScale.Add("x", t.localScale.x);
        jsonScale.Add("y", t.localScale.y);
        jsonScale.Add("z", t.localScale.z);
        jsonComp.Add("Scale", jsonScale);
    }

    private void SaveMeshRenderer(MeshRenderer mr, MeshFilter mf, JObject jsonComp)
    {
        jsonComp.Add("ComponentType", "MeshRenderer");
        jsonComp.Add("ModelName", "");

        int meshType = 0;
        foreach (var kvPair in MeshManager.GetMeshTable())
        {
            if (mf.sharedMesh == kvPair.Value)
            {
                meshType = (int)kvPair.Key + 1;
            }
        }
        jsonComp.Add("MeshType", meshType);

        jsonComp.Add("IsRainbowed", false);

        JObject jsonMat = new JObject();
        jsonMat.Add("MaterialType", "ColorMaterial");

        Color color = mr.sharedMaterial.color;
        JObject jsonColor = new JObject();
        jsonColor.Add("r", color.r);
        jsonColor.Add("g", color.g);
        jsonColor.Add("b", color.b);
        jsonMat.Add("Color", jsonColor);

        jsonComp.Add("Material", jsonMat);
    }

    private void SaveRigidBody3D(Rigidbody rb, Collider col, JObject jsonComp)
    {
        jsonComp.Add("ComponentType", "RigidBody3D");
        jsonComp.Add("Mass", (rb == null) ? 10.0f : rb.mass);

        int bodyType = (rb == null) ? 0 : (rb.isKinematic) ? 1 : 2;
        jsonComp.Add("BodyType", bodyType);
        jsonComp.Add("GravityEnabled", (rb == null) ? false : true);
        jsonComp.Add("LinearDamping", (rb == null) ? 0.0f : rb.drag);
        jsonComp.Add("AngularDamping", (rb == null) ? 0.0f : rb.angularDrag);

        int meshType = 0;
        if (col is BoxCollider) meshType = 1;
        else if (col is SphereCollider) meshType = 2;
        else if (col is CapsuleCollider) meshType = 8;
        else
        {
            MeshCollider mc = (MeshCollider)col;
            if (mc.sharedMesh == MeshManager.GetMesh(PrimitiveType.Plane)) meshType = 4;
        }
        jsonComp.Add("MeshType", meshType);
    }
    #endregion
}