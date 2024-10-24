#version 330 core 

in Vertex {
    vec4 colour;
} IN;

out vec4 fragColour;

// original triangle vertex positions
vec2 v0 = vec2(-0.5, -0.5);
vec2 v1 = vec2(0.5, -0.5);
vec2 v2 = vec2(0.0, 0.5);

// calculate the midpoints of edge
vec2 m0 = (v0 + v1) * 0.5;
vec2 m1 = (v1 + v2) * 0.5;
vec2 m2 = (v2 + v0) * 0.5; 

//receive the screen size
uniform vec2 screenSize;

//determine if a point is inside a triangle
bool pointInTriangle(vec2 p, vec2 a, vec2 b, vec2 c) {
    vec2 v0 = b - a;
    vec2 v1 = c - a;
    vec2 v2 = p - a;

    float dot00 = dot(v0, v0);
    float dot01 = dot(v0, v1);
    float dot02 = dot(v0, v2);
    float dot11 = dot(v1, v1);
    float dot12 = dot(v1, v2);

    float normalizationFactor = 1.0 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * normalizationFactor;
    float v = (dot00 * dot12 - dot01 * dot02) * normalizationFactor;

    // return true if the point is inside the triangle
    return (u >= 0.0) && (v >= 0.0) && (u + v <= 1.0);
}

void main(void) {
    // get the fragment's screen position
    vec2 fragPos = gl_FragCoord.xy;
    vec2 ndcPos = (fragPos / screenSize) * 2.0 - 1.0;
    
    if (pointInTriangle(ndcPos, m0, m1, m2)) {
        fragColour = vec4(0.1, 0.1, 0.1, 1.0);
    } else {
        fragColour = IN.colour;
    }
}
