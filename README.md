# 🎮 Fractol Controls & Features

## 🎯 Usage
```bash
./fractol mandelbrot                    # Display Mandelbrot set
./fractol julia <real> <imaginary>      # Display Julia set with parameters
```

## 🖱️ Mouse Controls
- **Mouse Wheel Up**: Zoom in (centered on mouse position)
- **Mouse Wheel Down**: Zoom out (centered on mouse position)

## ⌨️ Keyboard Controls
- **ESC**: Exit the program
- **+**: Zoom in (keyboard)
- **-**: Zoom out (keyboard)
- **Arrow Keys**: Navigate/pan around the fractal
  - **↑**: Move up
  - **↓**: Move down
  - **←**: Move left  
  - **→**: Move right

## ✨ Enhanced Features

### 🔍 Smart Zoom
- **Zoom-to-Point**: Zoom centers on your mouse cursor position
- **Smooth Scaling**: Progressive zoom factors for natural navigation
- **Deep Zoom**: Increased iteration count (150) for better detail at high zoom levels

### 🎯 Precise Navigation
- **Arrow Key Panning**: Move smoothly through the fractal space
- **Zoom-Aware Movement**: Pan speed adjusts based on current zoom level
- **Keyboard Zoom**: Independent zoom controls via +/- keys

### 🎨 Advanced Rendering
- **Mathematical Color Gradients**: Colors based on mathematical functions
- **High Contrast**: Better distinction between iteration bands
- **Smooth Transitions**: No harsh color boundaries
- **Black Core**: Points in the set remain black for contrast

## 📊 Technical Improvements

### Performance
- Optimized color calculations
- Better memory management
- Smooth real-time rendering

### Mathematics
- Improved iteration escape detection
- Enhanced complex number calculations
- Better coordinate mapping

### User Experience
- Intuitive mouse-based zoom
- Responsive keyboard controls
- Proper window closing (ESC key fixed)

## 🎮 Try These Examples

```bash
# Beautiful Mandelbrot with enhanced colors
./fractol mandelbrot

# Interesting Julia sets
./fractol julia -0.7 0.27015
./fractol julia -0.8 0.156
./fractol julia 0.285 0.01
./fractol julia -0.4 0.6
./fractol julia -0.74529 0.11307
```

## 🎯 Navigation Tips

1. **Start with mouse wheel**: Use scroll wheel to zoom into interesting areas
2. **Use arrow keys**: Fine-tune your position after zooming
3. **Keyboard zoom**: Use +/- for precise zoom control
4. **Explore boundaries**: The most interesting patterns are often at the edges
5. **Deep zoom**: Zoom way in to see incredible detail and patterns

Enjoy exploring the infinite beauty of fractals! 🌟
