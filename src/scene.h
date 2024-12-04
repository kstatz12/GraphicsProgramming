#ifndef SCENE_H_
#define SCENE_H_

#include "drawable.h"
#include <memory>

#include "drawable.h"
class Scene
{
    void register_element(std::unique_ptr<Drawable> drawable);
};

#endif // SCENE_H_
