/*
 
 Copyright (c) 2013 h2so5 <mail@h2so5.net>
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
 
 */

#pragma once

namespace Consts {
    
    const char APP_TITLE[]  = "Polylife";
    
    const int SCREEN_WIDTH  = 1200;
    const int SCREEN_HEIGHT = 800;

    const int RED_BITS      = 8;
    const int GREEN_BITS    = 8;
    const int BLUE_BITS     = 8;
    const int ALPHA_BITS    = 8;
    const int DEPTH_BITS    = 8;
    const int STENCIL_BITS  = 0;
    
    const float TRIS_TO_QUADS_FACE_ANGLE_MAX = 30.0f;
    const int THREAD_SLEEP_USEC = 100000;
    
    const float PHI = 3.14159265f;

} // namespace Consts