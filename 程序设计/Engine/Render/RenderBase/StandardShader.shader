// 通用顶点着色器
#version 330 core

layout(location = 0) in vec4 position;   // 顶点位置
layout(location = 1) in vec3 normal;     // 顶点法线
layout(location = 2) in vec2 texCoord;   // 纹理坐标

out vec3 FragPos;      // 片段位置
out vec3 Normal;       // 片段法线
out vec2 TexCoord;     // 片段纹理坐标

uniform mat4 model;       // 模型矩阵
uniform mat4 view;        // 视图矩阵
uniform mat4 projection;  // 投影矩阵

void main() {
    // 计算变换后的顶点位置和法线
    FragPos = vec3(model * position);
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoord = texCoord;

    // 计算最终顶点位置
    gl_Position = projection * view * model * position;
}

// 通用片段着色器
#version 330 core

out vec4 FragColor; // 输出颜色

in vec3 FragPos;    // 片段位置
in vec3 Normal;     // 片段法线
in vec2 TexCoord;   // 片段纹理坐标

uniform vec3 lightPos;    // 光源位置
uniform vec3 viewPos;     // 视点位置
uniform vec3 lightColor;  // 光源颜色
uniform vec3 objectColor; // 物体颜色

uniform sampler2D textureDiffuse;  // 漫反射纹理
// uniform sampler2DShadow shadowMap; // 阴影贴图

// float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir)
// {
//     // 转换片段的坐标到光空间
//     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//     projCoords = projCoords * 0.5 + 0.5;
    
//     // 检查片段是否在阴影中
//     float closestDepth = texture(shadowMap, projCoords.xy).r;
//     float currentDepth = projCoords.z;
//     float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

//     return shadow;
// }

void main() {
    // 计算光线方向和反射方向
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));

    // 计算漫反射和镜面反射的强度
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 specular = vec3(0.0); // 暂时不包含镜面反射

    // // 计算阴影
    // vec4 fragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    // float shadow = ShadowCalculation(fragPosLightSpace, lightDir);

    // 计算最终颜色
    vec3 ambient = 0.1 * lightColor; // 环境光
    // vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * objectColor;
    vec3 result = (ambient + (diffuse + specular)) * objectColor;

    // 加上纹理
    vec4 texColor = texture(textureDiffuse, TexCoord);

    // 输出最终颜色
    FragColor = vec4(result, 1.0) * texColor;
}
