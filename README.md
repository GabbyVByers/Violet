
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
int main() {

    Vi::Window window = Vi::Window("App Title", 1920, 1080);

    while (window.is_open()) {
        window.poll_events();
        window.clear(Vi::Color::blue());
        window.display();
    }

    return 0;
}
```

![Alt text](image_url)

> This is a quote

>> A nested quote

Einstein’s equation:

$E = mc^2$

Integral example:

$$
\int_0^1 x^2 \, dx = \frac{1}{3}
$$

$$
\frac{x^{3}}{9}+\frac{\sqrt{67}}{21}
$$

