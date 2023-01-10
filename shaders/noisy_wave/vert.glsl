// ==================================================================
#version 330 core
// Read in our attributes stored from our vertex buffer object
// We explicitly state which is the vertex information
// (The first 3 floats are positional data, we are putting in our vector)
layout(location=0)in vec3 position; 
layout(location=1)in vec3 normals; // Our second attribute - normals.
layout(location=2)in vec2 texCoord; // Our third attribute - texture coordinates.
layout(location=3)in vec3 tangents; // Our third attribute - texture coordinates.
layout(location=4)in vec3 bitangents; // Our third attribute - texture coordinates.

// If we are applying our camera, then we need to add some uniforms.
// Note that the syntax nicely matches glm's mat4!
uniform mat4 model; // Object space
uniform mat4 view; // Object space
uniform mat4 projection; // Object space

uniform float time;

// Export our normal data, and read it into our frag shader
out vec3 myNormal;
// Export our Fragment Position computed in world space
out vec3 FragPos;
// If we have texture coordinates we can now use this as well
out vec2 v_texCoord;
out float height;


float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}


void main()
{
    // set a new variable because we cannot modify postion
    vec3 new_position = position;

    // ignore the height given
    float x = position.x;
    float z = position.z;
    float k = 0.01; //control the size of the wave length 
    float w = 1; //controls the oscillation frequency
    float A = 6; //controls the amplitud

    float noise = rand(vec2(x,z));

    new_position.y = A*cos(k*x*noise - w*time) - A*sin(k*z*noise - w*time);

    if(position.y != 0){
        height = (new_position.y+3)/5;
    }
    else{
        height = 0;
    }
    

    gl_Position = projection * view * model * vec4(new_position, 1.0f);

    myNormal = normals;
    // Transform normal into world space
    FragPos = vec3(model* vec4(position,1.0f));

    // Store the texture coordinates which we will output to
    // the next stage in the graphics pipeline.
    v_texCoord = texCoord;
}
// ==================================================================
