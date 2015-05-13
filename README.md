# Otium
* Headers Only
* Easy to Use
* Portable
* Custom renderer
* UTF-8 supported

# Getting Started
Otium is easy to use, so we need to include only one header at the top of source file. 
To proper working we must overload a IManager object. We need it, because with this object Otium can load images or fonts, read image and font size etc. 
Your root Widget as Form can be just a ... Widget. This object with no overload doesn't have a look and no handle events. Otium, like rest GUI system, has a node hierarchy. 

`#include "Otium/Otium.h"

`int main()
`{
    // First of all we need to set our implementation of IManager
    Otium::IManager::Set(ourImplOfManager);
    
    // Here should be Skin setting and other things to proper working for manager implementation
    
    // Now we can create ROOT widget
    Otium::Widget root("ROOT");
    
    // Example of Button creating
    Otium::Button* btnTest = root.AddChild<Otium::Button>("btnTest");
    btnTest->SetDestination(0, 0, 71, 33);
    btnTest->SetSrcPosition(Button::STATE_DEFAULT, 0, 0);
    btnTest->SetSrcPosition(Button::STATE_HOVER, 0, 33);
    btnTest->SetSrcPosition(Button::STATE_ACTIVE, 0, 66);
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
        root.Render(deltaTime);
        
        // Present/SwapBuffers here
    }
}

