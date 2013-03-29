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

#include "model.h"
#include "consts.h"


/* public */ Model::Model(const std::string& path)
{
    std::ifstream ifs(path.c_str(), std::ios::in);
    
    FaceBuffer    face_buffer;
    VertToFaceMap vertex_to_face_map;
    Vec3Set       unique_vertex_set;
    
    this->ParseSTL(&ifs, &face_buffer, &vertex_to_face_map, &unique_vertex_set);
    
    Vec3Buffer unique_vertex_buffer(unique_vertex_set.begin(),  unique_vertex_set.end());
    this->ConvertTrisToQuads(&face_buffer, vertex_to_face_map, unique_vertex_buffer);
    
    this->CalcConnectingFace(&connecting_face_buffer_, face_buffer);
    this->GenerateVertexArray(&vertex_array_, face_buffer, unique_vertex_buffer);
}


/* public */ const ConnectingFaceSetBuffer& Model::connecting_face_buffer() const
{
    return this->connecting_face_buffer_;
}


/* public */ const VertexArrayBuffer& Model::vertex_array() const
{
    return this->vertex_array_;
}


/* private */ void Model::ParseSTL(std::ifstream* ifs,
                                   FaceBuffer* face_buffer,
                                   VertToFaceMap* vertex_to_face_map,
                                   Vec3Set* unique_vertex_set)
{
    FaceBuffer& face_buffer_ref = *face_buffer;
    VertToFaceMap& vertex_to_face_map_ref = *vertex_to_face_map;
    Vec3Set& unique_vertex_set_ref = *unique_vertex_set;
    
    Vec3Buffer vertex_buffer;
    Vec3Buffer normal_buffer;
    
    std::string line;
    while (std::getline(*ifs, line))
    {
        glm::vec3 vect;
        line.insert(line.begin(), ' ');
        if (sscanf(line.c_str(), "%*[ ]vertex %f %f %f", &vect.x, &vect.y, &vect.z) == 3)
        {
            vertex_buffer.push_back(vect);
            unique_vertex_set_ref.insert(vect);
        }
        else if (sscanf(line.c_str(), "%*[ ]facet normal %f %f %f", &vect.x, &vect.y, &vect.z) == 3)
        {
            normal_buffer.push_back(vect);
        }
    }
    
    assert(vertex_buffer.size() % 3 == 0);
    assert(normal_buffer.size() * 3 == vertex_buffer.size());
    size_t face_size = vertex_buffer.size() / 3;
    
    for (size_t i = 0; i < face_size; ++i)
    {
        size_t face_index = i;
        
        glm::vec3 tri_v1 = vertex_buffer[i * 3 + 0];
        glm::vec3 tri_v2 = vertex_buffer[i * 3 + 1];
        glm::vec3 tri_v3 = vertex_buffer[i * 3 + 2];
        
        size_t tri_v1_index = std::distance(unique_vertex_set_ref.begin(), unique_vertex_set_ref.find(tri_v1));
        size_t tri_v2_index = std::distance(unique_vertex_set_ref.begin(), unique_vertex_set_ref.find(tri_v2));
        size_t tri_v3_index = std::distance(unique_vertex_set_ref.begin(), unique_vertex_set_ref.find(tri_v3));
        
        Face face;
        face.p1 = tri_v1_index;
        face.p2 = tri_v2_index;
        face.p3 = tri_v3_index;
        face.p4 = tri_v3_index;
        face.normal = normal_buffer[i];
        
        float rad_v1_v2 = acosf(
                                glm::dot(tri_v3 - tri_v1, tri_v3 - tri_v2)
                                / glm::length(tri_v3 - tri_v1)
                                / glm::length(tri_v3 - tri_v2)
                                );
        
        float rad_v2_v3 = acosf(
                                glm::dot(tri_v1 - tri_v2, tri_v1 - tri_v3)
                                / glm::length(tri_v1 - tri_v2)
                                / glm::length(tri_v1 - tri_v3)
                                );
        
        float rad_v3_v1 = acosf(
                                glm::dot(tri_v2 - tri_v3, tri_v2 - tri_v1)
                                / glm::length(tri_v2 - tri_v3)
                                / glm::length(tri_v2 - tri_v1)
                                );
        
        if (rad_v1_v2 > rad_v2_v3 && rad_v1_v2 > rad_v3_v1)
        {
            vertex_to_face_map_ref[tri_v1_index].insert(face_index);
            vertex_to_face_map_ref[tri_v2_index].insert(face_index);
            face.connect_p1 = tri_v1_index;
            face.connect_p2 = tri_v2_index;
            face.noconnect_p = tri_v3_index;
        }
        else if (rad_v2_v3 > rad_v1_v2 && rad_v2_v3 > rad_v3_v1)
        {
            vertex_to_face_map_ref[tri_v2_index].insert(face_index);
            vertex_to_face_map_ref[tri_v3_index].insert(face_index);
            face.connect_p1 = tri_v2_index;
            face.connect_p2 = tri_v3_index;
            face.noconnect_p = tri_v1_index;
        }
        else if (rad_v3_v1 > rad_v1_v2 && rad_v3_v1 > rad_v2_v3)
        {
            vertex_to_face_map_ref[tri_v3_index].insert(face_index);
            vertex_to_face_map_ref[tri_v1_index].insert(face_index);
            face.connect_p1 = tri_v3_index;
            face.connect_p2 = tri_v1_index;
            face.noconnect_p = tri_v2_index;
        }
        
        face_buffer_ref.push_back(face);
    }
}


