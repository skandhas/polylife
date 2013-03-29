#pragma once

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
