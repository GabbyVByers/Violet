
## This `readme.md` is still under construction...

***
# Violet
Violet is a lightweight, object-oriented set of tools for desktop development in C++. Violet is currently under active development, with new features and modules planned for the near future. During this time, existing code is liable to be rewritten or reimplemented. Violet does not yet have an anticipated release date.

### Author
- Gabitha Byers (gabbyvbyers@gmail.com)

### Artisanally-Handcrafted Guarantee
Violet is written entirely by hand, without the use of any agentic AI coding tools. The makers of Violet care deeply about code craftsmanship and are strongly committed to publishing code that is well understood by their author.

### Contributions
Violet is not currently accepting contributions from anyone not personally connected to the primary author. Violet will never accept contributions submitted by AI agents.

### License
Violet is distributed under the MIT license. See [license.md](license.md). External libraries used by Violet are distributed under their own licenses.

### External Libraries
 - stb_image is public domain.
 - Dear ImGui is under the MIT License.
 - GLFW is under the zlib/libpng License.
 - The Khronos Specifications are under the Apache License.
 - The EGL Specification and various headers are under the MIT License.
 - GLAD is under the MIT license.

***
# Installation

Violet requires that your build system acknowledge include paths that begin inside `Violet/Libraries/include`, and that your build system’s linker is aware of static libraries located within `Violet/Libraries/lib`. Visual Studio can be configured to do so by following the procedure provided below.

### Adding Violet to a Visual Studio 2022/2026 Project
Open the `Property Pages` of your Visual Studio 2022 or 2026 project.  
Navigate to `Configuration Properties -> VC++ Directories`  
Add `$(SolutionDir)Violet/Libraries/include` to `Include Directories`  
Add `$(SolutionDir)Violet/Libraries/lib` to `Library Directories`  
Navigate to `Configuration Properties -> C/C++ -> General`  
Add `$(SolutionDir)Violet/Libraries/include` to: `Additional Include Directories`  
Navigate to `Configuration Properties -> Linker -> General`  
Add `$(SolutionDir)Violet/Libraries/lib` to: `Additional Library Directories`  
Navigate to `Configuration Properties -> Linker -> Input`  
Add `glfw3.lib`, `opengl32.lib`, and `Ws2_32.lib` to `Additional Dependencies`

***
# Documentation & Tutorials

The following modules are currently provided by Violet. All of the classes in modules provided by Violet exist in a namespace named `Vi`.
 - `Violet/Networking.h`
 - `Violet/Rendering.h`
 - `Violet/Logging.h`
 - `Violet/Math.h`
 - `Violet/SiVector.h`

### The Networking Module

Violet provides a module called Networking that enables access to a lightweight and intuitive UDP socket connection endpoint. A UDP socket can be configured to listen for incoming packets on a specific port. The same socket can be configured to send packets to a specific IPv4 address and port. The following example code demonstrates this ability.

```cpp
#include "Violet/Networking.h"
#include "Violet/Logging.h"
#include <string>

int main() {
    // Create a UDP Socket
    Vi::SocketUDP network_connection{};
    network_connection.set_listening_port(2000);
    network_connection.set_destination_address("127.0.0.1", 2000);

    // Send
    std::string outgoing_message = "I've just sent myself a message over UDP! :)";
    network_connection.send_packet(outgoing_message.c_str(), (int)outgoing_message.size());

    // Receive
    char buffer[1024]{};
    int num_bytes = network_connection.receive_packet(buffer, sizeof(buffer));
    std::string incoming_message(buffer, num_bytes);
    Vi::Log::info(incoming_message);
}
```

### The Rendering Module

Violet provides a module called Rendering that enables 3D rendering within a windows application via OpenGL and GLFW.

***
# Miscellaneous



<!-- Miscellaneous -->

### Code Standard

```cpp

/* Class Layout Standard */

class Foo {
public:
    /* Special Member Functions */
    /* Variables */
    /* Functions */
    /* Operators */
private:
    /* Friendships */
    /* Deleted or Private Special Member Functions */
    /* Internal Types (Always Plain Structs) */
    /* Variables */
    /* Functions */
};

/* Constructor(s) Only (Example) */

class Baz {
public:
    Baz() = default;
    Baz(int, int, int = 1)
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

/* All Special Members (Example) */

class Bar {
public:
    Bar();
    Bar(const Bar&);
    Bar(Bar&&) noexcept;
    Bar& operator = (const Bar&);
    Bar& operator = (Bar&&) noexcept;
    ~Bar();
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

```

