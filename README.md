#  Doom-style renderer for OpenGL

Graphics engine (No GUI editor) to create doom-style maps using mapvertex arrays and string arrays for referencing textures. 

For example, a sector may be created using the following data: 

```bash
{ 
  mapvertex_t sector_vertex[4]:{{0,0},{10,0},{10,10},{0,10}},
  floor_height: 0,
  ceil_height: 128,
  upper_textures: {"metal","metal","metal","metal"},
  middle_textures: {"metal","metal","metal","metal"},
  lower_textures: {"metal","metal","metal","metal"},
  light_level: 150
}
```

#  Samples

![sample](https://user-images.githubusercontent.com/70469919/153095587-5014c6b5-0719-41ff-8a6a-4c7d94412e78.png)
![Untitled](https://user-images.githubusercontent.com/70469919/157699272-f09b981b-852b-4ca3-a273-be787fd6399d.png)
![Untitled2](https://user-images.githubusercontent.com/70469919/157700008-f38c4586-1f34-4652-a170-fa25ae9bffbd.png)


#  Credits

- Classes such as a camera, shader, shader_img, resource_manager and texture were obtained from the site https://learnopengl.com/. 

- Doom Hd textures have been taken from the project (https://github.com/KuriKai/DHTP), credit goes to each one of the names on the Copyright / Permissions section.
