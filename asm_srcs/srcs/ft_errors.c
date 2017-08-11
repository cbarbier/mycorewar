#include "asm.h"

void  ft_error(t_asm *sfile)
{
  t_champ *champ;

  champ = sfile->champ;
  while (champ)
  {
    if (champ-> err == 1)
    {
      ft_printf("\x1b[37m%s\x1b[0m:%d:%d: ", sfile->origin, champ->ligne, champ->col + 1);
      if (champ->errcode == 1)
        ft_printf(".name wrong format\n");
      else if (champ->errcode == 2)
        ft_printf(".comment wrong format\n");
      else if (champ->errcode == 3)
        ft_printf("Unknown mnemonique\n");
      else if (champ->errcode == 4)
        ft_printf("Parameter missing\n");
      else if (champ->errcode == 5)
        ft_printf("Wrong parameters\n");
      else if (champ->errcode == 6)
        ft_printf("Unknown label\n");
      ft_printf("%s\n%*c\n",champ->line, champ->col + 1, '^');
    }
    champ = champ->next;
  }
}
