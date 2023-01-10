#include "Terrain.hpp"
#include "Image.hpp"

#include <iostream>

// Constructor for our object
// Calls the initialization method
Terrain::Terrain(unsigned int xSegs, unsigned int zSegs, std::string fileName) : 
                m_xSegments(xSegs), m_zSegments(zSegs) {
    std::cout << "(Terrain.cpp) Constructor called \n";

    // Load up some image data
    Image heightMap(fileName);
    heightMap.LoadPPM(true);
    // Set the height data for the image
    // TODO: Currently there is a 1-1 mapping between a pixel and a segment
    // You might consider interpolating values if there are more segments
    // than pixels. 
    float scale = 15.0f; // Note that this scales down the values to make
                        // the image a bit more flat.
    // Create height data
    m_heightData = new int[m_xSegments*m_zSegments];
    // Set the height data equal to the grayscale value of the heightmap
    // Because the R,G,B will all be equal in a grayscale image, then
    // we just grab one of the color components.

    // TODO: (Inclass) Implement populate heightData!
    for(unsigned int z = 0; z < m_zSegments; ++z){
        for(unsigned int x = 0; x < m_xSegments; ++x){
            //we obtain the heights by looking at the colors of a grey image
            //we just need the R pixel because is a grey image, i.e. we have the same value of Red, Green and Blue
            //we apply an scale to make the image more flat(i.e. we are making the height value smaller)
            m_heightData[x+z*m_xSegments] = (float) heightMap.GetPixelR(z,x) / scale;
        }
    }

    Init();
}

// Destructor
Terrain::~Terrain(){
    // Delete our allocatted higheithmap data
    if(m_heightData!=nullptr){
        delete m_heightData;
    }
}


// Creates a grid of segments
// This article has a pretty handy illustration here:
// http://www.learnopengles.com/wordpress/wp-content/uploads/2012/05/vbo.png
// of what we are trying to do.
void Terrain::Init(){
    // Create the initial grid of vertices.

    // TODO: (Inclass) Build grid of vertices! 
    for(unsigned int z = 0; z < m_zSegments; ++z){
        for(unsigned int x = 0; x < m_xSegments; ++x){
            //a texture ranges from 0.0f - 1.0f, we need to stretch out the image to obtain that range
            float u = 1.0f - ((float)x/(float)m_xSegments);
            float v = 1.0f - ((float)z/(float)m_zSegments);
            //Calculate the correct position and add the texture coordinates
            //we fitted an m_xSegments x m_zSegments 2D array into a one dimension array, 
            // Therefore, the elemnt [x][z] is going to be in [x+z*m_xSegments]
            m_geometry.AddVertex(x,m_heightData[x+z*m_xSegments],z,u,v);
        }
    }


    // Figure out which indices make up each triangle
    // By writing out a few of the indices you can figure out
    // the pattern here. Note there is an offset.
    
    // TODO: (Inclass) Build triangle strip
    for(unsigned int z =0 ; z < m_zSegments-1; ++z){
        for(unsigned int x = 0; x < m_xSegments-1; ++x){
            //we apply the pattern learnt in class to create a grid of triangles
            m_geometry.AddIndex(x+(z*m_xSegments));
            //I add + m_xSegment because the vertex is in the next row (the row behind)
            m_geometry.AddIndex(x+(z*m_xSegments)+m_xSegments);
            m_geometry.AddIndex(x+(z*m_xSegments+1));

            //shared index with the previous triangle
            m_geometry.AddIndex(x+(z*m_xSegments)+1);
            //shared index with the previous triangle
            m_geometry.AddIndex(x+(z*m_xSegments)+m_xSegments);
            //if we imagine the quad, this would be the vertes on the bottom-right corner
            m_geometry.AddIndex(x+(z*m_xSegments)+m_xSegments+1);
        }
    }










   // Finally generate a simple 'array of bytes' that contains
   // everything for our buffer to work with.
   m_geometry.Gen();  
   // Create a buffer and set the stride of information
   m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());
}

// Loads an image and uses it to set the heights of the terrain.
void Terrain::LoadHeightMap(Image image){

}
