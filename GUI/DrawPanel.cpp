#include "DrawPanel.h"
#include "Color.h"
#include "Rect.h"

#include <iostream>
using namespace std;

DrawPanel::DrawPanel(int w, int h, Drawable* d)
{
   drawable = d;
   width = w;
   height = h;

   add_events(Gdk::BUTTON_PRESS_MASK);
   this->signal_button_press_event().connect(sigc::mem_fun(*this, &DrawPanel::on_button_press_event));

   this->signal_draw().connect(sigc::mem_fun(*this, &DrawPanel::on_draw), false);
}

DrawPanel::~DrawPanel()
{
   delete drawable;
}

bool DrawPanel::on_button_press_event(GdkEventButton* event)
{
   GdkEventType type = event->type;
   if (type == GDK_2BUTTON_PRESS || type == GDK_3BUTTON_PRESS) return false;  //ignore double click or triple click events

   int x = (int) event->x;
   int y = (int) event->y;

   drawable->mouseClicked(x, y);

   //update screen after the mouse click has been processed
   render();

   return true;
}

bool DrawPanel::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
   render(cr);
   return true;
}

void DrawPanel::drawBackground(Cairo::RefPtr<Cairo::Context> cr)
{
   Color white(1.0, 1.0, 1.0);
   Rect rect(&white, width, height);  
   rect.draw(cr, width/2, height/2);
}

void DrawPanel::render()
{
   Glib::RefPtr<Gdk::Window> w = get_window();
   Gdk::Rectangle r(0, 0, width, height);

w->begin_paint_rect(r);  //double buffering!!
   Cairo::RefPtr<Cairo::Context> cr = w->create_cairo_context();
   render(cr);  
w->end_paint();
}

void DrawPanel::render(const Cairo::RefPtr<Cairo::Context>& cr)
{
   drawBackground(cr);
   drawable->draw(cr, width, height);
}
