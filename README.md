# GPU-accelerated image processor
A simple GPU-accelerated command-line image processor. Image editing operations are implemented on a GPU using CUDA, which can significantly speed-up hi-res image processing.
## External libraries used:
- NVIDIA CUDA (a capable GPU is required)
- OpenCV
## Working:
- Command-line UI
- Image importing and saving
- Edit history
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