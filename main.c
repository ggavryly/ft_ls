#include "ft_ls.h"

int main(int ar, char **av)
{
	clock_t begin = clock();
	struct dirent d;
	char mtime[128];
	struct stat buf;
	DIR *dir;
	struct dirent *entry = &d;
	dir = opendir(".");
	while (entry)
	{
		entry = readdir(dir);
		if (!entry)
			break;
		stat(entry->d_name, &buf);
		ft_strcpy(mtime, ctime(&buf.st_mtimespec));
		ft_printf("%10s - name %5o last modify - %s\n", entry->d_name, buf.st_mode, mtime);
	}
	uid_t id = 1;
	struct passwd *pwd;
	pwd = getpwuid(id);
	ft_printf("%s\n", pwd->pw_name);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	ft_printf("%f - time\n", time_spent);
	closedir(dir);
};