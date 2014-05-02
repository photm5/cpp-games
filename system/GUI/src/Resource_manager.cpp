#include "Resource_manager.h"

using namespace GUI;

Resource_manager::Resource_manager (std::string resources_path, std::string graphics_extension)
: resources_path(resources_path), graphics_extension(graphics_extension), fonts_extension(".ttf") {
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

sf::Font& Resource_manager::get_font ( std::string name ) {
    if (fonts.find(name) != fonts.end())
        return fonts.at(name);
    std::string path = construct_font_path(name);
    std::cout << "Loading font " << name << " from " << path << std::endl;

    sf::Font font;
    if (!font.loadFromFile(path)) {
        throw;
    }
    fonts.insert(std::make_pair(name, font));
    return fonts.at(name);
}

std::string Resource_manager::construct_image_path ( std::string name ) {
    std::string path = resources_path;
    std::replace_copy(name.begin(), name.end(), std::back_inserter(path), '.', '/');
    path.append(graphics_extension);
    return path;
}

std::string Resource_manager::construct_font_path ( std::string name ) {
    std::string path = resources_path;
    std::replace_copy(name.begin(), name.end(), std::back_inserter(path), '.', '/');
    path.append(fonts_extension);
    return path;
}
