#include "hlModel.h"
#include "hlDefines.h"


Model::Model() {}

Model::~Model() {}

Model::Model(string const& path, bool gamma) : gammaCorrection(gamma) {
    loadModel(path);
}

Model::Model(const Model& other) {
    copyModelData(other);
}

Model& Model::operator=(const Model& other) {
    if (this != &other) {
        clearModelData();
        copyModelData(other);
    }
    return *this;
}

void Model::Draw(Shader shader) {
    if (meshes.empty()) {
        return;
    }

    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}

void Model::setMeshTextures(const std::vector<Texture>& newTextures) {
    for (StaticMesh& mesh : meshes) {
        mesh.setMeshTextures(newTextures);
    }
}

void Model::loadModel(string const& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        engineLog.Log(Logger::LogLevel::Error, "ASSIMP::", importer.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            texture.id = LoadTexture(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

StaticMesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // Данные для заполнения
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // Цикл по всем вершинам меша
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // мы объявляем промежуточный вектор, т.к. Assimp использует свой собственный векторный класс, который не преобразуется напрямую в тип glm::vec3, поэтому сначала мы передаем данные в этот промежуточный вектор типа glm::vec3

        // Координаты
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        // Нормали
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        // Текстурные координаты
        if (mesh->mTextureCoords[0]) // если меш содержит текстурные координаты
        {
            glm::vec2 vec;

            // Вершина может содержать до 8 различных текстурных координат. Мы предполагаем, что мы не будем использовать модели,
            // в которых вершина может содержать несколько текстурных координат, поэтому мы всегда берем первый набор (0)
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        // Касательный вектор
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;

        // Вектор бинормали
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    // Теперь проходимся по каждой грани меша (грань - это треугольник меша) и извлекаем соответствующие индексы вершин
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        // Получаем все индексы граней и сохраняем их в векторе indices
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Обрабатываем материалы
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // Мы вводим соглашение об именах сэмплеров в шейдерах. Каждая диффузная текстура будет называться 'texture_diffuseN',
    // где N - порядковый номер от 1 до MAX_SAMPLER_NUMBER. 
    // Тоже самое относится и к другим текстурам:
    // диффузная - texture_diffuseN
    // отражения - texture_specularN
    // нормали - texture_normalN

    // 1. Диффузные карты
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // 2. Карты отражения
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // 3. Карты нормалей
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. Карты высот
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // Возвращаем меш-объект, созданный на основе полученных данных
    return StaticMesh(vertices, indices, textures);
}

void Model::copyModelData(const Model& other) {
    directory = other.directory;
    gammaCorrection = other.gammaCorrection;

   for (const StaticMesh& mesh : other.meshes) {
        meshes.push_back(mesh);
    }

    for (const Texture& texture : other.textures_loaded) {
        textures_loaded.push_back(texture);
    }
}

void Model::clearModelData() {
    meshes.clear();
    textures_loaded.clear();
}

void Model::SerializeModel(const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) { return; }

    size_t meshCount = this->meshes.size();
    out.write(reinterpret_cast<const char*>(&meshCount), sizeof(size_t));

    for (const StaticMesh& mesh : this->meshes) {

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

    for (StaticMesh& mesh : this->meshes) {

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
            tex.id = LoadTexture(tex.path.c_str(), directory);
        }
        mesh.setupMesh();
    }
    in.close();
} 


unsigned int LoadTexture(const char* path, const std::string& directory)
{
    std::string filename = directory + '/' + path;
    std::cout << "Texture at path Load model: " << filename << std::endl;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else
        {
            std::cerr << "Error: Unknown number of components in texture: " << nrComponents << std::endl;
            stbi_image_free(data);
            return 0;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Error: Failed to load texture at path: " << filename << std::endl;
        return 0;
    }

    return textureID;
}