/* private */ void Model::ConvertTrisToQuads(FaceBuffer* face_buffer,
                                            const VertToFaceMap& vertex_to_face_map,
                                            const Vec3Buffer& unique_vertex_buffer)
{
    FaceBuffer& face_buffer_ref = *face_buffer;
    
    for (auto it = face_buffer_ref.begin(); it != face_buffer_ref.end(); ++it)
    {
        if (it->p1 == 0 && it->p2 == 0)
        {
            continue;
        }
        
        size_t index = std::distance(face_buffer_ref.begin(), it);
        
        typedef std::unordered_set<size_t> FaceIndexSet;
        
        FaceIndexSet connecting_face_set;
        FaceIndexSet connecting_face_set_p1 = vertex_to_face_map.at(it->connect_p1);
        FaceIndexSet connecting_face_set_p2 = vertex_to_face_map.at(it->connect_p2);
        
        for (size_t face_index : connecting_face_set_p1)
        {
            if (face_index != index &&
                connecting_face_set_p2.find(face_index) != connecting_face_set_p2.end())
            {
                connecting_face_set.insert(face_index);
            }
        }
        
        if (connecting_face_set.size() == 1)
        {
            Face& connecting_face = face_buffer_ref[*connecting_face_set.begin()];
            
            glm::vec3 tri_center_vec1 =
                unique_vertex_buffer[it->noconnect_p] -
                (unique_vertex_buffer[it->connect_p1] +
                 unique_vertex_buffer[it->connect_p2]) / 2.0f;
            
            glm::vec3 tri_center_vec2 =
                unique_vertex_buffer[connecting_face.noconnect_p] -
                (unique_vertex_buffer[connecting_face.connect_p1] +
                 unique_vertex_buffer[connecting_face.connect_p2]) / 2.0f;
            
            float rad_tri_center = acosf(
                                         glm::dot(tri_center_vec1, tri_center_vec2)
                                         / glm::length(tri_center_vec1)
                                         / glm::length(tri_center_vec2)
                                         );
            
            float face_angle = fabs(180.0f - rad_tri_center / Consts::PHI * 180.0f);
            if (face_angle < Consts::TRIS_TO_QUADS_FACE_ANGLE_MAX)
            {
                connecting_face.p1 = 0;
                connecting_face.p2 = 0;
                connecting_face.p3 = 0;
                connecting_face.p4 = 0;
                
                if (it->p1 == it->noconnect_p)
                {
                    it->p3 = connecting_face.noconnect_p;
                }
                
                if (it->p2 == it->noconnect_p)
                {
                    it->p4 = connecting_face.noconnect_p;
                }
                
                if (it->p3 == it->noconnect_p)
                {
                    it->p3 = it->p2;
                    it->p2 = connecting_face.noconnect_p;
                }
                
                it->normal = glm::normalize((it->normal + connecting_face.normal) / 2.0f);
            }
        }
    }
    
    auto it = std::remove_if(face_buffer_ref.begin(),
                             face_buffer_ref.end(),
                             [](const Face& f){
                                 return f.p1 == 0 && f.p2 == 0;
                             });
    
    face_buffer_ref.erase(it, face_buffer_ref.end());

}


