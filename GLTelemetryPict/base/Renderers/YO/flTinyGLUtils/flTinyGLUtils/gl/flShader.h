//
//  flShader.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flShader__
#define __flTinyGLUtils__flShader__

#include <string>

#include "flCommon.h"

FL_NAMESPACE_BEGIN

class MatrixStack;
class Matrix4x4;
class Vec4f;
class Vec3f;
class Vec2f;

class Shader {
public:
    typedef std::shared_ptr<Shader> Ptr;
    
    enum Type {
        TYPE_SINGLE_COLOR,
        TYPE_TEXTURE_SINGLE_COLOR,
    };
    
    static Ptr create(Type type);
    
    Shader();
    ~Shader();
    
    void compileSource(GLenum type, const GLchar *source);
    void linkProgram();
    void validateProgram();
    
    void createProgram();
    void destoroyProgram();
    
    void createShaders();
    void destoroyShaders();
    
    void attachShaders();
    void detachShaders();
    
    void bindAttributeLocation(GLuint index, const std::string& name);
    
    void begin();
    void end();
    
    inline
    GLuint getProgram() const { return mProgram; }
    
    void setColor(fl::Vec4f& color);
    void setModelViewProjectionMatrix(fl::MatrixStack& matrixStack);
    void setModelViewProjectionMatrix(fl::Matrix4x4& mat);
    
    void setUniformMatrix4x4(const std::string& name,
                             GLsizei count,
                             GLboolean transpose,
                             const GLfloat* value);
    void setUniformMatrix3x3(const std::string& name,
                             GLsizei count,
                             GLboolean transpose,
                             const GLfloat* value);
    void setUniformMatrix2x2(const std::string& name,
                             GLsizei count,
                             GLboolean transpose,
                             const GLfloat* value);
    
    void setUniform1f(const std::string& name, GLfloat value);
    void setUniform2f(const std::string& name, GLfloat x, GLfloat y);
    void setUniform3f(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
    void setUniform4f(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniform1i(const std::string& name, GLint value);
    void setUniform2i(const std::string& name, GLint x, GLint y);
    void setUniform3i(const std::string& name, GLint x, GLint y, GLint z);
    void setUniform4i(const std::string& name, GLint x, GLint y, GLint z, GLint w);
    
    void setUniform1fv(const std::string& name, GLsizei count, const GLfloat* value);
    void setUniform2fv(const std::string& name, GLsizei count, const GLfloat* value);
    void setUniform3fv(const std::string& name, GLsizei count, const GLfloat* value);
    void setUniform4fv(const std::string& name, GLsizei count, const GLfloat* value);
    void setUniform1iv(const std::string& name, GLsizei count, const GLint* value);
    void setUniform2iv(const std::string& name, GLsizei count, const GLint* value);
    void setUniform3iv(const std::string& name, GLsizei count, const GLint* value);
    void setUniform4iv(const std::string& name, GLsizei count, const GLint* value);
    
private:
    Shader(const Shader& rhs);
    Shader& operator=(const Shader& rhs);
    
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mProgram;
    
};


FL_NAMESPACE_END


#endif /* defined(__flTinyGLUtils__flShader__) */