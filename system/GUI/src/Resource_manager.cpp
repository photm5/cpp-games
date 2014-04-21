#include "Resource_manager.h"

using namespace GUI;

Resource_manager::Resource_manager (std::string graphics_path, std::string graphics_extension)
: graphics_path(graphics_path), graphics_extension(graphics_extension) {
}

sf::Texture& Resource_manager::get_texture ( std::string name ) {
    if (textures.find(name) != textures.end())
        return textures.at(name);
    std::string path = construct_image_path(name);
    std::cout << "Loading texture " << name << " from " << path << std::endl;

    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        throw;
    }
    textures.insert(std::make_pair(name, texture));
    return textures.at(name);
}


std::string Resource_manager::construct_image_path ( std::string name ) {
    std::string path = graphics_path;
    std::replace_copy(name.begin(), name.end(), std::back_inserter(path), '.', '/');
    path.append(graphics_extension);
    return path;
}