/* private */ void Model::CalcConnectingFace(ConnectingFaceSetBuffer* connecting_face_buffer,
                               const FaceBuffer& face_buffer)
{
    ConnectingFaceSetBuffer& connecting_face_buffer_ref = *connecting_face_buffer;
    
    typedef std::unordered_map<size_t, std::unordered_set<size_t>> VertSharingFaceMap;
    VertSharingFaceMap vert_sharing_face_map;
    
    for (auto it = face_buffer.begin(); it != face_buffer.end(); ++it)
    {
        size_t index = std::distance(face_buffer.begin(), it);
        
        vert_sharing_face_map[it->p1].insert(index);
        vert_sharing_face_map[it->p2].insert(index);
        vert_sharing_face_map[it->p3].insert(index);
        vert_sharing_face_map[it->p4].insert(index);
    }
    
    connecting_face_buffer_ref.resize(face_buffer.size());
    
    for (auto it = face_buffer.begin(); it != face_buffer.end(); ++it)
    {
        size_t index = std::distance(face_buffer.begin(), it);
        
        typedef std::unordered_set<size_t> ConnectingFaceSet;
        ConnectingFaceSet connecting_face_set;
        
        const ConnectingFaceSet& connecting_face_p1 = vert_sharing_face_map[it->p1];
        connecting_face_set.insert(connecting_face_p1.begin(), connecting_face_p1.end());
        
        const ConnectingFaceSet& connecting_face_p2 = vert_sharing_face_map[it->p2];
        connecting_face_set.insert(connecting_face_p2.begin(), connecting_face_p2.end());
        
        const ConnectingFaceSet& connecting_face_p3 = vert_sharing_face_map[it->p3];
        connecting_face_set.insert(connecting_face_p3.begin(), connecting_face_p3.end());
        
        const ConnectingFaceSet& connecting_face_p4 = vert_sharing_face_map[it->p4];
        connecting_face_set.insert(connecting_face_p4.begin(), connecting_face_p4.end());
     
        connecting_face_set.erase(index);
        connecting_face_buffer_ref[index] = connecting_face_set;
    }
}


/* private */ void Model::GenerateVertexArray(VertexArrayBuffer* vertex_array,
                                              const FaceBuffer& face_buffer,
                                              const Vec3Buffer& unique_vertex_buffer)
{
    VertexArrayBuffer& vertex_array_ref = *vertex_array;
    
    vertex_array_ref.reserve(face_buffer.size() * 50);
    
    for (auto it = face_buffer.begin(); it != face_buffer.end(); ++it)
    {
        size_t index = std::distance(face_buffer.begin(), it);
        
        if (it->p3 == it->p4)
        {
            const glm::vec3& vertex_p1 = unique_vertex_buffer[it->p1];
            const glm::vec3& vertex_p2 = unique_vertex_buffer[it->p2];
            const glm::vec3& vertex_p3 = unique_vertex_buffer[it->p3];
            
            vertex_array_ref.push_back(vertex_p1.x);
            vertex_array_ref.push_back(vertex_p1.y);
            vertex_array_ref.push_back(vertex_p1.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
            
            vertex_array_ref.push_back(vertex_p2.x);
            vertex_array_ref.push_back(vertex_p2.y);
            vertex_array_ref.push_back(vertex_p2.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
            
            vertex_array_ref.push_back(vertex_p3.x);
            vertex_array_ref.push_back(vertex_p3.y);
            vertex_array_ref.push_back(vertex_p3.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
        }
        else
        {
            const glm::vec3& vertex_p1 = unique_vertex_buffer[it->p1];
            const glm::vec3& vertex_p2 = unique_vertex_buffer[it->p2];
            const glm::vec3& vertex_p3 = unique_vertex_buffer[it->p3];
            const glm::vec3& vertex_p4 = unique_vertex_buffer[it->p4];
            
            vertex_array_ref.push_back(vertex_p1.x);
            vertex_array_ref.push_back(vertex_p1.y);
            vertex_array_ref.push_back(vertex_p1.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
            
            vertex_array_ref.push_back(vertex_p2.x);
            vertex_array_ref.push_back(vertex_p2.y);
            vertex_array_ref.push_back(vertex_p2.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
            
            vertex_array_ref.push_back(vertex_p4.x);
            vertex_array_ref.push_back(vertex_p4.y);
            vertex_array_ref.push_back(vertex_p4.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
            
            vertex_array_ref.push_back(vertex_p2.x);
            vertex_array_ref.push_back(vertex_p2.y);
            vertex_array_ref.push_back(vertex_p2.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
            
            vertex_array_ref.push_back(vertex_p3.x);
            vertex_array_ref.push_back(vertex_p3.y);
            vertex_array_ref.push_back(vertex_p3.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
            
            vertex_array_ref.push_back(vertex_p4.x);
            vertex_array_ref.push_back(vertex_p4.y);
            vertex_array_ref.push_back(vertex_p4.z);
            vertex_array_ref.push_back(it->normal.x);
            vertex_array_ref.push_back(it->normal.y);
            vertex_array_ref.push_back(it->normal.z);
            vertex_array_ref.push_back(static_cast<float>(index));
        }
    }
    /*
    for (const auto& f : vertex_array_ref)
    {
        std::cout << f << std::endl;
    }
     */
}

