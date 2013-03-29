#pragma once

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

#include "type.h"

class Model {
public:
    Model(const std::string& path);
    const ConnectingFaceSetBuffer& connecting_face_buffer() const;
    const VertexArrayBuffer& vertex_array() const;
    
private:    
    void ParseSTL(std::ifstream* ifs,
                  FaceBuffer* face_buffer,
                  VertToFaceMap* vertex_to_face_map,
                  Vec3Set* unique_vertex_set);
    
    void ConvertTrisToQuads(FaceBuffer* face_buffer,
                            const VertToFaceMap& vertex_to_face_map,
                            const Vec3Buffer& unique_vertex_set);
    
    void CalcConnectingFace(ConnectingFaceSetBuffer* connecting_faces,
                            const FaceBuffer& face_buffer);
    
    void GenerateVertexArray(VertexArrayBuffer* vertex_array,
                             const FaceBuffer& face_buffer,
                             const Vec3Buffer& unique_vertex_buffer);
    
private: 
    // noncopyable
    Model(const Model&);
    Model& operator=(const Model&);
    
private:
    ConnectingFaceSetBuffer connecting_face_buffer_;
    VertexArrayBuffer vertex_array_;
    
};
