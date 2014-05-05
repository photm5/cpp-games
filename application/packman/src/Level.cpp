#include "Level.h"

using namespace packman;

std::string construct_level_path (std::string name) {
    std::string path = "application/packman/res/levels/";
    path.append(name);
    path.append(".txt");
    return path;
}


Level::Level (std::string name, GUI::Resource_manager* resource_manager) : name(name) {
    this->resource_manager = resource_manager;
    reset();
}

void Level::reset() {
    std::ifstream file (construct_level_path(name));
    if (!file.is_open()) {
        std::cout << "Failed to open level " << name << std::endl;
        std::cout << "Path: " << construct_level_path(name) << std::endl;
        throw;
    }

    std::cout << "parsing level " << name << std::endl;

    gamelogic::Level level;
    std::vector<std::function<void(gamelogic::World&)>> entities;

    std::string line;
    for (int y = 1; std::getline(file, line); ++y) {
        for (int x = 0; x < line.size(); ++x) {
            char tile_descriptor = line.at(x);
            switch (tile_descriptor) {
                case '#':
                    {
                        Wall* wall = new Wall (geom2d::Vector<int> (x, y), *resource_manager);
                        level.set_tile(wall);
                        draw_broadcaster.subscribe(wall);
                    }
                    break;

                case 'P':
                    {
                        entities.push_back([x,y,this](gamelogic::World& world) {
                                Packman* packman = new Packman(geom2d::Vector<int> (x, y), *resource_manager, &world);
                                world.spawn_actor(packman);
                                draw_broadcaster.subscribe(packman);
                                player = packman;
                                });
                    }
                    break;

                case 'G':
                    {
                        entities.push_back([x,y,this](gamelogic::World& world){
                                Ghost* ghost = new Ghost(geom2d::Vector<int> (x, y), *resource_manager, &world);
                                world.spawn_actor(ghost);
                                draw_broadcaster.subscribe(ghost);
                                });
                    }
                    break;

                case '.':
                    {
                        entities.push_back([x,y,this](gamelogic::World& world){
                                Dot* dot = new Dot(geom2d::Vector<int> (x, y), *resource_manager, &world);
                                world.spawn_powerup(dot);
                                draw_broadcaster.subscribe(dot);
                                });
                    }
                    break;

                case 'e':
                    {
                        entities.push_back([x,y,this](gamelogic::World& world){
                                Eat_ghost_powerup* eat = new Eat_ghost_powerup(geom2d::Vector<int> (x, y), *resource_manager, &world);
                                world.spawn_powerup(eat);
                                draw_broadcaster.subscribe(eat);
                                });
                    }
                    break;

                case ' ': // air
                    break;

                default:
                    std::cout << std::endl << std::endl;
                    std::cout << "'" << tile_descriptor << "' is not valid." << std::endl;
                    throw;
            }
            std::cout << tile_descriptor;
        }
        std::cout << std::endl;
    }

    std::cout << "parsed level " << name << " successfully." << std::endl;
    std::cout << "adding entities... ";

    world = std::make_shared<gamelogic::World> (level);

    std::for_each(entities.begin(), entities.end(),
            [&](std::function<void(gamelogic::World&)> fun) { fun(*world); });

    std::cout << "done." << std::endl;

    file.close();
}


std::shared_ptr<gamelogic::World> Level::get_world () {
    return world;
}

events::Shared_broadcaster<GUI::Draw_event> Level::get_draw_broadcaster () {
    return draw_broadcaster;
}

Packman* Level::get_player () {
    return player;
}

