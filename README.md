# ComputerGraphicsCourse
 
To-Do List
- 实现Camera对于渲染视图、区域、相关数据的管理
    CameraManager -> 管理所有的Camera，用于变换、渲染、更新对应数据，提供缩放窗口后更改Camera数据的统一接口函数
    Camera -> 相机数据, IComponent -> 相机是肯定要挂载于物体才生效
- 使用Camera拉伸变换窗口保证绘制按比例尺寸缩放
    glfwSetFramebufferSizeCallback -> 更新用于Camera和Shader对于Render部分的数据
- 接入InputSystem
- 接入物理系统 -> 碰撞检测 & 物理检测
- 封装Renderer便于绘制渲染
- 封装Shader、Material
- Shader 模板


