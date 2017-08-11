
#include "asm.h"

int		main(int argc, char **argv)
{
  if (argc == 2)
    ft_launcher(argv[1]);
  else
    ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
  return (0);
}
