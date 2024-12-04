#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

struct Drawable {
    glm::vec2 position;
    glm::vec2 size;
    float rotate;
    glm::vec3 color;
};

class DrawableBuilder {
public:
    DrawableBuilder()
        : position_(0.0f, 0.0f), size_(1.0f, 1.0f), rotate_(0.0f), color_(1.0f, 1.0f, 1.0f)
    {}

    // Set position
    DrawableBuilder& setPosition(const glm::vec2& position) {
        position_ = position;
        return *this;
    }

    // Set size
    DrawableBuilder& setSize(const glm::vec2& size) {
        size_ = size;
        return *this;
    }

    // Set rotation
    DrawableBuilder& setRotation(float rotate) {
        rotate_ = rotate;
        return *this;
    }

    // Set color
    DrawableBuilder& setColor(const glm::vec3& color) {
        color_ = color;
        return *this;
    }

    // Build method to create DrawableContext
    std::shared_ptr<Drawable> build() const {
        auto d = new Drawable{ position_, size_, rotate_, color_ };
        return std::shared_ptr<Drawable>(d);
    }

private:
    glm::vec2 position_;
    glm::vec2 size_;
    float rotate_;
    glm::vec3 color_;
};

#endif // DRAWABLE_H_
