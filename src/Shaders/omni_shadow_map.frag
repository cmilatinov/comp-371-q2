#version 330

in vec4 fragment_position;

uniform vec3 light_pos;
uniform float far_plane;

void main()
{
    float distance = length(fragment_position.xyz - light_pos);
    // Get our distance between 0 and 1
    distance = distance/far_plane;
    gl_FragDepth = distance;
}