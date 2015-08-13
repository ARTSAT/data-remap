//
//  flShader.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flShader.h"
#include "flException.h"
#include "flShaders.h"
#include "flVec4f.h"
#include "flMatrix4x4.h"
#include "flMatrixStack.h"
#include <stdlib.h>

using namespace fl;

Shader::Shader() :
mProgram(0),
mVertexShader(0),
mFragmentShader(0)
{
    
}

Shader::~Shader()
{
    destoroyShaders();
    destoroyProgram();
}

#pragma mark ___________________________________________________________________

void Shader::compileSource(GLenum type, const GLchar *source)
{
    GLuint* shader = NULL;
    switch (type) {
        case GL_VERTEX_SHADER:
            shader = &mVertexShader;
            break;
        case GL_FRAGMENT_SHADER:
            shader = &mFragmentShader;
            break;
        default:
            flThrowException("incorrect shader type");
            break;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        printf("Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    GLint status;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        flThrowException("failed to compile shader");
    }
}

void Shader::linkProgram()
{
    GLint status;
    glLinkProgram(mProgram);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(mProgram, logLength, &logLength, log);
        printf("Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (status == 0) {
        destoroyShaders();
        destoroyProgram();
        flThrowException("failed to link shader program");
    }
}

void Shader::validateProgram()
{
    GLint logLength, status;
    glValidateProgram(mProgram);
    glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(mProgram, logLength, &logLength, log);
        printf("Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(mProgram, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        flThrowException("failed to validate program");
    }
}

#pragma mark ___________________________________________________________________

void Shader::createProgram()
{
    if (mProgram) {
        destoroyProgram();
    }
    mProgram = glCreateProgram();
}

void Shader::destoroyProgram()
{
    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
}

#pragma mark ___________________________________________________________________

void Shader::createShaders()
{
    if (mVertexShader) {
        glDeleteShader(mVertexShader);
        mVertexShader = 0;
    }
    if (mFragmentShader) {
        glDeleteShader(mFragmentShader);
        mFragmentShader = 0;
    }
    
    mVertexShader = glCreateShader(GL_VERTEX_SHADER);
    mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}

void Shader::destoroyShaders()
{
    if (mVertexShader) {
        glDeleteShader(mVertexShader);
        mVertexShader = 0;
    }
    if (mFragmentShader) {
        glDeleteShader(mFragmentShader);
        mFragmentShader = 0;
    }
}

#pragma mark ___________________________________________________________________

void Shader::attachShaders()
{
    if (mVertexShader) {
        glAttachShader(mProgram, mVertexShader);
    }
    if (mFragmentShader) {
        glAttachShader(mProgram, mFragmentShader);
    }
}

void Shader::detachShaders()
{
    if (mVertexShader) {
        glDetachShader(mProgram, mVertexShader);
    }
    if (mFragmentShader) {
        glDetachShader(mProgram, mFragmentShader);
    }
}

#pragma mark ___________________________________________________________________

void Shader::bindAttributeLocation(GLuint index, const std::string& name)
{
    glBindAttribLocation(getProgram(), index, name.c_str());
}

#pragma mark ___________________________________________________________________

void Shader::begin()
{
    if (mProgram) {
        glUseProgram(mProgram);
    }
    else {
        flThrowException("shader haven't loaded yet");
    }
}

void Shader::end()
{
    glUseProgram(0);
}

#pragma mark ___________________________________________________________________

void Shader::setColor(fl::Vec4f& color)
{
    setUniform4fv("color", 1, color.getPtr());
}

void Shader::setModelViewProjectionMatrix(fl::MatrixStack& matrixStack)
{
    setUniformMatrix4x4("modelViewProjectionMatrix",
                        1,
                        false,
                        matrixStack.getModelViewProjectionMatrix().getPtr());
}

void Shader::setModelViewProjectionMatrix(fl::Matrix4x4& mat)
{
    setUniformMatrix4x4("modelViewProjectionMatrix",
                        1,
                        false,
                        mat.getPtr());
}

void Shader::setUniformMatrix4x4(const std::string& name,
                                 GLsizei count,
                                 GLboolean transpose,
                                 const GLfloat* value)
{
    glUniformMatrix4fv(glGetUniformLocation(getProgram(), name.c_str()),
                       count,
                       transpose,
                       value);
}

void Shader::setUniformMatrix3x3(const std::string& name,
                                 GLsizei count,
                                 GLboolean transpose,
                                 const GLfloat* value)
{
    glUniformMatrix3fv(glGetUniformLocation(getProgram(), name.c_str()),
                       count,
                       transpose,
                       value);
}

void Shader::setUniformMatrix2x2(const std::string& name,
                                 GLsizei count,
                                 GLboolean transpose,
                                 const GLfloat* value)
{
    glUniformMatrix2fv(glGetUniformLocation(getProgram(), name.c_str()),
                       count,
                       transpose,
                       value);
}

void Shader::setUniform1f(const std::string& name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(getProgram(), name.c_str()), value);
}

