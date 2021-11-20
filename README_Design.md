# Design and structure

This readme serves as notes and a quick reference for designing the subsystems that will be implemented, as well as other important notes about third-party tools and how they should be used / must be used.



# Rendering: OpenGL  <small>https://www.glfw.org/docs/latest</small>

## **Context**

- A context can only be current on one thread at a time
- A thread can only have one current context at a time
- To pass a context between threads, it must be made non-current on the current thread first  

```
Make current: glfwMakeContextCurrent(pWindow)
Get current: glfwGetCurrentContext();
```

These functions require a context to be current

```C
glfwSwapInterval()
glfwExtensionSupported()
glfwGetProcAddress()
```

## **Using Glad as loader**

Once a current context is set, we can initialize Glad.  
GLFW already provides a function for loading OpenGL/ES function pointers, one that automatically uses the selected context creation API.  
Glad can call this instead of implementing its own.

```C++
// Suppresses dev env's OpenGL header by including glad before glfw
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
...

glfwMakeContextCurrent(pWindow);

gladLoadGLLoader( (Gladloadproc) glfwGetProcAddress);

// We now have access to OpenGL core and extension functions supported
// Ready to start rendering
```

## **Window objects**

``GLFWwindow*`` object encapsulates both a window handle, and a context. Because they are inseperably linked, the same pointer is used as such.

```C++
GLFWwindow* pWindow = glfwCreateWindow(...); // Creates window and context

glfwDestroyWindow(pWindow); // To destroy a window and context

glfwTerminate(); // Also destroys windows and contexts
```

### **Fullscreen windows**

To make a window fullscreen, we must specify which monitor to use.  
The users primary monitor is generally a good place to start: ``glfwGetPrimaryMonitor();``

```C++
GLFWwindow* pWindow = glfwCreateWindow(int, int, "Title", glfwGetPrimaryMonitor(), nullptr);
```

>Read more: [GLFW Docs :: Retrieving monitors](https://www.glfw.org/docs/latest/monitor_guide.html#monitor_monitors)

Once we have a fullscreen window, we can change its resolution, refresh rate and monitor with ``glfwSetWindowMonitor``.  
If we only need to set the resolution, we can instead use: ``glfwSetWindowSize``  
In all cases the video mode will be selected the same way as glfwCreateWindow. If the window already have a context, it is unaffected.

### **Window creation hints** <small>https://www.glfw.org/docs/latest/window_guide.html#window_hints_wnd</small>

Some hints affect the window itself, some the framebuffer and some the context.

> Window hints must be set before window creation, as they serve as additional arguments to the ``glfwCreateWindow`` function

These hints are set to their default value every time ``glfwInit();`` is called.  
```C++
glfwWindowHint // Set integer hint values

glfwWindowHintString // String hint values

glfwDefaultWindowHints // Reset all hints to default
```

# Shaders and the GPU

## **Pipeline**

**Projection and matrices** : http://www.songho.ca/opengl/gl_projectionmatrix.html

**Stages:**

- Input-assembler stage (IA)
    - Read primitive data from user-defined vertex and index buffers
    - Assemble that data into geometric primitives (line lists, triangle strips or primitives with adjacency data)
- Vertex shader stage (VS) <small>[MSDN: Shaders](https://docs.microsoft.com/en-us/previous-versions//bb205146(v=vs.85)?redirectedfrom=MSDN)</small>
    - Responsible for transforming vertex data from object-space to clip-space
        - Object-space => World-space (Model matrix)
            - Local coordinates relative to the objects' local origin are converted to coordinates of the larger worlds' global origin
        - World-space => View-space (View matrix)
            - Converts the world space coordinates to view-space coordinates; as seen from the camera/viewers' point of view
        - View-space => Clips-space (Projection matrix)
            - Clip coordinates are processed to the -1.0 - 1.0 range, which determines which verticies will end up on screen. Projection to clip-space coordinates can add perspective if using perspective projection
        - Clip-space => Screen-space (Viewport transform)
            - Lastly transformed to screen-space coordinates in a process called viewport-transform, that transforms the -1.0 - 1.0 range to viewport coordinates that are defined by the viewport (OpenGL = glViewport). The resulting coordinates are sent to the rastirizer to turn them info fragments.
        - It's of course possible to define a transform that converts from object-space to clip-space in one go, but is less flexible depending on what calculations are necessary on the objects of the world.
    - Performs per-vertex operations such as transformations, skinning, morphing and per-vertex lighting. 
    - The vertex shader takes a single vertex as input and outputs the clip-space position of the vertex. 
    - This is the only shader stage that is absolutely in order to define a valid pipeline object.
- Hull shader stage (HS)
    - Is an optional shader stage which determines how much an input control patch should be tesselated by the tesselation stage.
    - Read: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476340(v=vs.85).aspx
- Tesselator stage (TS)
    - Is a fixed function stage
    - Subdivides patch primitives into smaller primitives according to the tesselation factors specified by the hull stage.
- Domain shader stage (DS)
    - Optional shader stage that computes the final vertex attributes based on the output control points from the hull shader and the interpolation coordinates from the tesselator stage.
    - The input to the domain shader is a single output point from the tessellator stage and the output is the computed attributes of the tessellated primitive.
- Geometry shader stage (GS)
    - An optional stage  that takes a single geometric primitive (a single vertex for a point primitive, three vertices for a triangle primitive, and two vertices for a line primitive) as input and can either discard the primitive, transform the primitive into another primitive type (for example a point to a quad) or generate additional primitives.
- Stream output stage (SO)
    - stage is an optional fixed-function stage that can be used to feed primitive data back into GPU memory. 
    - This data can be recirculated back to the rendering pipeline to be processed by another set of shaders. 
    - This is useful for spawning or terminating particles in a particle effect. 
    - The geometry shader can discard particles that should be terminated or generate new particles if particles should be spawned.
- Rasterized Stage (RS)
    -  is a fixed-function stage which will clip primitives into the view frustum and perform primitive culling if either front-face or back-face culling is enabled. 
    - The rasterizer stage will also interpolate the per-vertex attributes across the face of each primitive and pass the interpolated values to the pixel shader.
- Pixel shader stage (PS)
    - takes the interpolated per-vertex values from the rasterizer stage and produces one (or more) per-pixel color values. 
    - The pixel shader can also optionally output a depth value of the current pixel by mapping a single component 32-bit floating-point value to the SV_Depth semantic but this is not a requirement of the pixel shader program. 
    - The pixel shader is invoked once for each pixel that is covered by a primitive
- Output-merger stage (OM)
    - combines the various types of output data (pixel shader output values, depth values, and stencil information) together with the contents of the currently bound render targets to produce the final pipeline result.


# Rendering: DirectX  <small>https://www.3dgep.com/learning-directx-12-1/</small>