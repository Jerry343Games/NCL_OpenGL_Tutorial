﻿#version 330 core

uniform sampler2D diffuseTex;
uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

in Vertex {
    vec4 colour;
    vec2 texCoord;
    vec3 normal;
    vec3 worldPos;
} IN;

out vec4 fragColour;

void main(void) {
vec3 incident = normalize(lightPos - IN.worldPos);
vec3 viewDir = normalize(cameraPos - IN.worldPos);
vec3 halfDir = normalize(incident + viewDir);

vec4 diffuse = texture(diffuseTex, IN.texCoord);

float lambert = max(dot(incident, IN.normal), 0.0);
float distance = length(lightPos - IN.worldPos);
float attenuation = 1.0 - clamp(distance / lightRadius, 0.0, 1.0);

    vec3 surface = (diffuse.rgb * lightColour.rgb);
    fragColour.rgb = surface * lambert * attenuation;
    fragColour.rgb += (lightColour.rgb * 0.5) * attenuation * 0.33;
    fragColour.rgb += surface * 0.1; // ambient
    fragColour.a = diffuse.a;

