#include <pengine/model/manager.h>

#include <pengine/common.h>

namespace pengine
{
    ModelManager::ModelManager()
    {
        //
    }

    void ModelManager::RegisterModel(ModelDefine *modelDefine)
    {
        this->modelDefines.push_back(modelDefine);
    }

    int ModelManager::LoadModels()
    {
        for (ModelDefine* modelDefine : modelDefines)
        {
            Model* model = new Model();
            model->SetModelPath(modelDefine->ModelPath);
            model->LoadModel();

            model->SetVertShaderPath(modelDefine->VertShaderPath);
            model->LoadVertShader();

            model->SetFragShaderPath(modelDefine->FragShaderPath);
            model->LoadFragShader();

            this->modelMap[modelDefine->Name] = model;
        }

        return 0;
    }

    Model* ModelManager::FetchModel(std::string name)
    {
        std::map<std::string, pengine::Model *>::iterator iter = this->modelMap.find(name);

        if (iter != this->modelMap.end())
        {
            return iter->second;
        }

        return nullptr;
    }

}
