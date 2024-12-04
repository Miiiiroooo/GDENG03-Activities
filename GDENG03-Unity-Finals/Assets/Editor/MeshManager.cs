using System.Collections.Generic;
using UnityEngine;

public class MeshManager
{
    private static Dictionary<PrimitiveType, Mesh> meshTable;

    public static bool IsMeshTableInitialized()
    {
        return meshTable != null;
    }

    public static void CreateMeshTable()
    {
        meshTable = new();

        PrimitiveType[] typeList = 
        { 
            PrimitiveType.Cube, 
            PrimitiveType.Sphere, 
            PrimitiveType.Plane, 
            PrimitiveType.Capsule 
        };

        foreach (PrimitiveType type in typeList)
        {
            var temp = GameObject.CreatePrimitive(type);
            meshTable[type] = temp.GetComponent<MeshFilter>().sharedMesh;
            GameObject.DestroyImmediate(temp);
        }
    }

    public static Mesh GetMesh(PrimitiveType type)
    {
        if (!IsMeshTableInitialized()) return null;
        return meshTable[type];
    }

    public static Dictionary<PrimitiveType, Mesh> GetMeshTable()
    {
        return meshTable;
    }
}
