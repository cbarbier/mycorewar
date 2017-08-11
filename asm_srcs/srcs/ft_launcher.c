
#include "asm.h"

int		ft_check_error(char *file, t_asm *sfile)
{
	int		len;
	char	**tab;

	len = ft_strlen(file);
	if (len < 2 || file[len - 1] != 's' || file[len - 2] != '.')
	{
		ft_printf("Mauvaise extension de fichier\n");
		return (0);
	}
	else if ((sfile->fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("Erreur lors de l'ouverture du fichier\n");
		return (0);
	}
	tab = ft_strsplit(file, '.');
  sfile->origin = ft_strdup(file);
	sfile->file = ft_strjoin(tab[0], ".cor", 0);
	//ft_free_strtab(tab);
	return (1);
}

int		ft_launcher(char *file)
{
	t_asm	sfile;
  t_champ *champ;

  champ = NULL;
	ft_bzero(&sfile, sizeof(t_asm));
	if (ft_check_error(file, &sfile) && ft_head(&sfile) && ft_asm(&sfile, champ))
    ft_write(&sfile, sfile.champ);
	return (0);
}


