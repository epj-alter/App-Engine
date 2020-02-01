# Framework

Mathhelper
Bezierpath
Timer

Graphic settings
Graphics
Assets
Input
Audio
Shapes

Game entity
Texture
Animated
Colliders box circle
Physicshelper
Gameobject - Physicshandler -

# Commons           // MAKE PRECOMPILED HEADER WORK!! PLEASE!!

* src
    Styleshandler
* components
    Container
    Button
    Input Field
    Check Button
    Dropdown List
    Progress Bar
    Slider
    Message Box
    Confirmation Box
* scenes
    SCENEDATA {Textures, Fonts, Audio, }
    SCENE
    Commons.h

# AppCore

## include "Commons.h"

* owned find a better name please
    Definitions
    Hero Data
    Player Data
    Player Attributes
    Hero
    Person
    Player
    Team
    Ladder Team
    Pro Team
    Match
    Ladder Match
    Simulation
    Ladder simulation
* src
    Data Handler 			//FIX IMPORTANT TOPIC!!!!!!!!!!!!!!

# AppClient

* scenes
    * views
        ALL SCENE FILES GO HERE
    * src
        SCENEHANDLER (has to include the latest scene in the include chain..) // FIX!!
* src
    GAME
    MAIN