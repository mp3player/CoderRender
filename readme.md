# split resource and buffer 


# resource manager 
- 1. mesh data
- 2. texture 
- 3. multi-media data
- 4. shader program

# preprocess system
- 1. read main file 
- 2. parse main file to get preprocess command 
- 3. if the commond is 'include' => go to 1


# render shadow
- 1. render to depth buffer with the shadow camera
- 2. render the scene and transform it into the shadow scene 
- 3. compare the depth 