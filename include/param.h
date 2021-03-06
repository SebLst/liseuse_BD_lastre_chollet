#ifndef PARAM_H
#define PARAM_H

/**
 * Stores various numerical parameters for the application
*/
namespace param
{
    const double ZOOM_STEP = 0.1;              // 0.1 means each zoom step is +/-10% zoom
    const double MIN_SCALE = 0.1;              // 0.1 means the image cannot be smaller than 10% of its original size
    const int SCROLL_STEP = 100;               // in pixels
    const int WINDOW_MIN_SIZE_X = 300;         // in pixels
    const int WINDOW_MIN_SIZE_Y = 300;         // in pixels
    const int BOOKMARK_PANEL_MAX_SIZE_X = 300; // in pixels
} // namespace param

#endif