# Types

### 2D Cross Product

$$
a\times b=a_{x}b_{y}-a_{y}b_{x}
$$

### 3D Cross Product

$$
a\times b= 
\begin{Bmatrix}
c_{x}=a_{y}b_{z}-a_{z}b_{y}\\
c_{y}=a_{z}b_{x}-a_{x}b_{z}\\
c_{z}=a_{x}b_{y}-a_{y}b_{x}
\end{Bmatrix}
$$

### Quaternion Multiplication

$$
a\times b=
\begin{Bmatrix}
c_{w}=a_{w}b_{w}-a_{x}b_{x}-a_{y}b_{y}-a_{z}b_{z}\\
c_{x}=a_{w}b_{x}+a_{x}b_{w}+a_{y}b_{z}-a_{z}b_{y}\\
c_{y}=a_{w}b_{y}-a_{x}b_{z}+a_{y}b_{w}+a_{z}b_{x}\\
c_{z}=a_{w}b_{z}+a_{x}b_{y}-a_{y}b_{x}+a_{z}b_{w}
\end{Bmatrix}
$$

### Scalar Matrix

$$
m_{\text{scalar}}=
\begin{bmatrix}
s & 0 & 0 & 0\\
0 & s & 0 & 0\\
0 & 0 & s & 0\\
0 & 0 & 0 & 1
\end{bmatrix}
$$

### Translation Matrix

$$
m_{\text{trans}}=
\begin{bmatrix}
0 & 0 & 0 & x\\
0 & 0 & 0 & y\\
0 & 0 & 0 & z\\
0 & 0 & 0 & 1
\end{bmatrix}
$$

### Rotation Matrix (from Quaternion)

$$
m_{\text{rot}}=
\begin{bmatrix}
1-2(y^{2}+z^{2}) & 2(xy-zw) & 2(xz+yw) & 0\\
2(xy+zw) & 1-2(x^{2}+z^{2}) & 2(yz-xw) & 0\\
2(xz-yw) & 2(yz+xw) & 1-2(x^{2}+y^{2}) & 0\\
0 & 0 & 0 & 1
\end{bmatrix}
$$

# Camera

### Projection Matrix

$$
m_{\text{proj}}=
\begin{bmatrix}
\frac{l}{a} & 0 & 0 & 0\\
0 & l & 0 & 0\\
0 & 0 & \frac{f+n}{n-f} & \frac{2fn}{n-f}\\
0 & 0 & -1 & 0
\end{bmatrix}
$$

$$
l=\frac{1}{\text{tan(}\frac{\text{fov}}{2}\text{)}}
$$

$$
a=\frac{\text{width}}{\text{height}}\longrightarrow\text{aspect ratio}
$$

$$
n=\text{near plane}
$$

$$
f=\text{far plane}
$$

### Infininte Projection Matrix

$$
m_{\infty}=
\begin{bmatrix}
\frac{l}{a} & 0 & 0 & 0\\
0 & l & 0 & 0\\
0 & 0 & -1 & -2n\\
0 & 0 & -1 & 0
\end{bmatrix}
$$

$$
\lim_{f \to \infty } \left( \frac{f+n}{n-f} \right)=-1
$$

$$
\lim_{f \to \infty } \left( \frac{2fn}{n-f} \right)=-2n
$$

# Heading 1
## Heading 2
### Heading 3
#### Heading 4
##### Heading 5
###### Heading 6

This is some text

_This is some text_

__This is some text__

~~This is some text~~

`This is some text`

- Item
- Item
  - Item
  - Item
  - Item
    - Item
  - Item

[hyperlink](https://example.com)

![Alt text](image_url)

> This is a quote

>> A nested quote

Single Curley Brace Example:

$$
x=
\begin{cases}
ThingOne\\
ThingTwo
\end{cases}
$$


| Header 1 | Header 2 | Header 3 |
| -------- | -------- | -------- |
| Cell 1   | Cell 2   | Cell 3   |
| Cell 4   | Cell 5   | Cell 6   |

