/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>
//#include <custom/model.h>
#include <custom/texture.h>
#include <custom/shader.h>


class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    //static std::map<std::string, Model> Models;
    static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    static Shader    GetShader(std::string name);
    static Texture2D LoadTexture(const char *file, bool alpha, std::string name, float shininess, bool noSpecularColor);
    static Texture2D GetTexture(std::string name);
    //static Model Load3DModel(std::string path,std::string name);
    //static Model GetModel(std::string name);
    static void      Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char *file, bool alpha, float shininess, bool noSpecularColor);
    //static Model loadModelFromFile(std::string path);
};

#endif