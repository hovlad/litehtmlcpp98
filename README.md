# What is litehtml engine?

**litehtml** is the lightweight HTML rendering engine with CSS2/CSS3 support. Note that **litehtml** itself does not draw any text, pictures or other graphics and that **litehtml** does not depend on any image/draw/font library. You are free to use any library to draw images, fonts and any other graphics. **litehtml** just parses HTML/CSS and places the HTML elements into the correct positions (renders HTML). To draw the HTML elements you have to implement the simple callback interface [document_container](https://github.com/litehtml/litehtml/wiki/document_container). This interface is really simple, check it out! The [document_container](https://github.com/litehtml/litehtml/wiki/document_container) implementation is required to render HTML correctly.

[litehtml all information](https://github.com/litehtml/litehtml)

# What is litehtmlcpp98?

**litehtmlcpp98** is c++98 fork [litehtml](https://github.com/litehtml/litehtml).

# Differences from [litehtml](https://github.com/litehtml/litehtml)

  * C++98 (BOOST smart pointers from header only, need only BOOST_PATH variable)
  * [FreeType](https://github.com/aseprite/freetype2) library for fonts rendering (my container_cairo_ft) 
  * in CMakeLists.txt defined LITEHTML_UTF8
  
# Demo

To demo the work you can use [litehtmltopng](https://github.com/hovlad/litehtmltopng) simple render html to png based on [litehtml](https://github.com/litehtml/litehtml) engine.
