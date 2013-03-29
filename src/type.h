/*
 
 Copyright (c) 2013 h2so5 <mail@h2so5.net>
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
 
 */

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

