#ifndef PENGINE_MODEL_MANAGER_H
#define PENGINE_MODEL_MANAGER_H

#include <pengine/model/model.h>

#include <map>

namespace pengine
{
    struct ModelDefine {
        std::string Name;
        std::string ModelPath;
        std::string VertShaderPath;
        std::string FragShaderPath;
    };

    class ModelManager
    {
    private:
        std::map<std::string, Model*> modelMap;
        std::vector<ModelDefine*> modelDefines;

    public:
        ModelManager();
        void RegisterModel(ModelDefine *modelDefine);
        int LoadModels();
        Model* FetchModel(std::string name);
    };
}

#endif