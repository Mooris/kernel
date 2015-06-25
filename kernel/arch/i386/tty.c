#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>
#include <kernel/kernel.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_WHITE, COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;
  for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
      for ( size_t x = 0; x < VGA_WIDTH; x++ )
	{
	  const size_t index = y * VGA_WIDTH + x;
	  terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
    }
}

void terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}

static void scroll()
{
  unsigned blank, temp;

  blank = 0x20 | (terminal_color << 8);
  if(terminal_row >= VGA_HEIGHT)
    {
      temp = terminal_row - VGA_HEIGHT + 1;
      memcpy(terminal_buffer, terminal_buffer + temp * VGA_WIDTH, (VGA_HEIGHT - temp) * VGA_WIDTH * 2);
      memsetw(terminal_buffer + (VGA_HEIGHT - temp) * VGA_WIDTH, blank, VGA_WIDTH);
      terminal_row = VGA_HEIGHT - 1;
    }
}

static void move_cursor()
{
  unsigned temp;

  temp = terminal_row * VGA_WIDTH + terminal_column;
  outb(0x3D4, 14);
  outb(0x3D5, temp >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, temp);
}

void terminal_putchar(char c)
{
  if(c == 0x08)
    {
      if (terminal_column != 0)
	terminal_column--;
    }
  else if(c == 0x09)
    {
      terminal_column = (terminal_column + 8) & ~(8 - 1);
    }
  else if(c == '\r')
    {
      terminal_column = 0;
    }
  else if(c == '\n')
    {
      terminal_column = 0;
      terminal_row++;
    }
  else if(c >= ' ')
    {
      terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
      terminal_column++;
    }
  if(terminal_column >= VGA_WIDTH)
    {
      terminal_column = 0;
      terminal_row++;
    }
  scroll();
  move_cursor();
}

void terminal_write(const char* data, size_t size)
{
  for ( size_t i = 0; i < size; i++ )
    terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
  terminal_write(data, strlen(data));
}
