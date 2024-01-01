#include "hlModel.h"
#include "hlDefines.h"

Model::Model()
{

}

Model::~Model()
{

}

Model::Model(string const& path, bool gamma) :gammaCorrection(gamma)
{
    loadModel(path);
}

Model::Model(const Model& other)
{
}

void Model::Draw(Shader shader)
{
    if (meshes.empty()) { return; }

    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader);
    }
}

void Model::setMeshTextures(const std::vector<Texture>& newTextures)
{
    for (Mesh& mesh : meshes)
    {
        mesh.setMeshTextures(newTextures);
    }
}

void Model::SerializeModel(const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) { return; }

    size_t meshCount = this->meshes.size();
    out.write(reinterpret_cast<const char*>(&meshCount), sizeof(size_t));

    for (const Mesh& mesh : this->meshes) {

        size_t vertCount = mesh.vertices.size();
        out.write(reinterpret_cast<const char*>(&vertCount), sizeof(size_t));
        out.write(reinterpret_cast<const char*>(&mesh.vertices[0]), vertCount * sizeof(Vertex));

        size_t indexCount = mesh.indices.size();
        out.write(reinterpret_cast<const char*>(&indexCount), sizeof(size_t));
        out.write(reinterpret_cast<const char*>(&mesh.indices[0]), indexCount * sizeof(unsigned int));

        size_t texCount = mesh.textures.size();
        out.write(reinterpret_cast<const char*>(&texCount), sizeof(size_t));
        for (const Texture& tex : mesh.textures) {
            size_t pathLength = tex.path.size();
            out.write(reinterpret_cast<const char*>(&pathLength), sizeof(size_t));
            out.write(tex.path.c_str(), pathLength);
        }
    }
    out.close();
}

void Model::DeserializeModel(const std::string& filename, const std::string& directory)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) { return; }

    size_t meshCount;
    in.read(reinterpret_cast<char*>(&meshCount), sizeof(size_t));
    this->meshes.resize(meshCount);

    for (Mesh& mesh : this->meshes) {

        size_t vertCount;
        in.read(reinterpret_cast<char*>(&vertCount), sizeof(size_t));
        mesh.vertices.resize(vertCount);
        in.read(reinterpret_cast<char*>(&mesh.vertices[0]), vertCount * sizeof(Vertex));

        size_t indexCount;
        in.read(reinterpret_cast<char*>(&indexCount), sizeof(size_t));
        mesh.indices.resize(indexCount);
        in.read(reinterpret_cast<char*>(&mesh.indices[0]), indexCount * sizeof(unsigned int));

        size_t texCount;
        in.read(reinterpret_cast<char*>(&texCount), sizeof(size_t));
        mesh.textures.resize(texCount);

        for (Texture& tex : mesh.textures) {
            size_t pathLength;
            in.read(reinterpret_cast<char*>(&pathLength), sizeof(size_t));
            tex.path.resize(pathLength);
            in.read(&tex.path[0], pathLength);
            tex.id = TextureFromFile(tex.path.c_str(), directory, this->gammaCorrection);
        }
        mesh.setupMesh();
    }
    in.close();
}

void Model::loadModel(string const& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
       engineLog.Log(Logger::LogLevel::Error, "ASSIMP::", importer.GetErrorString()); return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    return Mesh(vertices, indices, textures);

}


Model& Model::operator=(const Model& other) {
    if (this != &other) {
        // Копирующая логика оператора присваивания, если необходимо
        // ...
    }

    return *this;
}