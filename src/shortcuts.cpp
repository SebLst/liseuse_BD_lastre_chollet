#include "shortcuts.h"
#include "id.h"

void addShortcuts(wxAcceleratorTable *accel)
{
    accel->Add(wxAcceleratorEntry(wxACCEL_NORMAL, WXK_LEFT, window::id::PREVIOUS_PAGE));
    accel->Add(wxAcceleratorEntry(wxACCEL_NORMAL, WXK_RIGHT, window::id::NEXT_PAGE));
    accel->Add(wxAcceleratorEntry(wxACCEL_NORMAL, WXK_CONTROL_A, window::id::FIRST_PAGE));
    accel->Add(wxAcceleratorEntry(wxACCEL_NORMAL, WXK_CONTROL_E, window::id::LAST_PAGE));
    accel->Add(wxAcceleratorEntry(wxACCEL_CTRL, WXK_NUMPAD_ADD, wxID_ZOOM_IN));
    accel->Add(wxAcceleratorEntry(wxACCEL_CTRL, WXK_NUMPAD_SUBTRACT, wxID_ZOOM_OUT));
}