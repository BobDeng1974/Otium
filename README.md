### Otium
* Headers Only
* Easy to Use
* Portable
* Custom renderer
* UTF-8 supported

### Getting Started
Otium is easy to use, so we need to include only one header at the top of source file. 
To proper working we must overload a IManager object. We need it, because with this object Otium can load images or fonts, read image and font size etc. 
Your root Widget as Form can be just a ... Widget. This object with no overload doesn't have a look and no handle events. Otium, like rest GUI system, has a node hierarchy. 

```cpp
#include "Otium/Otium.h"

int main()
{
    // First of all we need to set our implementation of IManager
    Otium::IManager::Set(ourImplOfManager);
    
    // Here should be Skin setting and other things to proper working for manager implementation
    
    // Now we can create ROOT widget
    Otium::Widget root("ROOT");
    
    // Example of Button creating
    Otium::Button* btnTest = root.AddChild<Otium::Button>("btnTest");
    btnTest->SetDestination(0, 0, 71, 33);
    btnTest->SetSrcPosition(Otium::Button::STATE_DEFAULT, 0, 0);
    btnTest->SetSrcPosition(Otium::Button::STATE_HOVER, 0, 33);
    btnTest->SetSrcPosition(Otium::Button::STATE_ACTIVE, 0, 66);
    btnTest->SetSrcSize(71, 33);
    btnTest->GetText()->SetFont("data/fonts/verdana.ttf", 12);
    // By default Otium using uint32 type for color storage, so we can use OTIUM_ENCODE_COLOR macro
    btnTest->GetText()->SetColor(OTIUM_ENCODE_COLOR(255, 255, 255, 255));
    btnTest->GetText()->SetString("Hello!");
    
    while (true)
    {
        // Handle events here
        // For example:
        if (event.type == MOUSE_DOWN)
            root.MouseMoveEvent(x, y, true);
            
        // Update
        root.Update(deltaTime);
        
        // Render
        root.Render();
        
        // Present/SwapBuffers here
    }
}
```

### Set Up Types
You can define types which Otium will be using. You can do it in two ways: Change code in Otium.h file under line `#ifndef OTIUM_DEFINED_TYPES` or define your own above `#include <Otium.h>` and write `#define OTIUM_DEFINED_TYPES`. I suggest you a second way. But, for what you will do it? For example, if you want to use integer types or double precision floating point variables. Remember that, Image type and Font type must be **NULLABLE**.

### Dependencies
Otium is using only FastDelegate as external library/header.

### Default manager implementations
You can find managers in `Implementations` folder. At this moment only SDL is available. To use one of them, just **copy** file to `Otium` folder and include it to the project. Yeah, that is all!

### Your own manager implementation
You can overload a IManager object to create your own implementation. 

### Otium options
You can define options above included _Otium_ header.
For example, to disable scissor test you need to define `OTIUM_NO_SCISSOR_TEST`:
```cpp
#define OTIUM_NO_SCISSOR_TEST
#include "Otium/Otium.h"
```
![scissor test](http://i.imgur.com/88N8ZKs.png)

### TODO
* Form loading from file (XML?)
* Skin template
* More Widgets
* Better textbox editor
* More manager implementations for popular renderers (SFML, Allegro, OpenGL, DirectX)
