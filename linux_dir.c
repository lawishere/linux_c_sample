/*
 *
 *  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
 *
 *  By downloading, copying, installing or using the software you agree to this license.
 *  If you do not agree to this license, do not download, install,
 *  Copy or use the software.
 *
 *  Copyright (C) 2012, JUAN, Co, All Rights Reserved.
 *
 *  Created on: Jul 6, 2015
 *	Author: Frank Law
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

void foreach_dir(char *path, int depth)
{
	DIR *Dir;
	struct dirent *Entry;
	struct stat statbuf;
	char whole_path[1024];

	// Init Root Path
	snprintf(whole_path, sizeof(whole_path), "%s", path);

	Dir = opendir(whole_path);
	if (!Dir)
	{
		fprintf(stderr, "Cannot Open Directory \"%s\"\n", path);
		return;
	}

	while (NULL != (Entry = readdir(Dir)))
	{

		lstat(Entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			// Skip Local and Upper Directory Description
			if (0 == strcmp(".", Entry->d_name)
					|| 0 == strcmp("..", Entry->d_name))
			{
				continue;
			}

			printf("%*s%s\r\n", depth, " ", Entry->d_name);
			if (0 == depth || depth > 1)
			{
				snprintf(whole_path + strlen(whole_path),
						sizeof(whole_path) - strlen(whole_path), "/%s",
						Entry->d_name);
				foreach_dir(whole_path, depth > 1 ? depth - 1 : depth);
			}
		}
		else
		{
			printf("%s/%s\r\n", whole_path, Entry->d_name);
		}
	}

	closedir(Dir);
}

int main()
{
	printf("Directory scan of /home:\n");
	foreach_dir("/home", 2);
	printf("done.\n");
	return 0;

}
