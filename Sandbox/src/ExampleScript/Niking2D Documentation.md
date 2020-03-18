primitive variables
  Width = application::width
  Height = application::height

- function Init()
  - primitive:
    <!-- - CreateCamera(width, height) -->
    - SetClearColor(r,g,b,a)
    **- LoadTexture(path)**
    - SetCameraPosition
  
- function Update(dt)
  - primitive:
    **- IsKeyPressed('space')**
    - 


- funtion Draw()
  - primitive:
    **- DrawQuad(posX,posY, width, height, r,g,b,a, )**
    **- DrawTex(posX,posY, width, height, texture )**
    <!-- - SetClearColor(r,g,b,a) -->
    <!-- - BeginScene(*m_Camera) -->
    <!-- - EndScene() -->


- function DrawUI()
  - primitive:
    - DrawFount(content, posX, posY, size)



FYI: 分辨率是窗口的大小,  图像显示的大小 和camera相关.

require  ===> sol::lib::package