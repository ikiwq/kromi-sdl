# Kromi SDL 
## Overview
KromiSDL is a 2D engine written in c++ with the SDL library.
### Screenshots
<p float="left">
  <img src="https://github.com/ikiwq/KromiSDL/assets/110495658/345bca09-f317-4edb-94b1-a26f3c46abda" width="400" />
  <img src="https://github.com/ikiwq/KromiSDL/assets/110495658/76453f80-d7ff-44d6-888c-a158089acac1" width="400" /> 
</p>

## Requisites 
In order to run, it requires the SDL2, SDL2_Image, SDL2_ttf and SDL2_Mixer libraries.

## List of the built in functions:

### Scenes
KromiSDL is based on multiple Scenes. Each Scene is indipendent from the other; you can render or update them individually.

#### Scene Manager
The Scene Manager manages all the scenes. You can write a code that switches the scene that you are rendering/updating inside of it.

#### The Scene
The Scene.h file contains a class that all scenes inherit from. The scene has by default a Camera, an SDL Event and a size.

### Entity Component System
KromiSDL has an "hybrid" Entity Component System. The ECS.h file contains the EntityManager, Entity and Component classes.

#### Entity Manager
The Entity Manager manages all the entities and their update/render functions. It can also create entities and delete them based on custom conditions. The Entities are put into different groups to allow Rendering Layers(Ex: the map tiles need to be rendered under the player).

#### Entity
The entity is a "container" for all the components. The entity has functions to add a component to its self or to check if it has a component and a Render and Update loop.

#### Components
The components inherit from the Component class. It has by default a Render and Update virtual functions.
When an Entity Update() or Render() is called, the Entity will loop through its components and call the update or render for each component.
#### The pre-built components are:
<ul>
<li>Transform2D (tracks the scale based on the Camera size)</li>
<li>Sprite Component (renders and updates an image based on the Transform and Camera position)</li>
<li>Animation Component (if the sprite component has a sprite sheet, it moves the source rect in the SDL_RenderCopy rect to give the illusion of movement)</li>
<li>Box Collider (gives the entity a hit box)</li>
<li>InputComponent (tracks the inputs of keyboard and mouse) </li>
<li>Text Component (Draws a text) </li>
</ul>

You can also write custom scripts and attach them to an entity.

### Managers
KromiSDL has various managers.

#### Graphics Manager
The Graphics Manager initializes the SDL_VIDEO and SDL_AUDIO and has functions that return a Renderer, a Window or a Texture.

#### Resource Manager
The Resource Manager has functions that return a *SDL_Texture, *font, *music or *SFX. In order to use resources efficiently, every pointer to an asset is stored inside a map to avoid loading duplicates.

#### Audio Manager
The Audio Manager plays music or an SFX.

#### Map
The Map.h file contains the Map class that has functions to create entities and then assign them tiles. It needs a .txt files with the tile map and a texture in order to do it. The map has a "zero" layer for the base map, then a "first" layer for the details than need to overlap the previous layer and then a "second" layer for collision tiles.

#### Timer

The timer keep track of times inside two different functions, in order to allow for the Render() loop and Update() loop to have different numbers of call each seconds.(Ex: The Render() loop is called 60 times in a seconds, while the Update() loop every 100). Every Transform component has a Velocity vector that is multiplied by the delta time between each Update() to allow for frame-indipendent movement.

## License
This project is licensed under the MIT License.
