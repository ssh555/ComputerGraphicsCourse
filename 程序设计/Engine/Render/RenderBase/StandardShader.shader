// 通用顶点着色器
#version 330 core

layout(location = 0) in vec4 position;   // 顶点位置
layout(location = 1) in vec3 normal;     // 顶点法线
layout(location = 2) in vec2 texCoord;   // 纹理坐标

out vec3 FragPos;      // 片段位置
out vec3 Normal;       // 片段法线
out vec2 TexCoord;     // 片段纹理坐标

uniform mat4 model;       // 模型矩阵
uniform mat4 PV;        // 投影矩阵 视图矩阵

void main() {
    // 计算变换后的顶点位置和法线
    FragPos = vec3(model * position);
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoord = texCoord;

    // 计算最终顶点位置
    gl_Position = PV * model * position;
}

// 通用片段着色器
#version 330 core

out vec4 FragColor; // 输出颜色

in vec3 FragPos;    // 片段位置
in vec3 Normal;     // 片段法线
in vec2 TexCoord;   // 片段纹理坐标

uniform vec3 lightDir;    // 光源方向
uniform vec3 viewPos;     // 视点位置
uniform vec3 lightColor;  // 光源颜色
uniform vec3 objectColor; // 物体颜色
uniform float lightIntensity; // 光源强度

uniform sampler2D textureDiffuse;  // 漫反射纹理

void main() {
    // 计算视线方向
    vec3 viewDir = normalize(viewPos - FragPos);

    // 计算漫反射和镜面反射的强度
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightIntensity; // 使用光源强度调节漫反射光照强度
    vec3 specular = vec3(0.0); // 暂时不包含镜面反射

    // 计算最终颜色
    vec3 ambient = 0.1 * lightColor * lightIntensity; // 使用光源强度调节环境光
    vec3 result = (ambient + (diffuse + specular)) * objectColor;

    // 加上纹理
    vec4 texColor = texture(textureDiffuse, TexCoord);

    // 输出最终颜色
    FragColor = vec4(result, 1.0) * texColor;
}
