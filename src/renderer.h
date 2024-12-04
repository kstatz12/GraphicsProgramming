#ifndef RENDERER_H_
#define RENDERER_H_

#include "drawable.h"
#include "shader.h"
#include <memory>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer {
private:
  std::unique_ptr<Shader> shader;
  unsigned int quadVAO;
  // TODO support textures

protected:
  Renderer(std::unique_ptr<Shader> shader) {
    this->shader = std::move(shader);
    unsigned int VBO;
    float vertices[] = {
        // pos
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    };
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

public:
  ~Renderer() { glDeleteVertexArrays(1, &this->quadVAO); }
  static std::unique_ptr<Renderer>
  from_shader(std::function<std::unique_ptr<Shader>()> fn) {
    auto shader = fn();
    return std::unique_ptr<Renderer>(new Renderer(std::move(shader)));
  }

  void render(std::shared_ptr<Drawable> drawable) {
    this->shader->activate();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(drawable->position, 0.0f));

    model = glm::translate(
        model, glm::vec3(0.5f * drawable->size.x, 0.5f * drawable->size.y, 0.0f));
    model = glm::rotate(model, glm::radians(drawable->rotate),
                        glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * drawable->size.x,
                                            -0.5f * drawable->size.y, 0.0f));

    model = glm::scale(model, glm::vec3(drawable->size, 1.0f));

    this->shader->setMatrix4("model", model, false);
    //this->shader->setVector3f("spriteColor", drawable->color, false);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
  }
};

#endif // RENDERER_H_
