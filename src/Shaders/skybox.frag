#version 330 core

in vec3 pass_pos;

out vec4 color;

uniform samplerCube tex;

void main() {

    color = texture(tex, normalize(pass_pos));

}