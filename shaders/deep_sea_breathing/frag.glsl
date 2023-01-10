// ====================================================
#version 330 core

// ======================= uniform ====================
// Our light sources
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientIntensity;
// Used for our specular highlights
uniform mat4 view;
// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 

// ======================= IN =========================
in vec3 myNormal; // Import our normal data
in vec2 v_texCoord; // Import our texture coordinates from vertex shader
in vec3 FragPos; // Import the fragment position
in float height;

// ======================= out ========================
// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// ======================= Globals ====================
// We will have another constant for specular strength
float specularStrength = 0.5f;


void main()
{
    // Store our final texture color
    vec3 diffuseColor;

    //We wil ignore the texture, and set the color to blue
    //diffuseColor = texture(u_DiffuseMap, v_texCoord).rgb;
    diffuseColor = vec3(0,0,height);


    if(gl_FrontFacing){
        FragColor = vec4(diffuseColor,1.0);
    }else{
        // Additionally color the back side the same color
         FragColor = vec4(diffuseColor,1.0);
    }
}
// ==================================================================