void Shader::setUniform2f(const std::string& name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(getProgram(), name.c_str()), x, y);
}

void Shader::setUniform3f(const std::string& name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(getProgram(), name.c_str()), x, y, z);
}

void Shader::setUniform4f(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(getProgram(), name.c_str()), x, y, z, w);
}

void Shader::setUniform1i(const std::string& name, GLint value)
{
    glUniform1i(glGetUniformLocation(getProgram(), name.c_str()), value);
}

void Shader::setUniform2i(const std::string& name, GLint x, GLint y)
{
    glUniform2i(glGetUniformLocation(getProgram(), name.c_str()), x, y);
}

void Shader::setUniform3i(const std::string& name, GLint x, GLint y, GLint z)
{
    glUniform3i(glGetUniformLocation(getProgram(), name.c_str()), x, y, z);
}

void Shader::setUniform4i(const std::string& name, GLint x, GLint y, GLint z, GLint w)
{
    glUniform4i(glGetUniformLocation(getProgram(), name.c_str()), x, y, z, w);
}

void Shader::setUniform1fv(const std::string& name, GLsizei count, const GLfloat* value)
{
    glUniform1fv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

void Shader::setUniform2fv(const std::string& name, GLsizei count, const GLfloat* value)
{
    glUniform2fv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

void Shader::setUniform3fv(const std::string& name, GLsizei count, const GLfloat* value)
{
    glUniform3fv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

void Shader::setUniform4fv(const std::string& name, GLsizei count, const GLfloat* value)
{
    glUniform4fv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

void Shader::setUniform1iv(const std::string& name, GLsizei count, const GLint* value)
{
    glUniform1iv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

void Shader::setUniform2iv(const std::string& name, GLsizei count, const GLint* value)
{
    glUniform2iv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

void Shader::setUniform3iv(const std::string& name, GLsizei count, const GLint* value)
{
    glUniform3iv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

void Shader::setUniform4iv(const std::string& name, GLsizei count, const GLint* value)
{
    glUniform4iv(glGetUniformLocation(getProgram(), name.c_str()), count, value);
}

Shader::Ptr Shader::create(Type type)
{
    auto shader = Ptr(new Shader());
    shader->createProgram();
    shader->createShaders();
    
    fl::Vec4f color(1.f, 1.f, 1.f, 1.f);
    
    switch (type) {
        case TYPE_SINGLE_COLOR:
        {
            shader->compileSource(GL_VERTEX_SHADER, kShaderSingleColorVert);
            shader->compileSource(GL_FRAGMENT_SHADER, kShaderSingleColorFrag);
            shader->attachShaders();
            shader->bindAttributeLocation(fl::ATTRIB_VERTEX, "position");
            shader->linkProgram();
            shader->begin();
            shader->setUniform4fv("color", 1, color.getPtr());
            shader->setUniform1f("pointSize", 1.f);
            shader->end();
        }
            break;
            
        case TYPE_TEXTURE_SINGLE_COLOR:
        {
            shader->compileSource(GL_VERTEX_SHADER, kShaderTextureSingleColorVert);
            shader->compileSource(GL_FRAGMENT_SHADER, kShaderTextureSingleColorFrag);
            shader->attachShaders();
            shader->bindAttributeLocation(fl::ATTRIB_VERTEX, "position");
            shader->bindAttributeLocation(fl::ATTRIB_TEXCOORD, "texCoord");
            shader->linkProgram();
            shader->begin();
            shader->setUniform4fv("color", 1, color.getPtr());
            shader->end();
        }
            break;
            
        default:
            break;
    }
    
    shader->detachShaders();
    //shader->destoroyShaders();
    
    return shader;
}
