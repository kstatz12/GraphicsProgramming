#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

//drawable stuff
//positional stuff (if that is different than drawables)
//need to attatch movement/collision stuff? extend? or compose

#include <vector>
#include "drawable.h"

class GameObjectPlugin
{

};

class CollisionPlugin : public GameObjectPlugin
{

};

class GameObject
{
private:
    std::shared_ptr<Drawable> drawable_context;
    std::vector<std::unique_ptr<GameObjectPlugin>> plugins;

    GameObject(std::shared_ptr<Drawable> ctx)
    {
        drawable_context = ctx;
    }
public:

    GameObject()
    {

    }
    GameObject(const GameObject &) = default;
    GameObject(GameObject &&) = delete;
    GameObject &operator=(const GameObject &) = default;
    GameObject &operator=(GameObject &&) = delete;
    // GameObject go = GameObject::create();
    static GameObject create(DrawableBuilder g_builder)
    {
        g_builder.setSize({.5f, 0.5f});
        auto drawable_context = g_builder.build();
        auto go = GameObject(drawable_context);
        return go;
    }

    void configure_plugin(std::unique_ptr<GameObjectPlugin> plugin)
    {
        this->plugins.push_back(std::move(plugin));
    }

    ~GameObject()
    {

    }
};

#endif // GAME_OBJECT_H_
