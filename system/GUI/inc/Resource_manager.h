#ifndef GUARD_GUI_RESOURCE_MANAGER
#define GUARD_GUI_RESOURCE_MANAGER

#include <string>
#include <map>
#include <iostream>

#include <algorithm>
#include <memory>

#include <SFML/Graphics.hpp>

namespace GUI {

    class Resource_manager {
        public:
            Resource_manager (std::string resources_path, std::string graphics_extension);
            ~Resource_manager () = default;

            sf::Texture& get_texture ( std::string name );
            sf::Font& get_font ( std::string name );

        protected:
            std::string resources_path;

            std::string graphics_extension;
            std::string fonts_extension;

            std::map<std::string, sf::Texture> textures;
            std::map<std::string, sf::Font> fonts;

        private:
            Resource_manager ( Resource_manager const & ) = delete;
            void operator= ( Resource_manager const & ) = delete;

            std::string construct_image_path ( std::string name );
            std::string construct_font_path ( std::string name );
    };

}

#endif // GUARD_GUI_RESOURCE_MANAGER
