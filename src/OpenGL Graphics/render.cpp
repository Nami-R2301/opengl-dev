//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/render.h"

void Render::clearScreen()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear and change the back buffer color bit with our color.
}

void Render::init_graphics()
{
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR : FAILED TO INITIALIZE GLFW"); //Initialize glfw
    exit(-1);
  }
  Color background_color;  // Default dark-mode-like color for background.
  glClearColor(background_color.get_red(), background_color.get_green(),
               background_color.get_blue(), background_color.get_alpha());

  glFrontFace(GL_CW); // Every shape drawn in clock-wise manner will be considered the FRONT face.
  glCullFace(GL_BACK); // The back side of shapes will NOT be drawn.
  glEnable(GL_CULL_FACE); // Don't render the back face of shapes since the camera won't see it.
  // Let OpenGL keep track of depth for shapes and auto determine if some shapes closer or further away from
  // the camera should take priority (drawn on top of other ones).
  glEnable(GL_DEPTH_TEST);

  //TODO: Depth clamp for later.

  // Let OpenGL do the exponential gamma correction for us so textures and colors don't appear as dark.
  glEnable(GL_FRAMEBUFFER_SRGB);
}
