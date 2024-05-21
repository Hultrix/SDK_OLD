#define SK_GL

// g++ -o test main1.cpp -I/usr/local/include/ -I/usr/include/skia -lskia -I/usr/include/cairo -lsfml-graphics -lsfml-window -lsfml-system  -lyogacore -lcairo -lOpenImageIO -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio

#include <cairo.h>

#include <memory>
#include <cmath>  
#include <iostream>
#include <mutex>

#include <SFML/Graphics.hpp>

#include <skia/include/gpu/GrDirectContext.h>
#include <skia/include/gpu/gl/GrGLInterface.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkPath.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkRect.h>
#include <skia/include/core/SkRRect.h>
#include <skia/include/core/SkBitmap.h>

#include <OpenImageIO/imageio.h>
using namespace OIIO;

#include <opencv2/opencv.hpp>










int main() {

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Skia and OpenGL Test v0.0.1");
    window.setFramerateLimit(24);

    sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
    sk_sp<GrDirectContext> context = GrDirectContext::MakeGL(interface);
    SkImageInfo imageinfo = SkImageInfo::MakeN32Premul(1024, 768);
    sk_sp<SkSurface> surface = SkSurface::MakeRenderTarget(context.get(), SkBudgeted::kNo, imageinfo);

    if (!surface) {
        std::cerr << "Failed to create Skia GPU surface\n";
        return -1;
    }

    context->flush();

    SkCanvas* canvas = surface->getCanvas();

    window.setActive(true);






     // Cairo Engine
    // Buffer to hold pixel data for a 800x600 canvas
    static uint32_t buffer[800 * 600];

    // Create a Cairo surface backed by the buffer
    cairo_surface_t* surface1 = cairo_image_surface_create_for_data(
        reinterpret_cast<unsigned char*>(buffer),
        CAIRO_FORMAT_ARGB32, // Format to match Skia's expectations (BGRA on little-endian)
        800, 600,            // Width and height of the surface
        800 * 4              // Stride: width * number of bytes per pixel
    );

    // Create a Cairo drawing context
    cairo_t* cr = cairo_create(surface1);

    // Set up text properties
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 90.0);

    // Draw text
    cairo_move_to(cr, 10.0, 135.0);
    cairo_show_text(cr, "Cairo");

    // Draw graphics
    cairo_move_to(cr, 70.0, 165.0);
    cairo_text_path(cr, "Engine");
    cairo_set_source_rgb(cr, 0.5, 0.5, 1);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2.56);
    cairo_stroke(cr);

    // Draw helping lines
    cairo_set_source_rgba(cr, 1, 0.2, 0.2, 0.6);
    cairo_arc(cr, 10.0, 135.0, 5.12, 0, 2*M_PI);
    cairo_close_path(cr);
    cairo_arc(cr, 70.0, 165.0, 5.12, 0, 2*M_PI);
    cairo_fill(cr);

    // Clean up Cairo resources
    cairo_destroy(cr);
    cairo_surface_destroy(surface1);

    // Create a Skia bitmap and install the pixels from the Cairo buffer
    SkBitmap bitmap;
    bitmap.installPixels(
        SkImageInfo::Make(800, 600, kBGRA_8888_SkColorType, kUnpremul_SkAlphaType),
        buffer,
        800 * 4 // Row bytes: width * number of bytes per pixel
    );








