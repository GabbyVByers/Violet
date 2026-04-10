
### This README is under construction...

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

```cpp

/* Class Layout Standard */

class Baz {
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

/* Single Constructor set to Default */

class Foo {
public:
    Foo() = default;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

/* All Special Members Present */

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

![Alt text](image_url)

> This is a quote

>> A nested quote

2D Cross Product

$$
a\times b=a_{x}b_{y}-a_{y}b_{x}
$$

3D Cross Product

$$
a\times b= 
\begin{Bmatrix}
c_{x}=a_{y}b_{z}-a_{z}b_{y}\\
c_{y}=a_{z}b_{x}-a_{x}b_{z}\\
c_{z}=a_{x}b_{y}-a_{y}b_{x}
\end{Bmatrix}
$$

Quaternion Multiplication

$$
a\times b=
\begin{Bmatrix}
c_{w}=a_{w}b_{w}-a_{x}b_{x}-a_{y}b_{y}-a_{z}b_{z}\\
c_{x}=a_{w}b_{x}+a_{x}b_{w}+a_{y}b_{z}-a_{z}b_{y}\\
c_{y}=a_{w}b_{y}-a_{x}b_{z}+a_{y}b_{w}+a_{z}b_{x}\\
c_{z}=a_{w}b_{z}+a_{x}b_{y}-a_{y}b_{x}+a_{z}b_{w}
\end{Bmatrix}
$$

Scalar Matrix

$$
m_{\text{scalar}}=
\begin{bmatrix}
s & 0 & 0 & 0\\
0 & s & 0 & 0\\
0 & 0 & s & 0\\
0 & 0 & 0 & 1
\end{bmatrix}
$$

Translation Matrix

$$
m_{\text{trans}}=
\begin{bmatrix}
0 & 0 & 0 & x\\
0 & 0 & 0 & y\\
0 & 0 & 0 & z\\
0 & 0 & 0 & 1
\end{bmatrix}
$$

Rotation Matrix (from Quaternion)

$$
m_{\text{rot}}=
\begin{bmatrix}
1-2(y^{2}+z^{2}) & 2(xy-zw) & 2(xz+yw) & 0\\
2(xy+zw) & 1-2(x^{2}+z^{2}) & 2(yz-xw) & 0\\
2(xz-yw) & 2(yz+xw) & 1-2(x^{2}+y^{2}) & 0\\
0 & 0 & 0 & 1
\end{bmatrix}
$$

