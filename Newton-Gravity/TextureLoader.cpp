#include "TextureLoader.h"

// Texture IDs
GLuint groundTexture, barkTexture, leafTexture, skyTexture, appleTexture;
GLuint skinTexture, hairTexture, noseTexture;
GLuint coatTexture, collarTexture, goldTexture, whiteTexture, blackTexture, brownTexture;

bool useTextures;

unsigned char* loadBMP(const char* filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open BMP file: " << filename << std::endl;
        return nullptr;
    }

    unsigned char header[54];
    file.read(reinterpret_cast<char*>(header), 54);

    if (header[0] != 'B' || header[1] != 'M') {
        std::cerr << "Not a valid BMP file.\n";
        return nullptr;
    }

    width  = *(int*)&header[18];
    height = *(int*)&header[22];
    short bitsPerPixel = *(short*)&header[28];
    int dataOffset = *(int*)&header[10];

    if (bitsPerPixel != 24) {
        std::cerr << "Only 24-bit BMP supported.\n";
        return nullptr;
    }

    bool topDown = (height < 0);
    height = std::abs(height);
    int row_padded = (width * 3 + 3) & (~3);

    auto* data = new unsigned char[width * height * 3];
    auto* rowData = new unsigned char[row_padded];

    file.seekg(dataOffset, std::ios::beg);

    for (int i = 0; i < height; i++) {
        file.read(reinterpret_cast<char*>(rowData), row_padded);
        int dstRow = topDown ? i : (height - 1 - i);
        for (int j = 0; j < width; j++) {
            int src = j * 3;
            int dst = (dstRow * width + j) * 3;
            data[dst + 0] = rowData[src + 2]; // R
            data[dst + 1] = rowData[src + 1]; // G
            data[dst + 2] = rowData[src + 0]; // B
        }
    }

    delete[] rowData;
    return data;
}

GLuint loadTexture(const char* filename) {
    int width, height;
    unsigned char* image = loadBMP(filename, width, height);
    if (!image) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] image;
    return texID;
}

// Fallback function to create a simple colored texture if file loading fails
GLuint createFallbackTexture(float r, float g, float b) {
    const int size = 64;
    auto* data = new unsigned char[size * size * 3];
    
    for (int i = 0; i < size * size * 3; i += 3) {
        data[i] = (unsigned char)(r * 255);
        data[i + 1] = (unsigned char)(g * 255);
        data[i + 2] = (unsigned char)(b * 255);
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    delete[] data;
    return textureID;
}

GLuint getTexture(const std::string& name, float r, float g, float b) {
    std::string path = "textures/" + name + ".bmp";
    GLuint texture = loadTexture(path.c_str());
    if (texture == 0 || !useTextures) {
        texture = createFallbackTexture(r, g, b);
        std::cout << "Using fallback texture - " << name << std::endl;
    }
    return texture;
}

void initTextures(bool useTexture) {
    
    useTextures = useTexture;
    
    // Environment
    groundTexture = getTexture("grass", 0.2f, 0.8f, 0.2f);
    skyTexture = getTexture("sky", 0.5f, 0.8f, 1.0f);

    // Tree
    barkTexture = getTexture("bark", 0.55f, 0.27f, 0.07f);
    leafTexture = getTexture("leaf", 0.1f, 0.7f, 0.1f);
    appleTexture = getTexture("apple", 0.8f, 0.2f, 0.2f);

    // Newton
    skinTexture = getTexture("skin", 0.9f, 0.8f, 0.7f);
    hairTexture = getTexture("hair", 0.85f, 0.85f, 0.85f);
    noseTexture = getTexture("skin", 0.85f, 0.75f, 0.65f);

    // Newton Clothes
    coatTexture = getTexture("purple", 0.2f, 0.1f, 0.4f);
    collarTexture = getTexture("purple", 0.15f, 0.05f, 0.35f);
    
    goldTexture = getTexture("gold", 0.8f, 0.7f, 0.4f);
    whiteTexture = getTexture("white", 0.9f, 0.9f, 0.8f);
    blackTexture = getTexture("black", 0.0f, 0.0f, 0.0f);
    brownTexture = getTexture("brown", 0.6f, 0.5f, 0.3f);

    std::cout << "Textures loaded successfully." << std::endl;
}

//    float coatR = 0.2f, coatG = 0.1f, coatB = 0.4f;      // Dark purple coat
//    float collarR = 0.15f, collarG = 0.05f, collarB = 0.35f; // Darker collar
//    float vestR = 0.6f, vestG = 0.5f, vestB = 0.3f;      // Brown vest
//    float buttonR = 0.8f, buttonG = 0.7f, buttonB = 0.4f; // Gold buttons
