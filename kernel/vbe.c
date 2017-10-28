#include "vbe.h"

void vbe_write(uint16_t index, uint16_t value)
{
   out_word(VBE_DISPI_IOPORT_INDEX, index);
   out_word(VBE_DISPI_IOPORT_DATA, value);
}


void vbe_set(uint16_t position_x, uint16_t position_y, uint16_t bpp)
{
   vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
   vbe_write(VBE_DISPI_INDEX_XRES, position_x);
   vbe_write(VBE_DISPI_INDEX_YRES, position_y);
   vbe_write(VBE_DISPI_INDEX_BPP, bpp);
   vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);   
}
