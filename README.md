# GPU-accelerated image processor
A simple GPU-accelerated command-line image processor. Image editing operations are implemented on a GPU using CUDA, which can significantly speed-up hi-res image processing.
## External libraries used:
- NVIDIA CUDA (a capable GPU is required)
- OpenCV
## Working:
- Command-line UI
- Image importing and saving
- Edit history (with undo and redo functions)
- NVIDIA GPU driver detection and CUDA availability checking on Windows and Linux
- Image cropping
- Color inversion
- Brightness correction
- Image resize
- Image preview
## In development:
- Contrast correction
- Histogram
- Histogram equalization
- Batch image processing
- GUI
- And more!
## Currently available commands:
```
General functions:
quit - Exits the program
load [file_path] - Loads the image from the selected path
save [file_path] - Saves the edited image to the selected path
undo - Reverts the latest change
redo - Performs the latest reverted action
show [~scale] - Opens the image preview window. If the custom scale (percentage, i.e 75% -> scale = 75) is not specified, the window will be automatically scaled to fit 80% of main screen's height.
history - Shows the history of changes
clear - Clears the notification area

Actions:
brightness [value] - Changes brightness of the image by the specified value (it can be either negative or positive)
invert - Inverts colors of the image
crop [x] [y] [width] [height] - Trims the image from the coordinates (x,y) to (x+width, y+height). Constraints: x+width < full width; y+height < full height.
resize [width] [height] - Resizes the image to the specified size

(~ - optional)
```