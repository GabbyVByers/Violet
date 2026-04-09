
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

$$
\int_0^1x^2\ dx=\frac{1}{3}
$$

$$
\frac{x^{3}}{9}+\frac{\sqrt{67}}{21}
$$

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

