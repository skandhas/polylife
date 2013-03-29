#pragma once

struct Face {
    size_t p1, p2, p3, p4;
    size_t connect_p1, connect_p2, noconnect_p;
    glm::vec3 normal;
};

struct VectorKeyFuncs
{
    inline size_t operator()(const glm::vec3& v) const
    {
        return  std::hash<float>()(v.x) ^
                std::hash<float>()(v.y) ^
                std::hash<float>()(v.z);
    }
    
    inline bool operator()(const glm::vec3& a, const glm::vec3& b) const
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

typedef std::vector<Face> FaceBuffer;
typedef std::vector<glm::vec3> Vec3Buffer;
typedef std::unordered_set<glm::vec3, VectorKeyFuncs> Vec3Set;
typedef std::unordered_map<size_t, std::unordered_set<size_t>> VertToFaceMap;
typedef std::vector<std::unordered_set<size_t>> ConnectingFaceSetBuffer;
typedef std::vector<float> VertexArrayBuffer;
typedef std::vector<unsigned char> TextureBuffer;