// OpenImageIO
const char* filename = "tron.png";

    auto inp = ImageInput::open(filename);
    if (!inp) {
        std::cerr << "Failed to open image: " << filename << std::endl;
        return -1;
    }

    const ImageSpec &spec = inp->spec();
    int xres = spec.width;
    int yres = spec.height;
    int nchannels = spec.nchannels;

    // Allocate memory for pixels
    size_t pixelCount = xres * yres * nchannels;
    auto pixels = std::unique_ptr<unsigned char[]>(new unsigned char[pixelCount]);

    // Read the image data with the correct channel order
    inp->read_image(0, 0, 0, nchannels, TypeDesc::UINT8, pixels.get());
    inp->close();

    // Reorder the color channels if necessary
    // Example: If the original image is RGBA and Skia expects BGRA
    for (int i = 0; i < pixelCount; i += nchannels) {
        unsigned char temp = pixels[i];
        pixels[i] = pixels[i + 2];
        pixels[i + 2] = temp;
    }

    // Create a Skia bitmap and install the pixels from the buffer
    SkBitmap bitmap1;
    bitmap1.installPixels(
        SkImageInfo::Make(xres, yres, kBGRA_8888_SkColorType, kUnpremul_SkAlphaType),
        pixels.get(),
        xres * 4 // Row bytes: width * number of bytes per pixel
    );




/*
    // Open the video file
    cv::VideoCapture video("big_buck_bunny.mp4");
    if (!video.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    cv::Mat frame;
*/
// OpenCV
    cv::Mat image = cv::imread("test.webp"); // Replace "your_image.jpg" with the path to your image

    if (image.empty()) {
        std::cerr << "Failed to load image\n";

    }

    // Convert OpenCV image to Skia Bitmap
    SkBitmap opencvBitmap;
    opencvBitmap.allocPixels(SkImageInfo::Make(image.cols, image.rows, kBGRA_8888_SkColorType, kUnpremul_SkAlphaType));

    cv::Mat rgba_image;
    cv::cvtColor(image, rgba_image, cv::COLOR_BGR2BGRA);
        memcpy(opencvBitmap.getPixels(), rgba_image.data, rgba_image.rows * rgba_image.cols * rgba_image.elemSize());
  
    
    



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        canvas->clear(SkColorSetARGB(255, 255, 255, 0));  // Clear with yellow color, full opacity


          canvas->drawImage(opencvBitmap.asImage(), 400, 0);
          canvas->drawImage(bitmap1.asImage(), 0, 150);
          
          canvas->drawImage(bitmap.asImage(), 200, 0);
                    

          
          

          
          /*
          
           // Decode frame with OpenCV
        if (!video.read(frame)) {
            std::cout << "End of video" << std::endl;

        }

        // Convert to RGBA for Skia
        cv::Mat rgba_frame;
        cv::cvtColor(frame, rgba_frame, cv::COLOR_BGR2BGRA);

        // Create Skia bitmap from the OpenCV frame
        SkBitmap bitmap2;
        bitmap2.allocN32Pixels(rgba_frame.cols, rgba_frame.rows);
        memcpy(bitmap2.getPixels(), rgba_frame.data, rgba_frame.total() * rgba_frame.elemSize());

        // Draw the frame onto the Skia canvas
        canvas->drawImage(SkImage::MakeFromBitmap(bitmap2), 0, 400);
        
        */
        
        
        

        
                    
          SkPaint paint;
          paint.setStyle(SkPaint::kFill_Style);
          paint.setAntiAlias(true);
          paint.setStrokeWidth(4);
          paint.setColor(0xff4285F4);

          SkRect rect = SkRect::MakeXYWH(10, 10, 100, 160);
          canvas->drawRect(rect, paint);

          SkRRect oval;
          oval.setOval(rect);
          oval.offset(40, 80);
          paint.setColor(0xffDB4437);
          canvas->drawRRect(oval, paint);

          paint.setColor(0xff0F9D58);
          canvas->drawCircle(180, 50, 25, paint);

          rect.offset(80, 50);
          paint.setColor(0xffF4B400);
          paint.setStyle(SkPaint::kStroke_Style);
          canvas->drawRoundRect(rect, 10, 10, paint);
        canvas->flush();


        window.display();
    }

//libvlc_media_player_stop(mp);
//libvlc_media_player_release(mp);
//libvlc_media_release(m);
//libvlc_release(vlc_instance);


    return 0;
}
